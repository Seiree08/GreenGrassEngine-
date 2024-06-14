#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"


void DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format)
{
    if (device.m_device == nullptr)
    {
        ERROR("DepthStencilView", "init", "CHECK FOR Device device");
        exit(1);
    }
    else if (depthStencil.m_texture == nullptr)
    {
        ERROR("DepthStencilView", "init", "CHECK FOR IDED11Resource* depthStencil");
        exit(1);
    }
    HRESULT hr = S_OK;
    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;

    device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_pDepthStencilView);

    if (FAILED(hr))
    {
        ERROR("DepthStencilView", "init", "CHECK FOR CreateDepthStencilView()");
        exit(1);
    }
}

void DepthStencilView::render(DeviceContext& deviceContext)
{
	deviceContext.m_deviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//Se usa nuestra variable del parámetro el lugar de las variables del mismo
}

//Se liberan los recursos y la variable es la que está en el destroy
void DepthStencilView::destroy()
{
    SAFE_RELEASE(m_pDepthStencilView);
}
