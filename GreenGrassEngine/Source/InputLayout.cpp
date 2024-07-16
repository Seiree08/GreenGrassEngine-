#include "InputLayout.h"
#include "Device.h"
#include "DeviceContext.h"

void InputLayout::init(Device device, 
					   std::vector<D3D11_INPUT_ELEMENT_DESC> Layout, 
					   ID3DBlob* VertexShaderData)
{
	//Revisa el vector del Layout que est� bien
	if (Layout.size() == 0) {
		ERROR("InputLayout", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout");
		exit(1);
	}
	//Revisa que el VertexShaderData est� inicializado previemente
	else if (VertexShaderData == nullptr) {
		ERROR("InputLayout", "init", "CHECK FOR ID3DBlob* VertexShaderData");
		exit(1);
	}

	HRESULT hr = S_OK;
	
	//Crea el Layout
	hr = device.CreateInputLayout(Layout.data()/*Accede a los recursos (memoria) del vector*/,
		Layout.size()/*Tama�o de elementos*/,
		VertexShaderData->GetBufferPointer()/*Apunta a la info del VertexShader*/,
		VertexShaderData->GetBufferSize()/*Accede al tama�o del buffer*/,
 		&m_inputLayout)/*Es para que se inicialize de forma correcta*/;

	//S�lo para corroborar, se manda un mensaje si hay alg�n error en el Layout
	if (FAILED(hr)) {
		ERROR("InputLayout", "init", "CHECK FOR CreateInputLayout()");
		exit(1);
	}
}

void InputLayout::update()
{
}

//Dibuja los recursos
void InputLayout::render(DeviceContext& deviceContext)
{
	deviceContext.IASetInputLayout(m_inputLayout);
}
//Libera recursos
void InputLayout::destroy()
{
	SAFE_RELEASE(m_inputLayout);
}
