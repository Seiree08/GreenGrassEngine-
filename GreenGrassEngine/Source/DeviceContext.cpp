#include "DeviceContext.h"

void DeviceContext::destroy()
{
	SAFE_RELEASE(m_deviceContext);
}

void DeviceContext::PSSetShaderResources(unsigned int StartSlot, 
	unsigned int NumViews, 
	ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	//En caso de ir mal, reviasr el parámetro de ShaderResources 
	if (ppShaderResourceViews == nullptr)
	{
		ERROR("DeviceContext", "PSSetShaderResources", "CHECK FOR ID3D11ShaderResorceView* const* PSSetShaderResources")
			exit(1);
	}
	//Si todo va bien, tendrá que hacer un ppSetShaderResorces
	else 
	{
		m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
	}
}
