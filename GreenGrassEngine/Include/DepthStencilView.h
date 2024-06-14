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


	void init(Device & device, Texture & depthStencil, DXGI_FORMAT format);

	void update();

	void render(DeviceContext& deviceContext);
	/*El & pasa por la referencia y que el contenido pueda ser modificado en render*/

	void destroy();

	//Se añade por que el recurso de ocupa para que funcione
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
private:
};