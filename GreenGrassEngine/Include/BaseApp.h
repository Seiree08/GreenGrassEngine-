#pragma once
#include "PreRequisites.h" /*Usa las librerías */
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
//#include "fbxsdk.h"
#include "Actor.h"
#include "UserInterface.h"

class BaseApp
{
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT init();
    //void init(); Los recursos se inicializan

    void update();
    //void update(); Toda la lógica matemática se actualiza
    //Todo lo que tenga valores va en el update
    void render();
    //void render(); Toda la lógica gráfica o visual se actualiza
    //Todo lo que tenga ClearRedner o de Set va en render

    void destroy();
    //void destroy(); Toda la lógica  se libera de memoria, todas las clases que tengan info o punteros se liberan de memoria

    int run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc);
    
    //Se define la función de WndProc
    //LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam  );

    void CreateGrid(int width, int depth, float spacing);

private:

    //Son nuestras variables personalizadas
    Window m_window;
    Device                              m_device;
    DeviceContext                       m_deviceContext;
    SwapChain                           m_swapchain;
    Texture                             m_backBuffer;
    Texture                             m_depthStencil;
    DepthStencilView                    m_depthStencilView;
    RenderTargetView                    m_renderTargetView;
    Viewport                            m_viewport;
    ShaderProgram                       m_shaderProgram;
    //Buffer                            m g_vertexBuffer;
    std::vector<Buffer>                 m_vertexBuffers;
    //Buffer                            m g_indexBuffer;
    std::vector<Buffer>                 m_indexBuffers;
    Buffer                              m_CBBufferNeverChanges;         /*vista de cámara*/
    Buffer                              m_CBBufferChangeOnResize;       /*proyección de cámara*/
    //Buffer                            m g_CBBufferChangesEveryFrame;    /*posición y colores del modelo*/
    Texture                             m_modelTexture;
    SamplerState                        m_sampler;
    ModelLoader                         m_model;
    UserInterface                       m_UserInterface;
    /*---------------------------------------------------------------------------------------*/
    XMMATRIX                            m_View;
    XMMATRIX                            m_Projection;
    XMFLOAT4                            m_vMeshColor;

    //std::vector<SimpleVertex> gridVertices;
    //std::vector<unsigned int> gridIndices;
    //Mesh                                g_mesh;

    //Grid Actor
    MeshComponent MC;
    EngineUtilities::TSharedPointer<Actor> AGrid;
    //Vela Actor
    EngineUtilities::TSharedPointer<Actor> AVela;

    Texture m_default;
    std::vector<Texture> modelTextures;
    std::vector<Texture> gridTexts;

    CBNeverChanges cbNeverChanges;
    CBChangeOnResize cbChangesOnResize;
    CBChangesEveryFrame cb;
};