//--------------------------------------------------------------------------------------
// File: GreenGrassEngine.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "PreRequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "SwapChain.h"
#include "DepthStencilView.h"
#include "RenderTargetView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "ModelLoader.h"
#include "fbxsdk.h"
//
//#include "InputLayout.h"
 
//--------------------------------------------------------------------------------------
// Estas Structures se llevaron a "PreRequisites"
//--------------------------------------------------------------------------------------
//struct SimpleVertex
//{
//    XMFLOAT3 Pos;
//    XMFLOAT2 Tex;
//};
//
//struct CBNeverChanges
//{
//    XMMATRIX mView;
//};
//
//struct CBChangeOnResize
//{
//    XMMATRIX mProjection;
//};
//
//struct CBChangesEveryFrame
//{
//    XMMATRIX mWorld;
//    XMFLOAT4 vMeshColor;
//};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
//Estas variables se comentan y se declaran las nuestras debajo
//HINSTANCE                           g_hInst = NULL;
//HWND                                g_hWnd = NULL;
//D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
//D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
//ID3D11Device*                       g_device.m_device = NULL;
//ID3D11DeviceContext*                g_deviceContext.m_deviceContext = NULL;
//IDXGISwapChain*                     g_pSwapChain = NULL;
//ID3D11Texture2D*                    g_pDepthStencil = NULL;
//ID3D11DepthStencilView*             g_pDepthStencilView = NULL;   
//ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
//ID3D11InputLayout*                  g_pVertexLayout = NULL;
//ID3D11VertexShader*                 g_pVertexShader = NULL;
//ID3D11PixelShader*                  g_pPixelShader = NULL;
//ID3D11ShaderResourceView*           g_pTextureRV = NULL;
//ID3D11SamplerState*                 g_pSamplerLinear = NULL;
//Esta variable ya no se ocupa (ShaderProgram) y la comentamos auqneu la pusimos previamente
//InputLayout                         g_inputLayout;
// 
//ID3D11Buffer*                       g_pVertexBuffer = NULL;
//ID3D11Buffer*                       g_pIndexBuffer = NULL;
//ID3D11Buffer*                       g_pCBNeverChanges = NULL;
//ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
//ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;

//Son nuestras variables personalizadas
Window                              g_window;
Device                              g_device;
DeviceContext                       g_deviceContext;
SwapChain                           g_swapchain;
Texture                             g_backBuffer;
Texture                             g_depthStencil;
DepthStencilView                    g_depthStencilView;
RenderTargetView                    g_renderTargetView;
Viewport                            g_viewport;
ShaderProgram                       g_shaderProgram;
//Buffer                              g_vertexBuffer;
std::vector<Buffer>                 g_vertexBuffers;
//Buffer                              g_indexBuffer;
std::vector<Buffer>                 g_indexBuffers;
Buffer                              g_CBBufferNeverChanges;         /*vista de cámara*/
Buffer                              g_CBBufferChangeOnResize;       /*proyección de cámara*/
Buffer                              g_CBBufferChangesEveryFrame;    /*posición y colores del modelo*/
Texture                             g_modelTexture;
SamplerState                        g_sampler;
ModelLoader                         g_model;
/*---------------------------------------------------------------------------------------*/
XMMATRIX                            g_World; 
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

//Se crea una  clase mesh 
Mesh                                g_mesh;

Texture g_default;

std::vector<Texture> modelTextures;

CBNeverChanges cbNeverChanges;
CBChangeOnResize cbChangesOnResize;
CBChangesEveryFrame cb;

//CBChangesEveryFrame cb;
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
//HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();
void Update(float DeltaTime);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------

//Los parámetros de aquí se vinculan con la inicialización del programa
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    //baseapp.run();
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED(g_window.init( hInstance, nCmdShow, WndProc) ) ) /*Se sustituye por nuestro objeto pa' acceder al init y se agreda en WndProc*/
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // Update our time
            static float t = 0.0f;
            if (g_swapchain.m_driverType == D3D_DRIVER_TYPE_REFERENCE)
            {
                t += (float)XM_PI * 0.0125f;
            }
            else
            {
                static DWORD dwTimeStart = 0;
                DWORD dwTimeCur = GetTickCount();
                if (dwTimeStart == 0)
                    dwTimeStart = dwTimeCur;
                t = (dwTimeCur - dwTimeStart) / 1000.0f;
            }
            Update(t);
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
}

