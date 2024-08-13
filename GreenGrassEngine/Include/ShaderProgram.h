#pragma once
#include "PreRequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class ShaderProgram
{
public:
	ShaderProgram() = default;
	~ShaderProgram() = default;

	/// <summary>
	/// Este m�todo inicializa el programa de shaders. Carga y compila los 
	/// shaders, y configura el input layout.
	/// </summary>
	/// <param name="device">: Objeto que representa el dispositivo Direct3D.</param>
	/// <param name="fileName">: Nombre del archivo HLSL que contiene los shaders.</param>
	/// <param name="Layout">: Descripci�n del layout de entrada de los v�rtices.</param>
	void 
		init(Device device,
			  std::string fileName,
			  std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

	/// <summary>
	/// Aqu� se actualiza la l�gica del ShaderProgram pero ahora no hay			  
	/// </summary>
	void 
		update();
	
	/// <summary>
	/// Establece el input layout.
	/// Aplica el vertex shader y el pixel shader.
	/// </summary>
	/// <param name="deviceContext">: Referencia al contexto del dispositivo 
	/// Direct3D.</param>
	void 
		render(DeviceContext& deviceContext);

	/// <summary>
	/// libera recursoso del programa
	/// </summary>
	void 
		destroy();

	/// <summary>
	/// Este m�todo compila un shader desde un archivo HLSL.
	/// </summary>
	/// <param name="szFileName">: Nombre del archivo HLSL.</param>
	/// <param name="szEntryPoint">: Punto de entrada del shader (funci�n principal).</param>
	/// <param name="szShaderModel">: Modelo de shader a utilizar.</param>
	/// <param name="ppBlobOut">: Puntero al blob donde se almacenar� el shader compilado.</param>
	/// <returns></returns>
	HRESULT 
		CompileShaderFromFile(char* szFileName,
													LPCSTR szEntryPoint,
					   						  LPCSTR szShaderModel,
		                      ID3DBlob** ppBlobOut);

	/// <summary>
	///  El input layout define c�mo los datos de los v�rtices 
	/// (como posiciones, colores, coordenadas de textura, etc.) 
	/// se estructuran y se interpretan en el shader.
	/// </summary>
	/// <param name="device">: Objeto que representa el dispositivo Direct3D.</param>
	/// <param name="Layout">: Es un vector de estructuras que describe los 
	/// elementos de entrada del v�rtice</param>
	void 
		CreateInputLayout(Device device, 
											std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

	/// <summary>
	/// Este m�todo crea un shader (vertex o pixel) usando los datos compilados.
	/// </summary>
	/// <param name="device">: Dispositivo Direct3D.</param>
	/// <param name="type">: Tipo de shader a crear (vertex o pixel).</param>
	void 
		CreateShader(Device device, 
								 ShaderType type);

public:
	//Puntero al vertex Shader
	ID3D11VertexShader* m_VertexShader = nullptr;
	//Puntero al pixel Shader
	ID3D11PixelShader* m_PixelShader = nullptr;
	//Gestiona el layout para la entrada de los v�rtices
	InputLayout m_inputLayout;

private:
	//Nombre del archivo que contiene el c�digo HLSL de los shaders.
	std::string m_shaderFileName;
	//Puntero al blob que almacena los datos compilados del vertex shader.
	ID3DBlob* m_vertexShaderData = nullptr;
	//Puntero al blob que almacena los datos compilados del pixel shader.
	ID3DBlob* m_pixelShaderData = nullptr;
};
