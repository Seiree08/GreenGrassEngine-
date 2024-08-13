//Documenta esta calse con "///" cada funci�n
#pragma once
#include "PreRequisites.h"

class Device
{
public:
	Device() = default;
	~Device() = default;

	void init();

	void update();

	void render();

	void destroy();

	/// <summary>
	/// La funci�n CreateRenderTargetView pertenece a la API de Direct3D 11, que es parte de DirectX, 
	/// una colecci�n de API para manejar tareas relacionadas con multimedia, especialmente programaci�n de juegos y video, 
	/// en plataformas de Microsoft.
	/// </summary>
	/// <param name="pResource">Este par�metro es un puntero a un recurso de Direct3D 11. Este recurso generalmente es una textura que se va a utilizar como objetivo de renderizado.</param>
	/// <param name="pDesc">Es un puntero a una estructura de tipo D3D11_RENDER_TARGET_VIEW_DESC que describe la vista de objetivo de renderizado a crear. Esta estructura especifica detalles como el formato de la vista y los subrecursos a utilizar.</param>
	/// <param name="ppRTView">Es un puntero a un puntero de ID3D11RenderTargetView. Esta funci�n crea la vista de objetivo de renderizado y almacena el puntero a la vista creada en la direcci�n especificada por este par�metro.</param>
	/// <returns></returns>
	HRESULT CreateRenderTargetView(ID3D11Resource* pResource, 
		const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, 
		ID3D11RenderTargetView** ppRTView);