/*Se comenta esta función*/

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
//HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
//{
//    // Register class
//    WNDCLASSEX wcex;
//    wcex.cbSize = sizeof( WNDCLASSEX );
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
//    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
//    wcex.lpszMenuName = NULL;
//    wcex.lpszClassName = "TutorialWindowClass";
//    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
//    if( !RegisterClassEx( &wcex ) )
//        return E_FAIL;
//
//    // Create window
//    g_hInst = hInstance;
//    RECT rc = { 0, 0, 640, 480 };
//    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
//    g_hWnd = CreateWindow( "TutorialWindowClass", "Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
//                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
//                           NULL );
//    if( !g_hWnd )
//        return E_FAIL;
//
//    ShowWindow( g_hWnd, nCmdShow );
//
//    return S_OK;
//}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
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
//    sd.BufferDesc.Width = g_window.m_width; /* */
//    sd.BufferDesc.Height = g_window.m_height; /* */
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    sd.OutputWindow = g_window.m_hWnd; /* */
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = TRUE;
//
//    //Se agarra esto y se pada a "SwapChain.cpp"
//    
//    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
//    {
//        g_driverType = driverTypes[driverTypeIndex];
//        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
//                                            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_device.m_device, &g_featureLevel, &g_deviceContext.m_deviceContext );
//        if( SUCCEEDED( hr ) )
//            break;
//    }
//    if( FAILED( hr ) )
//        return hr;

    // Create a render target view
    // ESTO SE COMENTA PORQUE EL BACKBUFEFR SE MANEJA DESDE EL SWAPCHAIN
    //ID3D11Texture2D* pBackBuffer = NULL;
    //hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    //if( FAILED( hr ) )
    //    return hr;

    g_swapchain.init(g_device, g_deviceContext, g_backBuffer, g_window);
    
    //Create a render target view a partir de nuestras variables 
    //eL DXGI es parte del formato de la textura
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    //Se comenta pues ya no se ocupa el release
    //g_device.CreateRenderTargetView(g_backBuffer.m_texture, nullptr, &g_pRenderTargetView);
    //hr = g_device.m_device->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
    //g_backBuffer.m_texture->Release(); /*Luego va a ser el destroy de la textura*/
    //if( FAILED( hr ) )
    //    return hr;
