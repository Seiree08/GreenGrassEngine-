#pragma once
#include "PreRequisites.h"

class Device;
class DeviceContext;

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

	//Hay dos tipos de init, el que se crea a partir de un modelo que se carga y la que se crea manual

	/// <summary>
	/// Brief: Crea una textura a partir de una imagen (.dds) desde un ordenador.
	/// </summary>
	/// <param name="device">: Llamamos al device para poder generar los drecursos en memoria </param>
	/// <param name="textureName">: Llamamos al device para poder generar los drecursos en memoria </param>
	/// 
	HRESULT init(Device device, std::string textureName);
	//Se transorma en HRESULT para ver si un elemento es nulo o no

	/// <summary>
	/// Brief: This method is responsible for creating 2D Texture from the data provided by the developer genera la textura 
	/// </summary>
	/// <param name="device">: It is in charge of providing the resources to create the 2D texture.</param>
	/// <param name="width">: It will take the width of our window</param>
	/// <param name="height">: It will take the height of our window</param>
	/// <param name="Format">: It is a classifier that will allow bit spaces to be created correctly in memory.</param>
	/// <param name="BindFlags">It s a characteristic to classify the type of texture that is being created.</param>
	void init(Device device,
			unsigned int width,
			unsigned int height,
			DXGI_FORMAT Format,
			unsigned int BindFlags);

	/// <summary>
	/// Brief: Is in charge of updating the logic of the texture
	/// </summary>
	void update();

	/// <summary>
	/// Brief: This is in charge of drawing the resorurce on the scene. (Only if necesary)
	/// </summary>
	/// <param name="deviceContext">: It is in charge of assigning resources to be used.</param>
	/// <param name="StartSlot">: It is in charge of assigning the star point in memory
	/// We recommend checking that it is not spliced ?? in memory with other resorces.</param>
	/// <param name="NumViews"></param>
	void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

	/// <summary>
	/// Brief: This method is in charge of releasing the resources stored in the class's memory
	/// </summary>
	void destroy();

	//This varibale is in charge of handle a texture resource as data
	ID3D11Texture2D* m_texture = nullptr;
	//This variable is in charge of handle a texture resource as image data, se carga de una textura del proyecto
	ID3D11ShaderResourceView* m_textureFromImg;
private:

};