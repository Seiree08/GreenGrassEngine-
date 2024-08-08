#include "ModelLoader.h"

ModelLoader::ModelLoader()
	: lSdkManager(nullptr), lScene(nullptr)
{
	//Inicializa el SDK Manager
	lSdkManager = FbxManager::Create();
	if (!lSdkManager)
	{
		ERROR("ModelLoader", "FbxManger::Create()", "Unable to create FBX Manager");
	}
	else
	{
		MESSAGE("ModelLoader", "ModelLoader", "Autodesk FBX SDK version" << lSdkManager->GetVersion());
	}
	//Crea un objeto IOSettings 
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	//Crea la escena FBX
	lScene = FbxScene::Create(lSdkManager, "myScene");
}

ModelLoader::~ModelLoader()
{
	//Destruye el SDK Manager y todos los ibjetos que manejaba
	if (lSdkManager) lSdkManager->Destroy();
}

bool ModelLoader::LoadModel(const std::string& filepath)
{
	//Crea un importador? usando el SDK Manager
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	//Usa el primer argumento como el nombre del archivo para el importer
	if (!lImporter->Initialize(filepath.c_str(), -1, lSdkManager->GetIOSettings()))
	{
		MESSAGE("ModelLoader", "LoadModel", "Unable to import the FBX scene from file : " << filepath.c_str())
		ERROR("ModelLoader", "LoadModel", "Error returned: " << lImporter->GetStatus().GetErrorString())
		return false;
	}

	//Importa la escena
	if (!lImporter->Import(lScene))
	{
		ERROR("ModelLoader", "lImporter->Import", "Unable to import the FBX scene from file : " << filepath.c_str())
		lImporter->Destroy();
		return false;
	}

	//Destruye el importer
	lImporter->Destroy();
	MESSAGE("ModelLoader", "LoasModel", "Succesfully imported the FBX scene from file: " << filepath.c_str())

	//Procesa la escena
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			FbxSurfaceMaterial* material = lScene->GetMaterial(i);
			ProcessNode(lRootNode);
		}
	}

	//Puedes proceder a la escena como sea requerida
	return true;
}

void ModelLoader::ProcessNode(FbxNode* node)
{
    // Verificar si el nodo tiene un atributo asociado
    if (node->GetNodeAttribute())
    {
        // Verificar si el atributo es de tipo malla (mesh)
        if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
        {
            // Procesar la malla contenida en el nodo
            ProcessMesh(node);
        }
	}

	//Recursivamente procesa todos los nodos
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		ProcessNode(node->GetChild(i));
	}
}

void ModelLoader::ProcessMesh(FbxNode* node)
{
	FbxMesh* mesh = node->GetMesh();
	if (!mesh) return;

	std::vector<SimpleVertex> vertices;
	std::vector<UINT> indices;

	// Procesar vértices y normales
	for (int i = 0; i < mesh->GetControlPointsCount(); i++) 
	{
		FbxVector4* controlPoint = mesh->GetControlPoints();
		SimpleVertex vertex;
		vertex.Pos = XMFLOAT3((float)controlPoint[i][0],
					   		  (float)controlPoint[i][1],
							  (float)controlPoint[i][2]);
		vertices.push_back(vertex);
	}

	// Procesar UVs
	if (mesh->GetElementUVCount() > 0) 
	{
		FbxGeometryElementUV* uvElement = mesh->GetElementUV(0);
		FbxGeometryElement::EMappingMode mappingMode = uvElement->GetMappingMode();
		FbxGeometryElement::EReferenceMode referenceMode = uvElement->GetReferenceMode();
		int polyIndexCounter = 0;

		for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) 
		{
			int polySize = mesh->GetPolygonSize(polyIndex);
			for (int vertIndex = 0; vertIndex < polySize; vertIndex++) 
			{
				int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);

				int uvIndex = -1;
				if (mappingMode == FbxGeometryElement::eByControlPoint) 
				{
					if (referenceMode == FbxGeometryElement::eDirect) 
					{
						uvIndex = controlPointIndex;
					}
					else if (referenceMode == FbxGeometryElement::eIndexToDirect) 
					{
						uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
					}
				}
				else if (mappingMode == FbxGeometryElement::eByPolygonVertex) 
				{
					if (referenceMode == FbxGeometryElement::eDirect || referenceMode == FbxGeometryElement::eIndexToDirect) 
					{
						uvIndex = uvElement->GetIndexArray().GetAt(polyIndexCounter);
						polyIndexCounter++;
					}
				}

				if (uvIndex != -1) 
				{
					FbxVector2 uv = uvElement->GetDirectArray().GetAt(uvIndex);
					vertices[controlPointIndex].Tex = XMFLOAT2((float)uv[0], -(float)uv[1]);
				}
			}
		}
	}

	// Procesar índices
	for (int i = 0; i < mesh->GetPolygonCount(); i++) 
	{
		for (int j = 0; j < mesh->GetPolygonSize(i); j++) 
		{
			indices.push_back(mesh->GetPolygonVertex(i, j));
		}
	}

	MeshComponent meshData;
	meshData.m_vertex = vertices;
	meshData.m_index = indices;
	meshData.m_name = node->GetName();
	meshData.m_numVertex = vertices.size();
	meshData.m_numIndex = indices.size();

	meshes.push_back(meshData);
	//ANTERIOR LÓGICA
	//int polygonCount = mesh->GetPolygonCount();
	//vertices.reserve(polygonCount * 3);
	//indices.reserve(polygonCount * 3);
	////Obtiene el UV set name
	//const char* uvSetName = nullptr;
	//FbxStringList uvSetNameList;
	//mesh->GetUVSetNames(uvSetNameList);
	//if (uvSetNameList.GetCount() > 0)
	//{
	//	uvSetName = uvSetNameList.GetStringAt(0);
	//}
	//else
	//{
	//	ERROR("ModelLoader", "ProcessMesh", "No UV set found in the mesh")
	//		return;
	//}
	////Obitne los vèrtices e ìndices
	//for (int i = 0; i < polygonCount; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		SimpleVertex vertex;
	//		//Obtiene las posicones del vertex
	//		int controlPointIndex = mesh->GetPolygonVertex(i, j);
	//		FbxVector4 pos = mesh->GetControlPointAt(controlPointIndex);
	//		vertex.Pos = XMFLOAT3(static_cast<float>(pos[0]), static_cast<float>(pos[1]), static_cast<float>(pos[2]));
	//		//Obtiene las coordenadas de textira
	//		FbxVector2 texCoord;
	//		bool unmapped;
	//		mesh->GetPolygonVertexUV(i, j, uvSetName, texCoord, unmapped);
	//		vertex.Tex = XMFLOAT2(static_cast<float>(texCoord[0]), static_cast<float>(texCoord[1]));
	//		//Agrega el vertex a la lista
	//		vertices.push_back(vertex);
	//		indices.push_back(vertices.size() - 1);
	//	}
	//}
}

void ModelLoader::ProcessMaterials(FbxSurfaceMaterial* material)
{
	// Procesar el material para obtener las texturas asociadas
	if (material)
	{
		//Desde el Fbx se ectraen los materiales del objeto y se guardam el la lista de texturas
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		if (prop.IsValid())
		{
			int textureCount = prop.GetSrcObjectCount<FbxTexture>();
			for (int i = 0; i < textureCount; ++i)
			{
				FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(i));
				if (texture)
				{
					textureFileNames.push_back(texture->GetName());
				}
			}
		}
	}
}

