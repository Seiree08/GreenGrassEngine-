#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Window.h"
#include "Texture.h"
#include "SwapChain.h"

void 
SwapChain::init(Device& device, 
                DeviceContext& deviceContext, 
                Texture& backBuffer, 
                Window window)
{
	//Revisar si la ventana existe
	if (window.m_hWnd == nullptr)
	{
		ERROR("Swapchain", "init", "CHECK FOR window window")
			exit(1);
	}

    unsigned int  createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    //Tipos de divers de Direct3D a considerar
    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    unsigned int  numDriverTypes = ARRAYSIZE(driverTypes);

    //Niveles de caracter�sticas de Direct3D a considerar
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    unsigned int  numFeatureLevels = ARRAYSIZE(featureLevels);

    //Configuraci�n de la cadena de intercambio
    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd)); /*Inicializa la estructura con ceros*/
    sd.BufferCount = 1; //N�mero de buffers en la SwapChain
    sd.BufferDesc.Width = window.m_width; //Ancho del buffer
    sd.BufferDesc.Height = window.m_height; //Alto del buffer
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Formato del buffer
    sd.BufferDesc.RefreshRate.Numerator = 60; //Tasa de refresco del bufferN
    sd.BufferDesc.RefreshRate.Denominator = 1;  //Tasa de refresco del bufferD
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Uso del buffer
    sd.OutputWindow = window.m_hWnd; //Ventana que mostrar� el contenido
    sd.SampleDesc.Count = 1; //N�mero de muestras por pixel
    sd.SampleDesc.Quality = 0; //Calidad de la texturas
    sd.Windowed = TRUE; //Modo ventana

    HRESULT hr = S_OK;

    //Crea la cadena de intercambio con diferentes tipos de drivers
    for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr, 
            m_driverType, 
            nullptr, 
            createDeviceFlags, 
            featureLevels, 
            numFeatureLevels,
            D3D11_SDK_VERSION, 
            &sd, 
            &m_swapChain, 
            &device.m_device, 
            &m_featureLevel, 
            &deviceContext.m_deviceContext);

        if (SUCCEEDED(hr))
        {
            break;
        }
    }
    //Si la craci�n falla manda mensaje de error
    if (FAILED(hr))
    {
        ERROR("Swapchain", "init", "CHECK FOR D3D11CreateDeviceAndSwapChain()")
            exit(1);
    }

    // Create a render target view
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.m_texture);

    // Si falla, muestra un error y sale
    if (FAILED(hr))
    {
        ERROR("Swapchain", "init", "CHECK FOR m_swapChain->GetBuffer()")
            exit(1);
    }
}

void 
SwapChain::update()
{
}

void 
SwapChain::render()
{
}
//Se hace SAFE_RELEASE para la libeeraci�n de memoria
void 
SwapChain::destroy()
{
	SAFE_RELEASE(m_swapChain);
}

void 
SwapChain::present()
{
	m_swapChain->Present(0, 0);
}
