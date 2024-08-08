#include "BaseApp.h"

//Se decaran los métodos init, update, render, destroy y run

HRESULT BaseApp::init()
{
  HRESULT hr = S_OK;
  //
  //    WARNING("Device::CreateRenderTargetView : [")
  //
  //    UINT createDeviceFlags = 0;
  //#ifdef _DEBUG
  //    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
  //#endif
  //
  //    D3D_DRIVER_TYPE driverTypes[] =
  //    {
  //        D3D_DRIVER_TYPE_HARDWARE,
  //        D3D_DRIVER_TYPE_WARP,
  //        D3D_DRIVER_TYPE_REFERENCE,
  //    };
  //    UINT numDriverTypes = ARRAYSIZE( driverTypes );
  //
  //    D3D_FEATURE_LEVEL featureLevels[] =
  //    {
  //        D3D_FEATURE_LEVEL_11_0,
  //        D3D_FEATURE_LEVEL_10_1,
  //        D3D_FEATURE_LEVEL_10_0,
  //    };
  //    UINT numFeatureLevels = ARRAYSIZE( featureLevels );
  //
  //    //Se ajustan las variables por las nuetras 
  //    DXGI_SWAP_CHAIN_DESC sd;
  //    ZeroMemory( &sd, sizeof( sd ) );
  //    sd.BufferCount = 1;
  //    sd.BufferDesc.Width = m_window.m_width; /* */
  //    sd.BufferDesc.Height = m_window.m_height; /* */
  //    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  //    sd.BufferDesc.RefreshRate.Numerator = 60;
  //    sd.BufferDesc.RefreshRate.Denominator = 1;
  //    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  //    sd.OutputWindow = m_window.m_hWnd; /* */
  //    sd.SampleDesc.Count = 1;
  //    sd.SampleDesc.Quality = 0;
  //    sd.Windowed = TRUE;
  //
  //    //Se agarra esto y se pada a "SwapChain.cpp"
  //    
  //    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
  //    {
  //        m_driverType = driverTypes[driverTypeIndex];
  //        hr = D3D11CreateDeviceAndSwapChain( NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
  //                                            D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_device.m_device, &m_featureLevel, &m_deviceContext.m_deviceContext );
  //        if( SUCCEEDED( hr ) )
  //            break;
  //    }
  //    if( FAILED( hr ) )
  //        return hr;
      // Create a render target view
      // ESTO SE COMENTA PORQUE EL BACKBUFEFR SE MANEJA DESDE EL SWAPCHAIN
      //ID3D11Texture2D* pBackBuffer = NULL;
      //hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
      //if( FAILED( hr ) )
      //    return hr;

  m_swapchain.init(m_device, m_deviceContext, m_backBuffer, m_window);

  //Create a render target view a partir de nuestras variables 
  //eL DXGI es parte del formato de la textura
  m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
  //Se comenta pues ya no se ocupa el release
  //m_device.CreateRenderTargetView(m_backBuffer.m_texture, nullptr, &m_pRenderTargetView);
  //hr = m_device.m_device->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
  //m_backBuffer.m_texture->Release(); /*Luego va a ser el destroy de la textura*/
  //if( FAILED( hr ) )
  //    return hr;
//
    // Create depth stencil texture
    //Agregamos nuestra función de init
  m_depthStencil.init(m_device, m_window.m_width, m_window.m_height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);

  //Se ajustan las variables por las nuetras 
  //D3D11_TEXTURE2D_DESC descDepth;
  //ZeroMemory( &descDepth, sizeof(descDepth) );
  //descDepth.Width = m_window.m_width; /* */
  //descDepth.Height = m_window.m_height; /* */
  //descDepth.MipLevels = 1;
  //descDepth.ArraySize = 1;
  //descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  //descDepth.SampleDesc.Count = 1;
  //descDepth.SampleDesc.Quality = 0;
  //descDepth.Usage = D3D11_USAGE_DEFAULT;
  //descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  //descDepth.CPUAccessFlags = 0;
  //descDepth.MiscFlags = 0;
  //m_device.CreateTexture2D(&descDepth, nullptr, &m_pDepthStencil);
  //Se cambia la forma de crear la textura con nuestras variables
  //hr = m_device.m_device->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil );
  //if( FAILED( hr ) )
  //    return hr;
  //
  // Create the depth stencil view
  //D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  //ZeroMemory( &descDSV, sizeof(descDSV) );
  //descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  //descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  //descDSV.Texture2D.MipSlice = 0;
  //
  //m_device.CreateDepthStencilView(m_depthStencil.m_texture, &descDSV, &m_pDepthStencilView);
  //  
  //Se cambia por nuestras variables
  //hr = m_device.m_device->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
  //if( FAILED( hr ) )
   //   return hr;

  m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

  // Setup the viewport
  //Se ajustan las variables por las nuetras 
  //Se comenta pues ya lo implementamos en la clase "Viewport"
  //y llamamos a nuestra función de la clase viewport
  m_viewport.init(m_window);
  //D3D11_VIEWPORT vp;
  //vp.Width = (FLOAT)m_window.m_width; /* */
  //vp.Height = (FLOAT)m_window.m_height; /* */
  //vp.MinDepth = 0.0f;
  //vp.MaxDepth = 1.0f;
  //vp.TopLeftX = 0;
  //vp.TopLeftY = 0;
  //m_deviceContext.m_deviceContext->RSSetViewports( 1, &vp );

  // Compile the vertex shader
  //
  //SE COMENTA POR QUE ESTA PARTE ESTÁ EN "SHADERPROGRAM" PARA VERTEX Y PIXEL
  //ID3DBlob* pVSBlob = NULL;
  //hr = CompileShaderFromFile( "GreenGrassEngine.fx", "VS", "vs_4_0", &pVSBlob );
  //if( FAILED( hr ) )
  //{
  //    MessageBox( NULL,
  //                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
  //    return hr;
  //}
  //
  //// Create the vertex shader
  //// hr = m_device.m_device->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader );
  ////Se sustituye el mpetodo por nuestras variables
  //hr = m_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
  ////No se le hace release al FAILED, ¿quizá por malas prácticas?...
  //if( FAILED( hr ) )
  //{    
  //    pVSBlob->Release();
  //    return hr;
  //}

  // Define the input layout
  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

  D3D11_INPUT_ELEMENT_DESC position;
  position.SemanticName = "POSITION";/*Nombre que se identifica en shader*/
  position.SemanticIndex = 0;/*Es por dónde empieza*/
  position.Format = DXGI_FORMAT_R32G32B32_FLOAT;/*Es necesario por si agarra valores en caso de que sean 3(RGB) o 2(RG)*/
  position.InputSlot = 0;/*Dónde se va a acomodar */
  position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;/*Ajusta el espacio de memoria donde se registra eso*/
  position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;/*Es el clasificador del ELEMENT_DES*/
  position.InstanceDataStepRate = 0;/*Cómo se manda la información*/
  Layout.push_back(position);/*Se guardan los elementos en el vector*/

  D3D11_INPUT_ELEMENT_DESC texcoord;
  texcoord.SemanticName = "TEXCOORD";/*Nombre que se identifica en shader*/
  texcoord.SemanticIndex = 0;/*Es por dónde empieza*/
  texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;/*Es necesario por si agarra valores en caso de que sean 3(RGB) o 2(RG)*/
  texcoord.InputSlot = 0;/*Dónde se va a acomodar */
  texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;/*Ajusta el espacio de memoria donde se registra eso*/
  texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;/*Es el clasificador del ELEMENT_DES*/
  texcoord.InstanceDataStepRate = 0;/*Cómo se manda la información*/
  Layout.push_back(texcoord);/*Se guardan los elementos en el vector*/

  //Se le pasa la info del  init, device, nombre del sahder y el layout
  m_shaderProgram.init(m_device, "GreenGrassEngine.fx", Layout);

  //Crea el grid
  CreateGrid(50, 50, 25.0f);

  //Load Model
  m_model.LoadModel("Models/Vela2.fbx");

  //for (auto& mesh : m_model.meshes)
  //{
  //    //Create Vertex Buffer
  //    Buffer vertexBuffer;
  //    vertexBuffer.init(m_device, mesh, D3D11_BIND_VERTEX_BUFFER);
  //    m_vertexBuffers.push_back(vertexBuffer);
  //    // // Create index buffer
  //    Buffer indexBuffer;
  //    indexBuffer.init(m_device, mesh, D3D11_BIND_INDEX_BUFFER);
  //    m_indexBuffers.push_back(indexBuffer);
  //}
  //YA NO SE OCUPA PORQUE SE USA EN EL FOR DE ARRIBA
  //int size = m_model.GetVertices().size();
  //Se comenta y se sustituye por m_ShaderProgram
  //m_inputLayout.init(m_device, Layout, pVSBlob);
  // Se declara para convertirlo en vector
  //D3D11_INPUT_ELEMENT_DESC layout[] =
  //{
  //    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  //    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  //};
  //UINT numElements = ARRAYSIZE( layout );
      //
  // Create the input layout
  // AQUÍ SE GESTIONA LA PARTE DE INFORMACIÓN DEL SHADER
  //hr = m_device.m_device->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout );
  //layout: es la estructura de datos a mandar a revisar del shader
  //numElements: es el tamaño del arreglo
  //pVSBlob: es la referecncia al VertexShader
  //Se comenta y se sustituye por nuestro init
  //hr = m_device.CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout);
//
    //SE COMENTA PUES SE IMPLEMENTA EN "SHADERPROGRAM"
    //m_inputLayout.init(m_device, Layout, pVSBlob);
    //pVSBlob->Release();
    ////if( FAILED( hr ) )
    ////    return hr;
//
    //// Set the input layout
    ////m_deviceContext.m_deviceContext->IASetInputLayout( m_pVertexLayout );
//
    //// Compile the pixel shader
    //ID3DBlob* pPSBlob = NULL;
    //hr = CompileShaderFromFile( "GreenGrassEngine.fx", "PS", "ps_4_0", &pPSBlob );
    //if( FAILED( hr ) )
    //{
    //    MessageBox( NULL,
    //                "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK );
    //    return hr;
    //}
//
    //// Create the pixel shader
    ////La diferencia de este a vertex shader es el puntero
    ////hr = m_device.m_device->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader );
    //hr = m_device.CreatePixelShader(pPSBlob->GetBufferPointer(), 
    //                                pPSBlob->GetBufferSize(), 
    //                                nullptr, 
    //                                &m_pPixelShader);
    //pPSBlob->Release();
    //if( FAILED( hr ) )
    //    return hr;
    //
    //Almacena la informaciòn de los vèrtices de las caras del cubo
    //Los buffers sirven para contener info
    //SimpleVertex vertices[] =
    //{
    //    { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
//
    //    { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
//
    //    { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
//
    //    { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
//
    //    { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
//
    //    { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
    //    { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
    //    { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    //};
    //
    // Create vertex buffer
    //m_mesh.name = "Vela";
    //m_mesh.vertex = m_model.GetVertices();
//
    ////Guarda la información de los vértices
    ////for (const SimpleVertex& vertex : vertices)
    ////{
    ////    m_mesh.vertex.push_back(vertex);
    ////} 
    ////
    ////NOTA: El static_cast<unsigned int> se está utilizando aquí para convertir
    ////el resultado del método size() de un std::vector a un tipo unsigned int.
    ////El método size() devuelve un valor del tipo std::size_t, que es un tipo
    ////específico de tamaño no negativo. En algunas plataformas, std::size_t puede
    ////ser de un tamaño diferente a unsigned int.
    ////Se almacena el tamaño de vétices 
    //m_mesh.numVertex = static_cast<unsigned int>(m_mesh.vertex.size());
//
    ////Se incializa el buffer con la bandera de vertex buffer
    //m_vertexBuffer.init(m_device, m_mesh, D3D11_BIND_VERTEX_BUFFER);
//
    ////ESTA PARTE ES DEL BUFFER
    ////D3D11_BUFFER_DESC bd;
    ////ZeroMemory( &bd, sizeof(bd) );
    ////bd.Usage = D3D11_USAGE_DEFAULT;
    ////bd.ByteWidth = sizeof( SimpleVertex ) * 24;
    ////bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    ////bd.CPUAccessFlags = 0;
    ////D3D11_SUBRESOURCE_DATA InitData;
    ////ZeroMemory( &InitData, sizeof(InitData) );
    ////InitData.pSysMem = vertices;
    //////hr = m_device.m_device->CreateBuffer( &bd, &InitData, &m_pVertexBuffer );
    //////este bufer tiene InitialData
    //////este es el buffer del VertexShader
    ////hr = m_device.CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
    ////if( FAILED( hr ) )
    ////    return hr;
    ////
    ////// Set vertex buffer
    ////UINT stride = sizeof( SimpleVertex );
    ////UINT offset = 0;
    ////m_deviceContext.m_deviceContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );
    ////
    //// Create index buffer
    //// Create vertex buffer
    ////Es la referencia de sonde se encuentran los recursos, con qué se conecta cada vèrtice 
    ////unsigned int indices[] =
    ////{
    //////Empieza por una cara
    ////    //El 3 dice que empieza por ahí y que se conceta con otros a partir del 3
    ////    3,1,0,
    ////    //Aquí hace la conexión 
    ////    2,1,3,
    //////Esta es otra cara y así
    ////    6,4,5,
    ////    7,4,6,
    ////
    ////    11,9,8,
    ////    10,9,11,
    ////
    ////    14,12,13,
    ////    15,12,14,
    ////
    ////    19,17,16,
    ////    18,17,19,
    ////
    ////    22,20,21,
    ////    23,20,22
    ////};
    ////
    ////for (unsigned int index : indices) {
    ////    m_mesh.index.push_back(index);
    ////}
//
    //m_mesh.index= m_model.GetIndices();
//
    //m_mesh.numIndex = static_cast<unsigned int>(m_mesh.index.size());
//
    //m_indexBuffer.init(m_device, m_mesh, D3D11_BIND_INDEX_BUFFER);

    // Inicialización de Constant Buffers
  m_CBBufferNeverChanges.init(m_device, sizeof(CBNeverChanges));

  m_CBBufferChangeOnResize.init(m_device, sizeof(CBChangeOnResize));

  //m_CBBufferChangesEveryFrame.init(m_device, sizeof(CBChangesEveryFrame));

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

  modelTextures.push_back(Vela_Corneas_BaseColor);        //1
  modelTextures.push_back(Vela_Gun_BaseColor);            //2
  modelTextures.push_back(Vela_Visor_BaseColor);          //3
  modelTextures.push_back(Vela_Legs_BaseColor);           //4
  modelTextures.push_back(Vela_Mechanical_BaseColor);     //5
  modelTextures.push_back(Vela_Char_BaseColor);           //6
  modelTextures.push_back(Vela_Plate_BaseColor);          //7


  //Esta info se procesa en un buffer
  //bd.Usage = D3D11_USAGE_DEFAULT;
  //bd.ByteWidth = sizeof( WORD ) * 36;
  //bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
  //bd.CPUAccessFlags = 0;
  //InitData.pSysMem = indices;
  ////hr = m_device.m_device->CreateBuffer( &bd, &InitData, &m_pIndexBuffer );
  ////este bufer tiene InitialData
  ////este es el buffer del IndexShader
  //hr = m_device.CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
  //
  //if( FAILED( hr ) )
  //    return hr;
  //
  //// Set index buffer
  //m_deviceContext.m_deviceContext->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
  //
  ////Set primitive topology
  //// Cambia la forma en que se construye la figura según los vértices
  //m_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  //
  //// Create the constant buffers
  //bd.Usage = D3D11_USAGE_DEFAULT;
  //bd.ByteWidth = sizeof(CBNeverChanges);
  ////ConstantBuffer no tiene InitalData
  ////Los buffers de CONSTANT son los 3 de abajo 
  //bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  //bd.CPUAccessFlags = 0;
  ////hr = m_device.m_device->CreateBuffer( &bd, NULL, &m_pCBNeverChanges );
  //hr = m_device.CreateBuffer(&bd, nullptr, &m_pCBNeverChanges);
  //
  //if( FAILED( hr ) )
  //    return hr;
  //
  //bd.ByteWidth = sizeof(CBChangeOnResize);
  ////hr = m_device.m_device->CreateBuffer( &bd, NULL, &m_pCBChangeOnResize );
  //hr = m_device.CreateBuffer(&bd, nullptr, &m_pCBChangeOnResize);
//
    //if( FAILED( hr ) )
    //    return hr;
    //
    //bd.ByteWidth = sizeof(CBChangesEveryFrame);
    ////hr = m_device.m_device->CreateBuffer( &bd, NULL, &m_pCBChangesEveryFrame );
    //hr = m_device.CreateBuffer(&bd, nullptr, &m_pCBChangesEveryFrame);
    //if( FAILED( hr ) )
    //    return hr;
    //
    // Load the Texture
    //Cómo lo dice, crea una textura a partir de una imagen cargada
    //Aqui verifica si el valor de retorno es correcto
    //
    //Se usa nuestra variable
    //hr = D3DX11CreateShaderResourceViewFromFile( m_device.m_device, "seafloor.dds", NULL, NULL, &m_pTextureRV, NULL );
    //if( FAILED( hr ) )
    //    return hr;
    //Inizializa cualquier textura desde memopria
    //m_default.init(m_device, "Textures/Default.png", ExtensionType::PNG);   
    //     
    // Create the sample state
    //D3D11_SAMPLER_DESC sampDesc;
    //ZeroMemory( &sampDesc, sizeof(sampDesc) );
    //sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    //sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    //sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    //sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    //sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    //sampDesc.MinLOD = 0;
    //sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    //Es una vinculación entre los recursos que se usan en texturas y cómo quiero que se usen
    //hr = m_device.m_device->CreateSamplerState( &sampDesc, &m_pSamplerLinear );
    //CreateSampleState se necarga de gestionar cómo las textures van a ser procesadas
    //hr = m_device.CreateSamplerState(&sampDesc, &m_pSamplerLinear);
    //if( FAILED( hr ) )
    //    return hr;
  m_sampler.init(m_device);
  // Initialize the world matrices
  //m_World = XMMatrixIdentity();

  // Initialize the view matrix
  XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
  XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  m_View = XMMatrixLookAtLH(Eye, At, Up);


  cbNeverChanges.mView = XMMatrixTranspose(m_View);
  //Se comenta y se sustituye por las de nuestra calse buffer 
  //m_deviceContext.m_deviceContext->UpdateSubresource( m_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );
  //
  // Initialize the projection matrix
  //Se ajustan las variables por las nuetras 
  m_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
    m_window.m_width /* */ / (FLOAT)m_window.m_height /* */,
    0.01f,
    100.0f);

  cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
  //m_deviceContext.m_deviceContext->UpdateSubresource( m_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );

  //Set vela Actor
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

  //Set grid Actor

  AGrid = EngineUtilities::MakeShared<Actor>(m_device);
  if (!AGrid.isNull())
  {
    std::vector<MeshComponent> gridMesh;
    gridMesh.push_back(MC);
    AGrid->setMesh(m_device, gridMesh);
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

  //initialize Classes
  m_UserInterface.init(m_window.m_hWnd, m_device.m_device, m_deviceContext.m_deviceContext);

  return S_OK;
}

