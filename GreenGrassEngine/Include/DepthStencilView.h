#pragma once
#include "PreRequisites.h"

//Se usann las foward declarations para usr recursos que no se declaran en el header y deban incluirse en el tiempo se ejecución
//Si ya se encuentra la variable en las F.D. se incluye cómo parámetro
class Device;
class DeviceContext;
class Texture;

class DepthStencilView
{
public:
	DepthStencilView() = default;
	~DepthStencilView() = default;

	/// <summary>
	/// Indica còmo se deben iterpretar los bits en el buffer de profundidad/stencil
	/// </summary>
	/// <param name="device">: Se utiliza para acceder a los recursos del 
	/// dispositivo necesarios para crear la vista.</param>
	/// <param name="depthStencil">: Proporciona el recurso de textura que 
	/// contendrá los datos de profundidad/stencil.</param>
	/// <param name="format">: Indica cómo se deben interpretar los bits 
	/// en el buffer de profundidad/stencil.</param>
	void 
		init(Device & device, 
				 Texture & depthStencil, 
				 DXGI_FORMAT format);

	/// <summary>
	/// Actualiza la lògica de DepthStencilView
	/// </summary>
	void 
		update();

	/// <summary>
	/// Limpia el buffer de profundidad/stencil con valores específicos (1.0 
	/// para la profundidad máxima y 0 para el stencil). 
	/// Esto es necesario antes de comenzar a renderizar una nueva escena para 
	/// asegurarse de que no haya datos residuales en el buffer de profundidad/stencil.
	/// </summary>
	/// <param name="deviceContext">: Se utiliza para aplicar la vista de 
	/// profundidad/stencil durante el proceso de renderizado.</param>
	void 
		render(DeviceContext& deviceContext);

	/// <summary>
	/// Libera los recursos usados de la memoria
	/// </summary>
	void 
		destroy();

	//Un puntero que maneja la vista de profundidad / stencil en Direct3D, usada 
	//para controlar las pruebas de profundidad y stencil durante el renderizado.
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
private:
};