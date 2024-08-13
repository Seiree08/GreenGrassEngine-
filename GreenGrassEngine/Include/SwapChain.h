#pragma once
#include "PreRequisites.h"

//Foward Declaratons - Declaraciones directas
//Hace referencia a una clase sin incluir el contenido, principalmente para parámetros
class Device;
class DeviceContext;
class Window;
class Texture;

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain() = default;

	/// <summary>
	///  inicializa la “SwapChain” y otros recursos relacionados con Direct3D.
	/// </summary>
	/// <param name="device">: Este es un objeto de dispositivo, que se utiliza 
	/// para crear recursos de Direct3D.</param>
	/// <param name="deviceContext">: Este es un objeto de contexto de dispositivo, 
	/// que se utiliza para configurar y controlar cómo los gráficos se dibujan.</param>
	/// <param name="backBuffer">: Este es un objeto de textura que representa el 
	/// back buffer. En una “SwapChain”, el back buffer es donde se dibujan los 
	/// gráficos antes de que se muestren en la pantalla.</param>
	/// <param name="window">: Este es un objeto de ventana que representa la ventana 
	/// en la que se mostrarán los gráficos.</param>
	void 
		init(Device & device,
				 DeviceContext & deviceContext,
				 Texture & backBuffer,
				 Window window);

	/// <summary>
	/// Actualiza la lógica del SwapChain aunque no hay
	/// </summary>
	void 
		update();

	/// <summary>
	/// Se usa pa' realizar operaciones de renderizado
	/// </summary>
	void 
		render();

	/// <summary>
	/// Libera los recursos de la memoria
	/// </summary>
	void 
		destroy();

	/// <summary>
	/// Presenta el contenido del BackBuffer en pantalla
	/// </summary>
	void 
		present();
	
	//Puntero a la interfaz IDXGISwapChain, presenta una cadena de intercambio
	IDXGISwapChain* m_swapChain = nullptr;
	//
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
};