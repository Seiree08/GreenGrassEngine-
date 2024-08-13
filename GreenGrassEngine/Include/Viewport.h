#pragma once
#include "PreRequisites.h"
class Window;
class DeviceContext;

class
	Viewport {
public:
	Viewport() = default;
	~Viewport() = default;

	/// <summary>
	/// Este método inicializa el viewport, que define el área de la ventana 
	/// donde se renderiza la escena.
	/// </summary>
	/// <param name="window">: Proporciona las dimensiones de la ventana 
	/// necesarias para definir el tamaño del viewport.</param>
	void
		init(Window window);

	/// <summary>
	/// Actualiza la lógica del Viewport
	/// </summary>
	void
		update();

	/// <summary>
	/// Este método llama a RSSetViewports en el contexto del dispositivo 
	/// para configurar el viewport actual.
	/// </summary>
	/// <param name="deviceContext">: Se utiliza para establecer el viewport 
	/// activo en el pipeline de renderizado de Direct3D.</param>
	void
		render(DeviceContext& deviceContext);

	/// <summary>
	/// Este método libera los recursos de memoria
	/// </summary>
	void
		destroy();
	
	//Estructura que describe las dimensiones y características del viewport en Direct3D. 
	//Contiene información como el ancho, la altura, 
	//la profundidad mínima y máxima, y la posición superior izquierda.
	D3D11_VIEWPORT m_viewport;
};