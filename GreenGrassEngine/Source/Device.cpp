//Aqu� se ve si los recursos est�n bien cargados
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
    //Aqu� se incluye en SAFE_RELEASE  
    SAFE_RELEASE(m_device);
}

//Se implementa la funci�n 
HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource, 
    const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
    ID3D11RenderTargetView** ppRTView)
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

//Se implementa la funci�n
HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, 
    const D3D11_SUBRESOURCE_DATA* pInitialData, 
    ID3D11Texture2D** ppTexture2D)
{
    {
        HRESULT hr = S_OK;
        //Check if the resource and CT2D exist
        if (pDesc != nullptr || ppTexture2D != nullptr)
        {
            hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
            MESSAGE("Device", "CreateTexture2D", "OK")
        }
        else
        {
            ERROR("Device", "CreateTexture2D", "CHECK FOR CREATION METHOD")
                exit(1);
        }
        return hr;
    }
}

HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource, 
    const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
    ID3D11DepthStencilView** ppDepthStencilView)
{
    HRESULT hr = S_OK;
    //Check if the resource and CDSView exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
    if (pResource == nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR CreateDepthStencilView METHOD")
        exit(1);
    }
    else if (ppDepthStencilView == nullptr)
    {
        ERROR("Device", "CreateDepthStencilView", "CHECK FOR ID2D11DepthStencilView** ppDepthStencilView")
            exit(1);
    }
    else
    {
        hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
        MESSAGE("Device", "CreateDepthStencilView", "OK")
    }
    return hr;
}

HRESULT Device::CreateVertexShader(const void* pShaderBytecode, 
    unsigned int BytecodeLength, 
    ID3D11ClassLinkage* pClassLinkage, 
    ID3D11VertexShader** ppVertexShader)
{
    HRESULT hr = S_OK;
    //Check if the resource and CVShader exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
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

HRESULT Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 
    unsigned int NumElements, 
    const void* pShaderBytecodeWithInputSignature, 
    unsigned BytecodeLength, 
    ID3D11InputLayout** ppInputLayout)
{
    HRESULT hr = S_OK;
    //Check if the resource and CILayout exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
    if (pInputElementDescs == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs")
        exit(1);
    }
    else if (pShaderBytecodeWithInputSignature == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR const void* pShaderBytecodeWithInputSignature")
        exit(1);
    }
    else if (ppInputLayout == nullptr)
    {
        ERROR("Device", "CreateInputLayout", "CHECK FOR  ID3D11InputLayout** ppInputLayout")
        exit(1);
    }
    else
    {
        hr = m_device->CreateInputLayout(pInputElementDescs,
            NumElements,
            pShaderBytecodeWithInputSignature,
            BytecodeLength,
            ppInputLayout);
        MESSAGE("Device", "CreateInputLayout", "OK")
    }
    return hr;
}

HRESULT Device::CreatePixelShader(const void* pShaderBytecode, 
    unsigned int BytecodeLength, 
    ID3D11ClassLinkage* pClassLinkage, 
    ID3D11PixelShader** ppPixelShader)
{
    HRESULT hr = S_OK;
    //Check if the resource and CPShader exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
    if (pShaderBytecode == nullptr)
    {
        ERROR("Device", "CreatePixelShader", "CHECK FOR const void* pShaderBytecode")
            exit(1);
    }
    else if (ppPixelShader == nullptr)
    {
        ERROR("Device", "CreatePixelShader", "CHECK FOR ID3D11PixelShader** ppPixelShader")
            exit(1);
    }
    else
    {
        hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
        MESSAGE("Device", "CreatePixelShader", "OK")
    }
    return hr;
}

HRESULT Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc/*Revisamos que el bufer tenga info*/,
    const D3D11_SUBRESOURCE_DATA* pInitialData/*Revisa que la info extra sea nulla o no*/,
    ID3D11Buffer** ppBuffer)
{
    HRESULT hr = S_OK;
    //Check if the resource and CB exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
    if (pDesc == nullptr)
    {
        ERROR("Device", "CreateBuffer", "CHECK FOR const D3D11_BUFFER_DESC* pDesc")
            exit(1);
    }
    else if (ppBuffer == nullptr)
    {
        ERROR("Device", "CreateBuffer", "CHECK FOR ID3D11Buffer** ppBuffer")
            exit(1);
    }
    else
    {
        hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);
        MESSAGE("Device", "CreateBuffer", "OK")
    }
    return hr;
}

HRESULT Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
    HRESULT hr = S_OK;
    //Check if the resource and CSState exist
    //Se deben comprobar dos cosas distintas por ello se crean dos mensajes distintos
    if (pSamplerDesc == nullptr)
    {
        ERROR("Device", "CreateSamplerState", "CHECK FOR const D3D11_SAMPLER_DESC* pSamplerDesc")
            exit(1);
    }
    else if (ppSamplerState == nullptr)
    {
        ERROR("Device", "CreateSamplerState", "ID3D11SamplerState** ppSamplerState")
            exit(1);
    }
    else
    {
        hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);
        MESSAGE("Device", "CreateSamplerState", "OK")
    }
    return hr;
}
