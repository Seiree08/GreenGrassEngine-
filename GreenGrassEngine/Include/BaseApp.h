//Se incluyen las dependencias necesarias que son nuestros headers
#pragma once
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
#include "Actor.h"
#include "UserInterface.h"

class BaseApp
{
public:
  /// <summary>
  /// Son el contructor y destructor de la clase
  /// </summary>
  BaseApp() = default;
  ~BaseApp() = default;

    /// <summary>
    /// Inicializa todos los recursoso de la app
    /// </summary>
    /// <returns></returns>
    HRESULT 
    init();

    /// <summary>
    /// Actualiza la l�gica de la aplicaci�n, c�lculos matem�ticos
    /// </summary>
    void 
    update();

    /// <summary>
    /// Se ejcutan llamadas para dibujar objetos en pantalla
    /// </summary>
    void 
    render();
    
    /// <summary>
    /// Libera los recursos usados por la aplicaci�n
    /// </summary>
    void 
    destroy();

    /// <summary>
    /// Maneja el ciclo principal de la aplicaci�n, actualizando y renderizando 
    /// mientras procesa mensajes de Windows.
    /// </summary>
    /// <param name="hInstance">: Se usa principalmente para cargar recursos c�mo �conos, 
    /// men�s, crear ventanas</param>
    /// <param name="hPrevInstance">: Verifica si hay otra instancia de la app
    ///   ejecut�ndose</param>
    /// <param name="lpCmdLine">: Es un puntero a una cadena de caracteres 
    ///   (se pasa como una s�la cadena de texto)</param>
    /// <param name="nCmdShow">: Indica c�mo se va a mostrar la pantalla al 
    /// iniciar la app</param>
    /// <param name="wndproc"></param>
    /// <returns></returns>
    int 
    run(HINSTANCE hInstance, 
        HINSTANCE hPrevInstance, 
        LPWSTR lpCmdLine, 
        int nCmdShow, 
        WNDPROC wndproc);
    
    /// <summary>
    /// Crea la cuadr�cula que se muestra es escena
    /// </summary>
    /// <param name="width">: Es para el ancho</param>
    /// <param name="depth">: Es para la profundidad</param>
    /// <param name="spacing">: Es para el espaciado de la malla</param>
    void 
      CreateGrid(int width, 
                 int depth, 
                 float spacing);

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
    std::vector<Buffer>                 m_vertexBuffers;
    std::vector<Buffer>                 m_indexBuffers;
    Buffer                              m_CBBufferNeverChanges;         /*vista de c�mara*/
    Buffer                              m_CBBufferChangeOnResize;       /*proyecci�n de c�mara*/
    Texture                             m_modelTexture;
    SamplerState                        m_sampler;
    ModelLoader                         m_model;
    UserInterface                       m_UserInterface;
    /*---------------------------------------------------------------------------------------*/
    XMMATRIX                            m_View;
    XMMATRIX                            m_Projection;
    XMFLOAT4                            m_vMeshColor;

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