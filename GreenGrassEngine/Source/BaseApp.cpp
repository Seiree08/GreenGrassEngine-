#include "BaseApp.h"

//Se decaran los métodos init, update, render, destroy y run

HRESULT BaseApp::init()
{
  HRESULT hr = S_OK;

  // Inicializa la swapchain, el render target, y la vista de stencil
  m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);
  m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
  m_depthStencil.init(m_device, m_window.m_width, m_window.m_height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);
  m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
  
  // Inicializa el viewport con las dimensiones de la ventana
  m_viewport.init(m_window);

  // Define the input layout
  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  // Configura la descripción del layout de entrada para la posición
  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";/*Nombre que se identifica en shader*/
  position.SemanticIndex = 0;/*Es por dónde empieza*/
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;/*Es necesario por si agarra valores en caso de que sean 3(RGB) o 2(RG)*/
  position.InputSlot = 0;/*Dónde se va a acomodar */
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;/*Ajusta el espacio de memoria donde se registra eso*/
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;/*Es el clasificador del ELEMENT_DES*/
  position.InstanceDataStepRate = 0;/*Cómo se manda la información*/
  Layout.push_back(position);/*Se guardan los elementos en el vector*/

  // Configura la descripción del layout de entrada para las coordenadas de textura
  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";/*Nombre que se identifica en shader*/
  texcoord.SemanticIndex = 0;/*Es por dónde empieza*/
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;/*Es necesario por si agarra valores en caso de que sean 3(RGB) o 2(RG)*/
  texcoord.InputSlot = 0;/*Dónde se va a acomodar */
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;/*Ajusta el espacio de memoria donde se registra eso*/
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;/*Es el clasificador del ELEMENT_DES*/
  texcoord.InstanceDataStepRate = 0;/*Cómo se manda la información*/
  Layout.push_back(texcoord);/*Se guardan los elementos en el vector*/

  //Inicializa en ShaderProgram con el layout de entrada
  m_shaderProgram.init(m_device, "GreenGrassEngine.fx", Layout);

  //Crea el grid con los valores dados
  CreateGrid(50, 50, 25.0f);

  //Carga el modelo de "Vela" de un .fbx
  m_model.LoadModel("Models/Vela2.fbx");

  // Inicialización de Constant Buffers
  m_CBBufferNeverChanges.init(m_device, sizeof(CBNeverChanges));
  m_CBBufferChangeOnResize.init(m_device, sizeof(CBChangeOnResize));

  //Carga las texturas del modelo "Vela"
  Texture Vela_Char_BaseColor;
  Vela_Char_BaseColor.init(m_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Corneas_BaseColor;
  Vela_Corneas_BaseColor.init(m_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Gun_BaseColor;
  Vela_Gun_BaseColor.init(m_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Legs_BaseColor;
  Vela_Legs_BaseColor.init(m_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Mechanical_BaseColor;
  Vela_Mechanical_BaseColor.init(m_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Plate_BaseColor;
  Vela_Plate_BaseColor.init(m_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

  Texture Vela_Visor_BaseColor;
  Vela_Visor_BaseColor.init(m_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

  //Añade las texturas cargadas a la lista de texturas del modelo
  modelTextures.push_back(Vela_Corneas_BaseColor);        //1
  modelTextures.push_back(Vela_Gun_BaseColor);            //2
  modelTextures.push_back(Vela_Visor_BaseColor);          //3
  modelTextures.push_back(Vela_Legs_BaseColor);           //4
  modelTextures.push_back(Vela_Mechanical_BaseColor);     //5
  modelTextures.push_back(Vela_Char_BaseColor);           //6
  modelTextures.push_back(Vela_Plate_BaseColor);          //7

  //Inicializa el Sampler para las muestras
  m_sampler.init(m_device);

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);

  cbNeverChanges.mView = XMMatrixTranspose(m_View);

  //Configura la maztriz de vista y proyección
  m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
                                          m_window.m_width /* */ / (FLOAT)m_window.m_height /* */,
                                          0.01f,
                                          100.0f);

  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);

  //Set vela Actor y asigna los componentes
  AVela = EngineUtilities::MakeShared<Actor>(m_device);

  //Obtener el componente Transform del Actor
  std::shared_ptr<Transform> transform = AVela->getComponent<Transform>();

  if (!AVela.isNull())
  {

    AVela->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(-0.9f, -2.0f, 2.0f));
    AVela->getComponent<Transform>()->setRotation(EngineUtilities::Vector3(XM_PI / -2.0f, 0.0f, XM_PI / 2.0f));
    AVela->getComponent<Transform>()->setScale(EngineUtilities::Vector3(0.03f, 0.03f, .03f));
    AVela->setMesh(m_device, m_model.meshes);
    AVela->setTextures(modelTextures);
    MESSAGE("Actor", "Actor", "Actor accesed sucessfully.")
  }
  else {
    MESSAGE("Actor", "Actor", "Actor resorurce not found.")
  }

  //Set grid Actor y asigna los componentes
  AGrid = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AGrid.isNull())
  {
    std::vector<MeshComponent> gridMesh;
    gridMesh.push_back(MC);
    AGrid->setMesh(m_device, gridMesh);

    //Inicializa la textura por defecto
    m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);
    gridTexts.push_back(m_default);
    AGrid->setTextures(gridTexts);
    
    AGrid->getComponent<Transform>()->setPosition(EngineUtilities::Vector3(0.0f, -2.0f, 0.0f));
    AGrid->getComponent<Transform>()->setScale(EngineUtilities::Vector3(.03f, .03f, .03f));
    MESSAGE("Actor", "AGrid", "Actor created sucessfully.")
  }
  else {
    MESSAGE("Actor", "AGrid", "Actor resource not found.")
  }

  //initialize interfaz de usuario
  m_UserInterface.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  return S_OK;
}