void BaseApp::update()
{
  m_UserInterface.update();
  bool show_demo_window = true;
  ImGui::ShowDemoWindow(&show_demo_window);
  //ImGui::Begin("Test");

  //ImGui::End();

  m_CBBufferNeverChanges.update(m_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
  m_CBBufferChangeOnResize.update(m_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

  AVela->update(0, m_deviceContext);
  AGrid->update(0, m_deviceContext);
  //Rotate cube around the origin
  //XMVECTOR translation = XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f); // Traslación en x=1, y=2, z=3
  //XMVECTOR rotation = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(260), XMConvertToRadians(DeltaTime * 50), 0.0f); // Rotación en X=180, Y=180, Z=0
  //XMVECTOR scale = XMVectorSet(.03f, .03f, .03f, 0.0f); // Escala por 2 en x, y, z
  // Combinar las transformaciones en una matriz de mundo
  //m_World = XMMatrixScalingFromVector(scale) * XMMatrixRotationQuaternion(rotation) * XMMatrixTranslationFromVector(translation);
  // Rotate cube around the origin
  //m_World = XMMatrixRotationZ(DeltaTime);
  // Modify the color
  //Update Constant Buffers
  //cb.mWorld = XMMatrixTranspose(m_World);
  //cb.vMeshColor = m_vMeshColor;
  //m_CBBufferChangesEveryFrame.update(m_deviceContext, 0, nullptr, &cb, 0, 0);
 /* m_vMeshColor.x = (sinf(DeltaTime * 1.0f) + 1.0f) * 0.5f;
  m_vMeshColor.y = (cosf(DeltaTime * 3.0f) + 1.0f) * 0.5f;
  m_vMeshColor.z = (sinf(DeltaTime * 5.0f) + 1.0f) * 0.5f;*/
}

void BaseApp::render()
{

  //
  // Clear the back buffer
  //
  float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
  m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, ClearColor);

  m_viewport.render(m_deviceContext);
  //Esto va en el render, y se pasó a la clase del mismo 
  //m_deviceContext.m_deviceContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
  //"ClearColor" es el color del fondo
  //Device genera los recursos, no los usa 
  //DeviceContext establece o setea los recursos que se presentan en pantalla 

  // Clear the depth buffer to 1.0 (max depth)

  /*m_pDepthStencilView Limpia el BackBuffer para que luego SwapChain presente el nuevo buffer en pantalla*/
  m_depthStencilView.render(m_deviceContext);

  m_shaderProgram.render(m_deviceContext);

  AVela->render(m_deviceContext);
  AGrid->render(m_deviceContext);

  // Update variables that change once per frame
  //
  //Se sustituye por la nuestra
  //m_deviceContext.m_deviceContext->UpdateSubresource( m_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );
  //
  //
  // Render the cube
  //Se pone nuestro render del InputLayout
  // Se comentan pues tenemos el ShaderProgram
  //m_inputLayout.render(m_deviceContext);
  //m_deviceContext.m_deviceContext->VSSetShader( m_pVertexShader, NULL, 0 );
  //m_deviceContext.m_deviceContext->PSSetShader( m_pPixelShader, NULL, 0 );
  //Se sustituyen por las nuestras 
  //m_deviceContext.m_deviceContext->VSSetConstantBuffers( 0, 1, &m_pCBNeverChanges );
  //m_deviceContext.m_deviceContext->VSSetConstantBuffers( 1, 1, &m_pCBChangeOnResize );
  //m_deviceContext.m_deviceContext->VSSetConstantBuffers( 2, 1, &m_pCBChangesEveryFrame );
  //m_vertexBuffers.render(m_deviceContext, 0, 1);
  //m_indexBuffers.render(m_deviceContext, DXGI_FORMAT_R32_UINT);
  // //Render los models
  //for (size_t i = 0; i < m_model.meshes.size(); i++)
  //{
  //    m_vertexBuffers[i].render(m_deviceContext, 0, 1);
  //    m_indexBuffers[i].render(m_deviceContext, DXGI_FORMAT_R32_UINT);
  //    if (i <= modelTextures.size() - 1)
  //    {
  //        modelTextures[i].render(m_deviceContext, 0, 1);
  //    }
  //    else
  //    {
  //        m_default.render(m_deviceContext, 0, 1);
  //    }
  //    
  //    m_sampler.render(m_deviceContext, 0, 1);
      //m_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
      //m_deviceContext.m_deviceContext->DrawIndexed(m_model.meshes[i].m_numIndex, 0, 0);
  //}
  //m_CBBufferChangesEveryFrame.renderModel(m_deviceContext, 2, 1); // Slot 2
      //Set primitve topology
      // 
  //m_CBBufferNeverChanges.render(m_deviceContext, 0, 1); // Slot 0
  //m_CBBufferChangeOnResize.render(m_deviceContext, 1, 1); // Slot 1
  //m_CBBufferChangesEveryFrame.renderModel(m_deviceContext, 2, 1); // Slot 2
  ////
  ////m_deviceContext.m_deviceContext->PSSetConstantBuffers( 2, 1, &m_pCBChangesEveryFrame );
  ////Se usa nuestra variable
  ////m_deviceContext.m_deviceContext->PSSetShaderResources( 0, 1, &m_pTextureRV );
  //m_modelTexture.render(m_deviceContext, 0, 1);
  //m_sampler.render(m_deviceContext, 0, 1);
  ////m_deviceContext.m_deviceContext->PSSetSamplers( 0, 1, &m_pSamplerLinear );
  ////
  ////Set primitive Topology
  //m_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  //m_deviceContext.m_deviceContext->DrawIndexed( m_mesh.numIndex, 0, 0 );
  //
  //
  // Present our back buffer to our front buffer
  //
  //m_pSwapChain->Present( 0, 0 );

  //Actualiza los buffers constante
  m_CBBufferNeverChanges.render(m_deviceContext, 0, 1); // Slot 0
  m_CBBufferChangeOnResize.render(m_deviceContext, 1, 1); // Slot 1

  m_UserInterface.render();
  m_swapchain.present();
}

void BaseApp::destroy()
{
  if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->ClearState();

  AVela->destroy();
  AGrid->destroy();

  //if( m_pSamplerLinear ) m_pSamplerLinear->Release();
  //m_sampler.destroy();
  //for (auto& tex : modelTextures)
  //{
  //    tex.destroy();
  //}
  //m_modelTexture.destroy();
  //if( m_pTextureRV ) m_pTextureRV->Release();
  //Se sustituyen por las nuestras
  //if( m_pCBNeverChanges ) m_pCBNeverChanges->Release();
  //if( m_pCBChangeOnResize ) m_pCBChangeOnResize->Release();
  //if( m_pCBChangesEveryFrame ) m_pCBChangesEveryFrame->Release();
  //if( m_pVertexBuffer ) m_pVertexBuffer->Release();
  //if( m_pIndexBuffer ) m_pIndexBuffer->Release();
  //if( m_pVertexLayout ) m_pVertexLayout->Release();
  //m_default.destroy();

  m_CBBufferNeverChanges.destroy();
  m_CBBufferChangeOnResize.destroy();


  //m_CBBufferChangesEveryFrame.destroy();
  //for (auto& vertexBuffer : m_vertexBuffers)
  //{
  //    vertexBuffer.destroy();
  //}
  //for (auto& indexBuffer : m_indexBuffers)
  //{
  //    indexBuffer.destroy();
  //}

  m_shaderProgram.destroy();
  //m_vertexBuffers.destroy();
  //m_indexBuffers.destroy();
  //Se sustituye por nuestro Destroy
  //m_inputLayout.destroy();
  //if( m_pVertexShader ) m_pVertexShader->Release();
  //if( m_pPixelShader ) m_pPixelShader->Release();
  //if( m_pDepthStencil ) m_pDepthStencil->Release();
  //Se sustituye por el nuestro
  m_depthStencil.destroy();
  //if( m_pDepthStencilView ) m_pDepthStencilView->Release();
  m_depthStencilView.destroy();
  //Aquí se liberan recursos
  m_renderTargetView.destroy();
  //if( m_pRenderTargetView ) m_pRenderTargetView->Release();
  //if( m_pSwapChain ) m_pSwapChain->Release();
  //Pa' la liberación de memoria
  m_swapchain.destroy();
  //if( m_deviceContext.m_deviceContext ) m_deviceContext.m_deviceContext->Release();
  //Cambiamos esto por nuestra función que libera m_deviceContext
  m_deviceContext.destroy();
  //Libera la información con nuestro método personalizado
  m_device.destroy();
  //if( m_device.m_device ) m_device.m_device->Release();
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

//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Se pone el contenido que està en el engine.cpp
//LRESULT CALLBACK BaseApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    //PAINTSTRUCT ps;
//    //HDC hdc;
//    //switch (message)
//    //{
//    //case WM_PAINT:
//    //    hdc = BeginPaint(hWnd, &ps);
//    //    EndPaint(hWnd, &ps);
//    //    break;
//    //case WM_DESTROY:
//    //    PostQuitMessage(0);
//    //    break;
//    //default:
//    //    return DefWindowProc(hWnd, message, wParam, lParam);
//    //}
//    //return 0;
//
//  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
//    return true;
//
//  PAINTSTRUCT ps;
//  HDC hdc;
//
//  switch (message)
//  {
//  case WM_PAINT:
//    hdc = BeginPaint(hWnd, &ps);
//    EndPaint(hWnd, &ps);
//    break;
//
//  case WM_DESTROY:
//    PostQuitMessage(0);
//    break;
//
//  default:
//    return DefWindowProc(hWnd, message, wParam, lParam);
//  }
//
//  return 0;
//}

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