	/// <summary>
	/// La funci�n CreateTexture2D pertenece a la API de Direct3D 11 y se utiliza para crear una textura 2D.
	/// </summary>
	/// <param name="pDesc">Es un puntero a una estructura D3D11_TEXTURE2D_DESC que describe la textura 2D que se va a crear. Esta estructura incluye informaci�n sobre el formato, ancho, alto, n�mero de mipmaps, uso, bind flags, entre otros detalles.</param>
	/// <param name="pInitialData">Es un puntero a una estructura D3D11_SUBRESOURCE_DATA que contiene los datos iniciales de los subrecursos de la textura. Puede ser NULL si no se especifican datos iniciales.</param>
	/// <param name="ppTexture2D">Es un puntero a un puntero de ID3D11Texture2D. Esta funci�n crea la textura 2D y almacena el puntero a la textura creada en la direcci�n especificada por este par�metro.</param>
	/// <returns></returns>
	HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, 
		const D3D11_SUBRESOURCE_DATA* pInitialData, 
		ID3D11Texture2D** ppTexture2D);

	/// <summary>
	/// La funci�n CreateDepthStencilView pertenece a la API de Direct3D 11 y se utiliza para crear una vista de stencil y profundidad para un recurso dado.
	/// </summary>
	/// <param name="pResource">Es un puntero a un recurso de Direct3D 11. Este recurso generalmente es una textura que se utilizar� para la profundidad y el stencil.</param>
	/// <param name="pDesc">Es un puntero a una estructura de tipo D3D11_DEPTH_STENCIL_VIEW_DESC que describe la vista de stencil y profundidad a crear. Esta estructura especifica detalles como el formato de la vista y los subrecursos a utilizar.</param>
	/// <param name="ppDepthStencilView">Es un puntero a un puntero de ID3D11DepthStencilView. Esta funci�n crea la vista de stencil y profundidad y almacena el puntero a la vista creada en la direcci�n especificada por este par�metro.</param>
	/// <returns></returns>
	HRESULT CreateDepthStencilView(ID3D11Resource* pResource, 
		const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, 
		ID3D11DepthStencilView** ppDepthStencilView);
	
	/// <summary>
	/// La funci�n CreateVertexShader se utiliza para crear un vertex shader, que es un componente esencial en el renderizado de gr�ficos 3D. Procesa los datos de los v�rtices para la representaci�n de gr�ficos. 
	/// </summary>
	/// <param name="pShaderBytecode">Un puntero al bytecode del shader, que contiene el c�digo del shader precompilado.</param>
	/// <param name="BytecodeLength">Un entero sin signo que representa la longitud del array de bytecode.</param>
	/// <param name="pClassLinkage">Un puntero a una interfaz de enlace de clase, que podr�a usarse para el enlace din�mico de shaders.</param>
	/// <param name="ppVertexShader">Un puntero a un puntero a una interfaz ID3D11VertexShader donde se almacenar� el vertex shader creado.</param>
	/// <returns></returns>
	HRESULT CreateVertexShader(const void* pShaderBytecode, 
		unsigned int BytecodeLength, 
		ID3D11ClassLinkage* pClassLinkage, 
		ID3D11VertexShader** ppVertexShader);

	/// <summary>
	/// La funci�n CreateInputLayout es una funci�n de la API Direct3D 11 que se utiliza para crear un layout de entrada. Este layout describe el formato de los datos de entrada para el pipeline de gr�ficos. 
	/// </summary>
	/// <param name="pInputElementDescs">Un puntero a un array de descripciones de elementos de entrada.</param>
	/// <param name="NumElements">El n�mero de elementos en el array.</param>
	/// <param name="pShaderBytecodeWithInputSignature">Un puntero al bytecode del shader con la firma de entrada.</param>
	/// <param name="BytecodeLength">La longitud del bytecode.</param>
	/// <param name="ppInputLayout">Un puntero a un puntero donde se almacenar� el layout de entrada creado.</param>
	/// <returns></returns>
	HRESULT CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
		unsigned int NumElements,
		const void* pShaderBytecodeWithInputSignature,
		unsigned BytecodeLength,
		ID3D11InputLayout** ppInputLayout);

	//Procesa los pixles que se mostrar�n en pantalla, la info que venga de VertexShader se procesa a pixel
	/// <summary>
	/// 
	/// </summary>
	/// <param name="pShaderBytecode"></param>
	/// <param name="BytecodeLength"></param>
	/// <param name="pClassLinkage"></param>
	/// <param name="ppPixelShader"></param>
	/// <returns></returns>
	 
	/// <summary>
	/// Esta funci�n crea un pixel shader. Los shaders de p�xeles son programas que calculan el color de los p�xeles individuales renderizados en la pantalla.
	/// </summary>
	/// <param name="pShaderBytecode">Un puntero al bytecode del shader.</param>
	/// <param name="BytecodeLength"> La longitud del bytecode.</param>
	/// <param name="pClassLinkage">Un puntero a una interfaz de enlace de clase.</param>
	/// <param name="ppPixelShader">Un puntero a un puntero donde se almacenar� el shader de p�xeles creado.</param>
	/// <returns></returns>
	HRESULT CreatePixelShader(const void* pShaderBytecode,
		unsigned int BytecodeLength,
		ID3D11ClassLinkage* pClassLinkage,
		ID3D11PixelShader** ppPixelShader);

	/// <summary>
	/// Esta funci�n crea un buffer, que es una regi�n de la memoria f�sica utilizada para almacenar temporalmente los datos mientras se est�n moviendo de un lugar a otro.
	/// </summary>
	/// <param name="pDesc">Un puntero a una descripci�n del buffer.</param>
	/// <param name="pInitialData">Un puntero a los datos iniciales que se cargar�n en el buffer.</param>
	/// <param name="ppBuffer">Un puntero a un puntero donde se almacenar� el buffer creado.</param>
	/// <returns></returns>
	HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
		const D3D11_SUBRESOURCE_DATA *pInitialData,
		ID3D11Buffer **ppBuffer);

	/// <summary>
	/// Esta funci�n crea un estado de muestreador, que define c�mo se deben muestrear los datos de textura cuando se renderizan.
	/// </summary>
	/// <param name="pSamplerDesc">Un puntero a una descripci�n del estado del muestreador.</param>
	/// <param name="ppSamplerState">Un puntero a un puntero donde se almacenar� el estado del muestreador creado.</param>
	/// <returns></returns>
	HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
		ID3D11SamplerState** ppSamplerState);


	ID3D11Device* m_device = nullptr;
};