#pragma once
#include "PreRequisites.h"
class Device;
class DeviceContext;

class InputLayout
{
public:
	InputLayout() = default;
	~InputLayout() = default;
	
	//Para usar el vector se declara en PreRequisites
	//Este maneja el seteo del InputLayout
	void
		init(Device device,
			std::vector<D3D11_INPUT_ELEMENT_DESC> Layout,
			ID3DBlob* VertexShaderData);

	void
		update();

	void
		render(DeviceContext& deviceContext);

	void
		destroy();

public:
	ID3D11InputLayout* m_inputLayout = nullptr;
};