//
    // Create depth stencil texture
    //Agregamos nuestra función de init
    g_depthStencil.init(g_device, g_window.m_width, g_window.m_height, DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_BIND_DEPTH_STENCIL);

    //Se ajustan las variables por las nuetras 
    //D3D11_TEXTURE2D_DESC descDepth;
    //ZeroMemory( &descDepth, sizeof(descDepth) );
    //descDepth.Width = g_window.m_width; /* */
    //descDepth.Height = g_window.m_height; /* */
    //descDepth.MipLevels = 1;
    //descDepth.ArraySize = 1;
    //descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    //descDepth.SampleDesc.Count = 1;
    //descDepth.SampleDesc.Quality = 0;
    //descDepth.Usage = D3D11_USAGE_DEFAULT;
    //descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    //descDepth.CPUAccessFlags = 0;
    //descDepth.MiscFlags = 0;
    //g_device.CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
    //Se cambia la forma de crear la textura con nuestras variables
    //hr = g_device.m_device->CreateTexture2D( &descDepth, NULL, &g_pDepthStencil );
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
    //g_device.CreateDepthStencilView(g_depthStencil.m_texture, &descDSV, &g_pDepthStencilView);
    //  
    //Se cambia por nuestras variables
    //hr = g_device.m_device->CreateDepthStencilView( g_pDepthStencil, &descDSV, &g_pDepthStencilView );
    //if( FAILED( hr ) )
     //   return hr;

    g_depthStencilView.init(g_device, g_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);

    // Setup the viewport
    //Se ajustan las variables por las nuetras 
    //Se comenta pues ya lo implementamos en la clase "Viewport"
    //y llamamos a nuestra función de la clase viewport
    g_viewport.init(g_window);
    //D3D11_VIEWPORT vp;
    //vp.Width = (FLOAT)g_window.m_width; /* */
    //vp.Height = (FLOAT)g_window.m_height; /* */
    //vp.MinDepth = 0.0f;
    //vp.MaxDepth = 1.0f;
    //vp.TopLeftX = 0;
    //vp.TopLeftY = 0;
    //g_deviceContext.m_deviceContext->RSSetViewports( 1, &vp );

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
    //// hr = g_device.m_device->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
    ////Se sustituye el mpetodo por nuestras variables
    //hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
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
    g_shaderProgram.init(g_device, "GreenGrassEngine.fx", Layout);
    
    //Load Model
    g_model.LoadModel("Models/Vela2.fbx");

    for (auto& mesh : g_model.meshes)
    {
        //Create Vertex Buffer
        Buffer vertexBuffer;
        vertexBuffer.init(g_device, mesh, D3D11_BIND_VERTEX_BUFFER);
        g_vertexBuffers.push_back(vertexBuffer);

        // // Create index buffer
        Buffer indexBuffer;
        indexBuffer.init(g_device, mesh, D3D11_BIND_INDEX_BUFFER);
        g_indexBuffers.push_back(indexBuffer);
    }
    //YA NO SE OCUPA PORQUE SE USA EN EL FOR DE ARRIBA
    //int size = g_model.GetVertices().size();
    //Se comenta y se sustituye por g_ShaderProgram
    //g_inputLayout.init(g_device, Layout, pVSBlob);
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
    //hr = g_device.m_device->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout );
    //layout: es la estructura de datos a mandar a revisar del shader
    //numElements: es el tamaño del arreglo
    //pVSBlob: es la referecncia al VertexShader
    //Se comenta y se sustituye por nuestro init
    //hr = g_device.CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &g_pVertexLayout);
//
    //SE COMENTA PUES SE IMPLEMENTA EN "SHADERPROGRAM"
    //g_inputLayout.init(g_device, Layout, pVSBlob);
    //pVSBlob->Release();
    ////if( FAILED( hr ) )
    ////    return hr;
//
    //// Set the input layout
    ////g_deviceContext.m_deviceContext->IASetInputLayout( g_pVertexLayout );
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
    ////hr = g_device.m_device->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
    //hr = g_device.CreatePixelShader(pPSBlob->GetBufferPointer(), 
    //                                pPSBlob->GetBufferSize(), 
    //                                nullptr, 
    //                                &g_pPixelShader);
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
    //g_mesh.name = "Vela";
    //g_mesh.vertex = g_model.GetVertices();
//
    ////Guarda la información de los vértices
    ////for (const SimpleVertex& vertex : vertices)
    ////{
    ////    g_mesh.vertex.push_back(vertex);
    ////} 
    ////
    ////NOTA: El static_cast<unsigned int> se está utilizando aquí para convertir
    ////el resultado del método size() de un std::vector a un tipo unsigned int.
    ////El método size() devuelve un valor del tipo std::size_t, que es un tipo
    ////específico de tamaño no negativo. En algunas plataformas, std::size_t puede
    ////ser de un tamaño diferente a unsigned int.
    ////Se almacena el tamaño de vétices 
    //g_mesh.numVertex = static_cast<unsigned int>(g_mesh.vertex.size());
//
    ////Se incializa el buffer con la bandera de vertex buffer
    //g_vertexBuffer.init(g_device, g_mesh, D3D11_BIND_VERTEX_BUFFER);
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
    //////hr = g_device.m_device->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
    //////este bufer tiene InitialData
    //////este es el buffer del VertexShader
    ////hr = g_device.CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
    ////if( FAILED( hr ) )
    ////    return hr;
    ////
    ////// Set vertex buffer
    ////UINT stride = sizeof( SimpleVertex );
    ////UINT offset = 0;
    ////g_deviceContext.m_deviceContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );
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
    ////    g_mesh.index.push_back(index);
    ////}
