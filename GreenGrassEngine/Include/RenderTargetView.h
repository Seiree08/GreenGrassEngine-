#pragma once
#include "PreRequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

class RenderTargetView
{
public:
	//Son los contructores y destructores
	RenderTargetView() = default;
	~RenderTargetView() = default;

	/// <summary>
	/// Inicializa el RenderTargetView con el device, el cackBuffer y el formato
	/// </summary>
	/// <param name="device">: Es una instancia de la clase Device que representa
	/// el dispositivo Direct3D para crear recursos gràficos</param>
	/// <param name="backBuffer">: Representa a la textura que se usarà 
	/// còmo backBuffer</param>
	/// <param name="Format">: Define el formato de los datos de textura</param>
	void 
		init(Device device, 
				 Texture backBuffer, 
				 DXGI_FORMAT Format);

	/// <summary>
	/// Actualiza el estado de RenderTargetView
	/// </summary>
	void 
		update();

	/// <summary>
	/// Renderiza el contenido de la clase y establece el buffer de profundidad
	/// </summary>
	/// <param name="deviceContext">: Representa el contexto del dispositivo 
	/// Direct3D.</param>
	/// <param name="depthStencilView">: Representa la vista del buffer de 
	/// profundidad y stencil.</param>
	/// <param name="numViews">: Especifica cuántas vistas de renderizado se deben 
	/// establecer en el pipeline.</param>
	/// <param name="ClearColor">: Especifica el color de fondo que se aplicará al 
	/// limpiar el RenderTargetView antes de renderizar nuevos gráficos.</param>
	void 
		render(DeviceContext& deviceContext,
		   		 DepthStencilView& depthStencilView,
					 unsigned int numViews,
				   float ClearColor[4]);

	/// <summary>
	/// Liberaciòn de recursos
	/// </summary>
	void 
		destroy();

	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};