//Documenta esta calse con "///" cada función
#pragma once
#include "PreRequisites.h"

class Device
{
public:
	Device() = default;
	~Device() = default;

	void init();

	void update();

	void render();

	void destroy();

	//Se implementa la clase CreateRenderTargetView y definimos
	HRESULT CreateRenderTargetView(ID3D11Resource* pResource, 
		const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
		ID3D11RenderTargetView** ppRTView);

	//Se implementa la clase CreateTexture2D y definimos
	HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, 
		const D3D11_SUBRESOURCE_DATA* pInitialData, 
		ID3D11Texture2D** ppTexture2D);

	//Creamos la clase CreateDepthStencilView y definimos
	HRESULT CreateDepthStencilView(ID3D11Resource* pResource, 
		const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
		ID3D11DepthStencilView** ppDepthStencilView);
	
	//Creamos la clase CreateVertexShader y definimos
	HRESULT CreateVertexShader(const void* pShaderBytecode, 
		unsigned int BytecodeLength, 
		ID3D11ClassLinkage* pClassLinkage, 
		ID3D11VertexShader** ppVertexShader);

	//Creamos nuestra clase "CreateInputLayout" y definimos en Device.cpp
	HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
		unsigned int NumElements,
		const void* pShaderBytecodeWithInputSignature,
		unsigned BytecodeLength,
		ID3D11InputLayout** ppInputLayout);

	//Creamos nuestra clase "CreatePixelShader" e igualmente definimos en .cpp
	//Procesa los pixles que se mostrarán en pantalla, la info que venga de VertexShader se procesa a pixel
	HRESULT CreatePixelShader(const void* pShaderBytecode,
		unsigned int BytecodeLength,
		ID3D11ClassLinkage* pClassLinkage,
		ID3D11PixelShader** ppPixelShader);

	HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
		const D3D11_SUBRESOURCE_DATA *pInitialData,
		ID3D11Buffer **ppBuffer);

	HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
		ID3D11SamplerState** ppSamplerState);

	ID3D11Device* m_device = nullptr;
private:

};