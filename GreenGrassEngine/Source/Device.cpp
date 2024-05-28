#include "Device.h"
     
void Device::init()
{
}

void Device::update()
{
}

void Device::render()
{
}

void Device::destroy()
{
    SAFE_RELEASE(m_device);
}

HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pResource != nullptr || ppRTView != nullptr)
    {
        hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);
        MESSAGE("Device", "CreateRenderTarfetView", "OK")
    }
    else
    {
        ERROR("Device", "CreateRenderTargetView", "CHECK FOR CREATION METHOD")
        exit(1);
    }
    return hr;
}

HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
    {
        HRESULT hr = S_OK;
        //Check if the resource and RTView exist
        if (pDesc != nullptr || ppTexture2D != nullptr)
        {
            hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
            MESSAGE("Device", "CreateRenderTarfetView", "OK")
        }
        else
        {
            ERROR("Device", "CreateTexture2D", "CHECK FOR CREATION METHOD")
                exit(1);
        }
        return hr;
    }
}

HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pResource == nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR CreateDepthStencilView METHOD")
        exit(1);
    }
    else if (ppDepthStencilView== nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID2D11DepthStencilView** ppDepthStencilView")
            exit(1);
    }
    else
    {
        hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
        MESSAGE("Device", "CreateRenderTarfetView", "OK")
    }
    return hr;
}

HRESULT Device::CreateVertexShader(const void* pShaderBytecode, unsigned int BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
    HRESULT hr = S_OK;
    //Check if the resource and RTView exist
    if (pShaderBytecode == nullptr)
    {
        ERROR("Device", "CreateVertexShader", "CHECK FOR const void* pShaderBytecode")
            exit(1);
    }
    else if (ppVertexShader == nullptr)
    {
        ERROR("Device", "CreateVertexShader", "CHECK FOR ID2D11VertexShader** ppVertexShader")
            exit(1);
    }
    else
    {
        hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
        MESSAGE("Device", "CreateVertexShader", "OK")
    }
    return hr;
}
