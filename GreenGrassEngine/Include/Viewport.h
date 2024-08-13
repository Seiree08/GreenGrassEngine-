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
	/// Este m�todo inicializa el viewport, que define el �rea de la ventana 
	/// donde se renderiza la escena.
	/// </summary>
	/// <param name="window">: Proporciona las dimensiones de la ventana 
	/// necesarias para definir el tama�o del viewport.</param>
	void
		init(Window window);

	/// <summary>
	/// Actualiza la l�gica del Viewport
	/// </summary>
	void
		update();

	/// <summary>
	/// Este m�todo llama a RSSetViewports en el contexto del dispositivo 
	/// para configurar el viewport actual.
	/// </summary>
	/// <param name="deviceContext">: Se utiliza para establecer el viewport 
	/// activo en el pipeline de renderizado de Direct3D.</param>
	void
		render(DeviceContext& deviceContext);

	/// <summary>
	/// Este m�todo libera los recursos de memoria
	/// </summary>
	void
		destroy();
	
	//Estructura que describe las dimensiones y caracter�sticas del viewport en Direct3D. 
	//Contiene informaci�n como el ancho, la altura, 
	//la profundidad m�nima y m�xima, y la posici�n superior izquierda.
	D3D11_VIEWPORT m_viewport;
};