#include "RenderTargetView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "DepthStencilView.h"

// Comprueba que los recuersos estén inicializados
void RenderTargetView::
init(Device device, 
		 Texture backBuffer, 
		 DXGI_FORMAT Format)
{
	if (device.m_device == nullptr) {
		ERROR("RenderTargetView", "init", "CHECK FOR Device device")
			exit(1);
	}
	else if (backBuffer.m_texture == nullptr) {
		ERROR("RenderTargetView", "init", "CHECK FOR Texture backBuffer")
			exit(1);
	}

	//Valida que los recursos se validen correctamente
	HRESULT hr = S_OK;
	
	//Este descritor es la parte que había em el nullptr
	//Se usa este renderTrget para una venta en la interfaz de usuario
	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = Format;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = device.CreateRenderTargetView(backBuffer.m_texture,
		&desc,
		&m_renderTargetView);
	
	//Se define el mensaje de error en caso de que falle el RenderTrgetView
	if (FAILED(hr)) {
		ERROR("RenderTargetView", "init", "CHECK FOR CreateRenderTargetView()")
			exit(1);
	}
}

void RenderTargetView::
update()
{
}

void RenderTargetView::
render(DeviceContext& deviceContext, 
			 DepthStencilView& depthStencilView, 
			 unsigned int numViews, 
			 float ClearColor[4])
{
	deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
	deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &m_renderTargetView, depthStencilView.m_pDepthStencilView);
}

void RenderTargetView::
destroy()
{
	SAFE_RELEASE(m_renderTargetView);
}
