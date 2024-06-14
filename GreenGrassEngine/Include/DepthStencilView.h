#pragma once
#include "PreRequisites.h"

//Se usann las foward declarations para usr recursos que no se declaran en el header y deban incluirse en el tiempo se ejecuci�n
//Si ya se encuentra la variable en las F.D. se incluye c�mo par�metro
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

	//Se a�ade por que el recurso de ocupa para que funcione
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
private:
};