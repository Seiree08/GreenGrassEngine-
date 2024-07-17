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
	FbxNode* rootNode = lScene->GetRootNode();
	if (rootNode)
	{
		ProcessNode(rootNode);
	}

	//Puedes proceder a la escena como sea requerida
	return true;
}

void ModelLoader::ProcessNode(FbxNode* node)
{
	//Procesa todos los node's meshes
	if (node->GetNodeAttribute())
	{
		if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			ProcessMesh(node->GetMesh());
		}
	}

	//Recursivamente procesa todos los nodos
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		ProcessNode(node->GetChild(i));
	}
}

void ModelLoader::ProcessMesh(FbxMesh* mesh)
{
	int polygonCount = mesh->GetPolygonCount();
	vertices.reserve(polygonCount * 3);
	indices.reserve(polygonCount * 3);

	//Obtiene el UV set name
	const char* uvSetName = nullptr;
	FbxStringList uvSetNameList;
	mesh->GetUVSetNames(uvSetNameList);
	if (uvSetNameList.GetCount() > 0)
	{
		uvSetName = uvSetNameList.GetStringAt(0);
	}
	else
	{
		ERROR("ModelLoader", "ProcessMesh", "No UV set found in the mesh")
			return;
	}

	//Obitne los vèrtices e ìndices
	for (int i = 0; i < polygonCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SimpleVertex vertex;

			//Obtiene las posicones del vertex
			int controlPointIndex = mesh->GetPolygonVertex(i, j);
			FbxVector4 pos = mesh->GetControlPointAt(controlPointIndex);
			vertex.Pos = XMFLOAT3(static_cast<float>(pos[0]), static_cast<float>(pos[1]), static_cast<float>(pos[2]));

			//Obtiene las coordenadas de textira
			FbxVector2 texCoord;
			bool unmapped;
			mesh->GetPolygonVertexUV(i, j, uvSetName, texCoord, unmapped);
			vertex.Tex = XMFLOAT2(static_cast<float>(texCoord[0]), static_cast<float>(texCoord[1]));

			//Agrega el vertex a la lista
			vertices.push_back(vertex);
			indices.push_back(vertices.size() - 1);
		}
	}
}

