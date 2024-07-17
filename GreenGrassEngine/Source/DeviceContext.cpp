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

void DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	//Verifica que el InputLayout est� creado y ES PRIORITARIO
	if (pInputLayout == nullptr) {
		ERROR("DeviceContext", "IASetInputLayout", "CHECK FOR ID3D11InputLayout* pInputLayout");
		exit(1);
	}
	else {
		m_deviceContext->IASetInputLayout(pInputLayout);
	}
}

void DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, 
								ID3D11ClassInstance* const* ppClassInstances, 
								unsigned int NumClassInstances)
{
	//Verifica que el VertexShader est� creado
	if (pVertexShader == nullptr) 
	{
		ERROR("DeviceContext", "VSSetShader", "CHECK FOR ID3D11VertexShader* pVertexShader");
		exit(1);
	}
	else 
	{
		m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}
}

void DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, 
								ID3D11ClassInstance* const* ppClassInstances, 
								unsigned int NumClassInstances)
{
	//Verifica que el Pixel shader est� creado
	if (pPixelShader == nullptr) 
	{
		ERROR("DeviceContext", "PSSetShader", "CHECK FOR ID3D11PixelShader* pPixelShader");
		exit(1);
	}
	else 
	{
		m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}
}

void DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, unsigned int DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, unsigned int SrcRowPitch, unsigned int SrcDepthPitch)
{
	m_deviceContext->UpdateSubresource(pDstResource,
									   DstSubresource,
									   pDstBox,
									   pSrcData,
									   SrcRowPitch,
									   SrcDepthPitch);
}

void DeviceContext::IASetVertexBuffers(unsigned int StartSlot, unsigned int NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const unsigned int* pStrides, const unsigned int* pOffsets)
{
	m_deviceContext->IASetVertexBuffers(StartSlot,
										NumBuffers,
										ppVertexBuffers,
										pStrides,
										pOffsets);
}

void DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, unsigned int Offset)
{
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset); 
}

void DeviceContext::PSSetSamplers(unsigned int StartSlot, 
								  unsigned int NumSamplers, 
								  ID3D11SamplerState* const* ppSamplers)
{
	if (ppSamplers == nullptr) {
		ERROR("DeviceContext", "PSSetSamplers", "CHECK FOR ID3D11SamplerState* const* ppSamplers");
	}
	else {
		m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
	}
}
