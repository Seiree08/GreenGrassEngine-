#pragma once
#include "PreRequisites.h"
#include "fbxsdk.h"
#include "MeshComponent.h"

class ModelLoader
{
public:
	//Inicializa el FbxManager, crea la configuraci�n de E/S (FbxIOSettings) y la escena FbxScene.
	ModelLoader();
	//Libera los recursos asignados por el FbxManager.
	~ModelLoader();

	/// <summary>
	/// Este m�todo se encarga de cargar un archivo FBX desde la ruta especificada.
	/// </summary>
	/// <param name="filepath">Una cadena de texto que representa la ruta 
	/// completa del archivo FBX que se desea cargar.</param>
	/// <returns>Retorna true si el modelo se carga correctamente, o false 
	/// si ocurre alg�n error.</returns>
	bool 
		LoadModel(const std::string& filepath);

	/// <summary>
	/// Devuelve un vector constante de los v�rtices (SimpleVertex) que han 
	/// sido extra�dos del modelo.
	/// </summary>
	/// <returns>Devuelve una referencia constante a un vector de SimpleVertex, 
	/// que contiene los v�rtices procesados del modelo.</returns>
	const std::vector<SimpleVertex>& 
		GetVertices() const { return vertices; }

	/// <summary>
	/// Devuelve un vector constante de los �ndices (uint32_t) que definen 
	/// la geometr�a de los pol�gonos en el modelo.
	/// </summary>
	/// <returns>Devuelve una referencia constante a un vector de uint32_t, 
	/// que contiene los �ndices procesados del modelo.</returns>
	const std::vector<uint32_t>& 
		GetIndices() const { return indices; }

	/// <summary>
	/// Devuelve una lista de nombres de archivos de textura asociados con el modelo.
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> 
		GetTextureFileNames() const { return textureFileNames; }

	/// <summary>
	/// Este m�todo se encarga de procesar un nodo del modelo. Si el nodo tiene 
	/// un atributo que es una malla (mesh), llama a ProcessMesh para procesar 
	/// esa malla. Luego, recursivamente llama a s� misma para procesar 
	/// todos los nodos hijos del nodo actual.
	/// </summary>
	/// <param name="node">: Un puntero a un objeto FbxNode, que representa 
	/// un nodo en la jerarqu�a de la escena del modelo FBX.</param>
	void 
		ProcessNode(FbxNode* node);

	/// <summary>
	/// Procesa la malla contenida en un nodo. Extrae los v�rtices, normales, 
	/// coordenadas UV y los �ndices de los pol�gonos. Estos datos se almacenan 
	/// en los vectores vertices y indices para su uso posterior.
	/// </summary>
	/// <param name="node">: Un puntero a un objeto FbxNode que contiene 
	/// una malla (mesh). Este nodo es procesado para extraer su geometr�a.</param>
	void 
		ProcessMesh(FbxNode* node);

	/// <summary>
	/// Procesa un material para extraer los nombres de los archivos de textura 
	/// asociados a �l. Estos nombres se almacenan en el vector textureFileNames.
	/// </summary>
	/// <param name="material">:  Un puntero a un objeto FbxSurfaceMaterial, 
	/// que representa un material de la superficie en la escena.</param>
	void 
		ProcessMaterials(FbxSurfaceMaterial* material);

private:
	//Es un puntero a un objeto FbxManager, que es el n�cleo del SDK de FBX. 
	//Se utiliza para gestionar la carga y el procesamiento de archivos FBX.
	FbxManager* lSdkManager;
	//Es un puntero a un objeto FbxScene, que representa la escena 3D cargada 
	//desde un archivo FBX.
	FbxScene* lScene;
	//Vectores que almacenan los v�rtices de los pol�gonos del modelo.
	std::vector<SimpleVertex> vertices;
	//Vectores que almacenan los �ndices de los pol�gonos del modelo.
	std::vector<unsigned int> indices;
	//Un vector de strings que contiene los nombres de los archivos de 
	//textura asociados con el modelo.
	std::vector<std::string>textureFileNames;

public:
	//Almacena informaci�n de cada malla procesada en el modelo.
	std::vector<MeshComponent>meshes;
};