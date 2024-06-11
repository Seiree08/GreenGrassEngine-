#pragma once
#include "PreRequisites.h"

//Foward Declaratons - Declaraciones directas
//Hace referencia a una clase sin incluir el contenido, principalmente para par�metros
class Device;
class DeviceContext;
class Window;
class Texture;

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain() = default;

	void init(Device & device,
		DeviceContext & deviceContext,
		Texture & backBuffer,
		Window window);

	void update();

	void render();

	void destroy();

	void present();

	IDXGISwapChain* m_swapChain = nullptr;
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
};