void BaseApp::update()
{
  // Actualiza la interfaz de usuario y muestra la ventana de demostración de ImGui
  m_UserInterface.update();
  bool show_demo_window = true;
  ImGui::ShowDemoWindow(&show_demo_window);

  // Actualiza los buffers constantes con los cambios necesarios

  m_CBBufferNeverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
  m_CBBufferChangeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

  // Actualiza los actores en la escena
  AVela->update(0, m_deviceContext);
  AGrid->update(0, m_deviceContext);
  
  //permite que se muestren los actores y se modifiquen sus transforms
  AVela->getComponent<Transform>()->ui_noWindow("Transform");
  AVela->update(0, m_deviceContext);
  AGrid->getComponent<Transform>()->ui_noWindow("Grid Transform");
  AGrid->update(0, m_deviceContext);
}

void BaseApp::render()
{

  // Clear the back buffer
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
  m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

  m_viewport.render(m_deviceContext);
  //Esto va en el render, y se pasó a la clase del mismo 
  //"ClearColor" es el color del fondo
  //Device genera los recursos, no los usa 
  //DeviceContext establece o setea los recursos que se presentan en pantalla 

  // Clear the depth buffer to 1.0 (max depth)

  m_depthStencilView.render(m_deviceContext);

  m_shaderProgram.render(m_deviceContext);

  AVela->render(m_deviceContext);
  AGrid->render(m_deviceContext);

  //Actualiza los buffers constante
  m_CBBufferNeverChanges.render(m_deviceContext, 0, 1); // Slot 0
  m_CBBufferChangeOnResize.render(m_deviceContext, 1, 1); // Slot 1

  m_UserInterface.render();
  m_swapchain.present();
}

void BaseApp::destroy()
{
  //Asegurar que el dispositivo no tenga recursos establecidos antes de liberar todo.
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

  //Libera recursos para liberar memoria
  AVela->destroy();
  AGrid->destroy();

  m_CBBufferNeverChanges.destroy();
  m_CBBufferChangeOnResize.destroy();
  m_shaderProgram.destroy();
  m_depthStencil.destroy();
  m_depthStencilView.destroy();
  m_renderTargetView.destroy();
  m_swapchain.destroy();
  m_deviceContext.destroy();
  m_device.destroy();
  m_UserInterface.destroy();
}

int
BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc) 
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //inicializa la ventana
    if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
        return 0;

    //inicializa los recursos de la app
    if (FAILED(init()))
    {
        destroy();
        return 0;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            update();   //Se actualiza tod a la parte matemàtica y fìsica
            render();   //Se actualiza todo lo que tenga qwue ver con seteos o que aparezaca en pantalla
        }
    }

    destroy();

    return (int)msg.wParam;
}

void BaseApp::CreateGrid(int width, int depth, float spacing)
{
  MC.m_vertex.clear();
  MC.m_index.clear();
  float halfLineWidth = .8 * 0.5f;

  for (int i = -width; i <= width; ++i)
  {
    //Crea vertices para una linea vertical como dos triángulos
    MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, -depth * spacing),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, -depth * spacing),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(i * spacing - halfLineWidth, 0, depth * spacing),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(i * spacing + halfLineWidth, 0, depth * spacing),
                            XMFLOAT2(0.0f, 0.0f) });

    MC.m_index.push_back(MC.m_vertex.size() - 4);
    MC.m_index.push_back(MC.m_vertex.size() - 3);
    MC.m_index.push_back(MC.m_vertex.size() - 2);

    MC.m_index.push_back(MC.m_vertex.size() - 3);
    MC.m_index.push_back(MC.m_vertex.size() - 2);
    MC.m_index.push_back(MC.m_vertex.size() - 1);
  }

  for (int i = -depth; i <= depth; ++i)
  {
    //Crea vertices para una linea vertical como dos triángulos
    MC.m_vertex.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing - halfLineWidth),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(width * spacing, 0, i * spacing - halfLineWidth),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(-width * spacing, 0, i * spacing + halfLineWidth),
                            XMFLOAT2(0.0f, 0.0f) });
    MC.m_vertex.push_back({ XMFLOAT3(width * spacing, 0, i * spacing + halfLineWidth),
                            XMFLOAT2(0.0f, 0.0f) });

    MC.m_index.push_back(MC.m_vertex.size() - 4);
    MC.m_index.push_back(MC.m_vertex.size() - 3);
    MC.m_index.push_back(MC.m_vertex.size() - 2);

    MC.m_index.push_back(MC.m_vertex.size() - 3);
    MC.m_index.push_back(MC.m_vertex.size() - 2);
    MC.m_index.push_back(MC.m_vertex.size() - 1);
  }
  MC.m_numVertex = MC.m_vertex.size();
  MC.m_numIndex = MC.m_index.size();
}