//
    //g_mesh.index= g_model.GetIndices();
//
    //g_mesh.numIndex = static_cast<unsigned int>(g_mesh.index.size());
//
    //g_indexBuffer.init(g_device, g_mesh, D3D11_BIND_INDEX_BUFFER);

    // Inicialización de Constant Buffers
    g_CBBufferNeverChanges.init(g_device, sizeof(CBNeverChanges));

    g_CBBufferChangeOnResize.init(g_device, sizeof(CBChangeOnResize));

    g_CBBufferChangesEveryFrame.init(g_device, sizeof(CBChangesEveryFrame));

    Texture Vela_Char_BaseColor;
    Vela_Char_BaseColor.init(g_device, "Textures/Vela/Vela_Char_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Corneas_BaseColor;
    Vela_Corneas_BaseColor.init(g_device, "Textures/Vela/Vela_Corneas_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Gun_BaseColor;
    Vela_Gun_BaseColor.init(g_device, "Textures/Vela/Vela_Gun_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Legs_BaseColor;
    Vela_Legs_BaseColor.init(g_device, "Textures/Vela/Vela_Legs_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Mechanical_BaseColor;
    Vela_Mechanical_BaseColor.init(g_device, "Textures/Vela/Vela_Mechanical_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Plate_BaseColor;
    Vela_Plate_BaseColor.init(g_device, "Textures/Vela/Vela_Plate_BaseColor.png", ExtensionType::PNG);

    Texture Vela_Visor_BaseColor;
    Vela_Visor_BaseColor.init(g_device, "Textures/Vela/Vela_Visor_BaseColor.png", ExtensionType::PNG);

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
    ////hr = g_device.m_device->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );
    ////este bufer tiene InitialData
    ////este es el buffer del IndexShader
    //hr = g_device.CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
    //
    //if( FAILED( hr ) )
    //    return hr;
    //
    //// Set index buffer
    //g_deviceContext.m_deviceContext->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
    //
    ////Set primitive topology
    //// Cambia la forma en que se construye la figura según los vértices
    //g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //
    //// Create the constant buffers
    //bd.Usage = D3D11_USAGE_DEFAULT;
    //bd.ByteWidth = sizeof(CBNeverChanges);
    ////ConstantBuffer no tiene InitalData
    ////Los buffers de CONSTANT son los 3 de abajo 
    //bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    //bd.CPUAccessFlags = 0;
    ////hr = g_device.m_device->CreateBuffer( &bd, NULL, &g_pCBNeverChanges );
    //hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
    //
    //if( FAILED( hr ) )
    //    return hr;
    //
    //bd.ByteWidth = sizeof(CBChangeOnResize);
    ////hr = g_device.m_device->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );
    //hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
//
    //if( FAILED( hr ) )
    //    return hr;
    //
    //bd.ByteWidth = sizeof(CBChangesEveryFrame);
    ////hr = g_device.m_device->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );
    //hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
    //if( FAILED( hr ) )
    //    return hr;
    //
    // Load the Texture
    //Cómo lo dice, crea una textura a partir de una imagen cargada
    //Aqui verifica si el valor de retorno es correcto
    //
    //Se usa nuestra variable
    //hr = D3DX11CreateShaderResourceViewFromFile( g_device.m_device, "seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
    //if( FAILED( hr ) )
    //    return hr;
    //Inizializa cualquier textura desde memopria
    //g_default.init(g_device, "Textures/Default.png", ExtensionType::PNG);   
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
    //hr = g_device.m_device->CreateSamplerState( &sampDesc, &g_pSamplerLinear );
    //CreateSampleState se necarga de gestionar cómo las textures van a ser procesadas
    //hr = g_device.CreateSamplerState(&sampDesc, &g_pSamplerLinear);
    //if( FAILED( hr ) )
    //    return hr;
    g_sampler.init(g_device);
    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
    XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
    g_View = XMMatrixLookAtLH( Eye, At, Up );


    cbNeverChanges.mView = XMMatrixTranspose( g_View );
    //Se comenta y se sustituye por las de nuestra calse buffer 
    //g_deviceContext.m_deviceContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );
    //
    // Initialize the projection matrix
    //Se ajustan las variables por las nuetras 
    g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4, g_window.m_width /* */ / (FLOAT)g_window.m_height /* */, 0.01f, 100.0f);
    
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
    //g_deviceContext.m_deviceContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    if( g_deviceContext.m_deviceContext ) g_deviceContext.m_deviceContext->ClearState();

    //if( g_pSamplerLinear ) g_pSamplerLinear->Release();
    g_sampler.destroy();
    for (auto& tex : modelTextures)
    {
        tex.destroy();
    }
    //g_modelTexture.destroy();
    //if( g_pTextureRV ) g_pTextureRV->Release();
    //Se sustituyen por las nuestras
    //if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
    //if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
    //if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
    //if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    //if( g_pIndexBuffer ) g_pIndexBuffer->Release();
    //if( g_pVertexLayout ) g_pVertexLayout->Release();
    g_default.destroy();
    g_CBBufferNeverChanges.destroy();
    g_CBBufferChangeOnResize.destroy();
    g_CBBufferChangesEveryFrame.destroy();

    for (auto& vertexBuffer : g_vertexBuffers)
    {
        vertexBuffer.destroy();
    }
    for (auto& indexBuffer : g_indexBuffers)
    {
        indexBuffer.destroy();
    }

    g_shaderProgram.destroy();
    //g_vertexBuffers.destroy();
    //g_indexBuffers.destroy();
    //Se sustituye por nuestro Destroy
    //g_inputLayout.destroy();
    //if( g_pVertexShader ) g_pVertexShader->Release();
    //if( g_pPixelShader ) g_pPixelShader->Release();
    //if( g_pDepthStencil ) g_pDepthStencil->Release();
    //Se sustituye por el nuestro
    g_depthStencil.destroy();
    //if( g_pDepthStencilView ) g_pDepthStencilView->Release();
    g_depthStencilView.destroy();
    //Aquí se liberan recursos
    g_renderTargetView.destroy();
    //if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    //if( g_pSwapChain ) g_pSwapChain->Release();
    //Pa' la liberación de memoria
    g_swapchain.destroy();
    //if( g_deviceContext.m_deviceContext ) g_deviceContext.m_deviceContext->Release();
    //Cambiamos esto por nuestra función que libera m_deviceContext
    g_deviceContext.destroy();
    //Libera la información con nuestro método personalizado
    g_device.destroy();
    //if( g_device.m_device ) g_device.m_device->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

//Update every frame, recibe actualizaciones lógicas
void Update(float DeltaTime)
{
    // Rotate cube around the origin
    XMVECTOR translation = XMVectorSet(0.0f, -2.0f, 0.0f, 0.0f); // Traslación en x=1, y=2, z=3
    XMVECTOR rotation = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(260), XMConvertToRadians(DeltaTime * 50), 0.0f); // Rotación en X=180, Y=180, Z=0
    XMVECTOR scale = XMVectorSet(.03f, .03f, .03f, 0.0f); // Escala por 2 en x, y, z

    // Combinar las transformaciones en una matriz de mundo
    g_World = XMMatrixScalingFromVector(scale) * XMMatrixRotationQuaternion(rotation) * XMMatrixTranslationFromVector(translation);
    // Rotate cube around the origin

    //g_World = XMMatrixRotationZ(DeltaTime);
    // Modify the color
   /* g_vMeshColor.x = (sinf(DeltaTime * 1.0f) + 1.0f) * 0.5f;
    g_vMeshColor.y = (cosf(DeltaTime * 3.0f) + 1.0f) * 0.5f;
    g_vMeshColor.z = (sinf(DeltaTime * 5.0f) + 1.0f) * 0.5f;*/
    //Update Constant Buffers
    g_CBBufferNeverChanges.update(g_deviceContext, 0, nullptr, &cbNeverChanges, 0, 0);
    g_CBBufferChangeOnResize.update(g_deviceContext, 0, nullptr, &cbChangesOnResize, 0, 0);

    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    g_CBBufferChangesEveryFrame.update(g_deviceContext, 0, nullptr, &cb, 0, 0);
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_renderTargetView.render(g_deviceContext, g_depthStencilView, 1, ClearColor);
    
    g_viewport.render(g_deviceContext);
    //Esto va en el render, y se pasó a la clase del mismo 
    //g_deviceContext.m_deviceContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );
    //"ClearColor" es el color del fondo
    //Device genera los recursos, no los usa 
    //DeviceContext establece o setea los recursos que se presentan en pantalla 

    // Clear the depth buffer to 1.0 (max depth)
    
    /*g_pDepthStencilView Limpia el BackBuffer para que luego SwapChain presente el nuevo buffer en pantalla*/
    g_depthStencilView.render(g_deviceContext); 

    g_shaderProgram.render(g_deviceContext);
    // Update variables that change once per frame
    //
    //Se sustituye por la nuestra
    //g_deviceContext.m_deviceContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );
    //
    //
    // Render the cube
    //Se pone nuestro render del InputLayout
    // Se comentan pues tenemos el ShaderProgram
    //g_inputLayout.render(g_deviceContext);
    //g_deviceContext.m_deviceContext->VSSetShader( g_pVertexShader, NULL, 0 );
    //g_deviceContext.m_deviceContext->PSSetShader( g_pPixelShader, NULL, 0 );
    //Se sustituyen por las nuestras 
    //g_deviceContext.m_deviceContext->VSSetConstantBuffers( 0, 1, &g_pCBNeverChanges );
    //g_deviceContext.m_deviceContext->VSSetConstantBuffers( 1, 1, &g_pCBChangeOnResize );
    //g_deviceContext.m_deviceContext->VSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
    //g_vertexBuffers.render(g_deviceContext, 0, 1);
    //g_indexBuffers.render(g_deviceContext, DXGI_FORMAT_R32_UINT);

     //Render los models
    for (size_t i = 0; i < g_model.meshes.size(); i++)
    {
        g_vertexBuffers[i].render(g_deviceContext, 0, 1);
        g_indexBuffers[i].render(g_deviceContext, DXGI_FORMAT_R32_UINT);
        if (i <= modelTextures.size() - 1)
        {
            modelTextures[i].render(g_deviceContext, 0, 1);
        }
        else
        {
            g_default.render(g_deviceContext, 0, 1);
        }
        
        g_sampler.render(g_deviceContext, 0, 1);

        //Actualiza los buffers constante
        g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
        g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
        g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
        //Set primitve topology

        g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        g_deviceContext.m_deviceContext->DrawIndexed(g_model.meshes[i].numIndex, 0, 0);
    }

    //g_CBBufferNeverChanges.render(g_deviceContext, 0, 1); // Slot 0
    //g_CBBufferChangeOnResize.render(g_deviceContext, 1, 1); // Slot 1
    //g_CBBufferChangesEveryFrame.renderModel(g_deviceContext, 2, 1); // Slot 2
    ////
    ////g_deviceContext.m_deviceContext->PSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
    ////Se usa nuestra variable
    ////g_deviceContext.m_deviceContext->PSSetShaderResources( 0, 1, &g_pTextureRV );
    //g_modelTexture.render(g_deviceContext, 0, 1);
    //g_sampler.render(g_deviceContext, 0, 1);
    ////g_deviceContext.m_deviceContext->PSSetSamplers( 0, 1, &g_pSamplerLinear );
    ////
    ////Set primitive Topology
    //g_deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //g_deviceContext.m_deviceContext->DrawIndexed( g_mesh.numIndex, 0, 0 );
    //
    //
    // Present our back buffer to our front buffer
    //
    //g_pSwapChain->Present( 0, 0 );
    g_swapchain.present();
}