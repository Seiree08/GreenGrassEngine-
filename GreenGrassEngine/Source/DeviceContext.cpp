#include "DeviceContext.h"

void DeviceContext::destroy()
{
	SAFE_RELEASE(m_deviceContext);
}

void DeviceContext::RSSetViewports(unsigned int NumViewports, 
								   const D3D11_VIEWPORT* pViewports)
{
	//Checa si est� el recurso, de no ser lo crea en el "else"
	if (pViewports == nullptr) {
		ERROR("DeviceContext", "RSSetViewports", "CHECK FOR const D3D11_VIEWPORT* pViewports")
			exit(1);
	}
	else {
		m_deviceContext->RSSetViewports(NumViewports, pViewports);
	}
}

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, 
	unsigned int NumViews, 
	ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	//En caso de ir mal, reviasr el par�metro de ShaderResources 
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", "CHECK FOR ID3D11ShaderResorceView* const* PSSetShaderResources")
			exit(1);
	}
	//Si todo va bien, tendr� que hacer un ppSetShaderResorces
	else 
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}