//Aquí se manejan las librerías a utilizar, no es una clase

#pragma once
//Librerías STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>

//Librerías DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"

//Third Parties

/*Se usan macros pa' agilizar el proyecto*/

// MACRO for safe release of resources, libera memoria de forma segura
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
//#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)           \
//OutputDebugStringA(_ClassName);                                        \
//OutputDebugStringA(" : In Function : ");                               \
//OutputDebugStringA(_FunctionName);                                     \
//OutputDebugStringA(" : ");                                             \
//OutputDebugStringA(_OutputMessage);                                    \
//OutputDebugStringA("\n");

//Muestra los mensaje en consola pa' saber qué pasa en el proyecto
#define WARNING( s )                         \
{                                            \
   std::wostringstream os_;                  \
   os_ << s;                                 \
   OutputDebugStringW( os_.str().c_str() );  \
}

//Es para mostrar mensaje de manera ordenada
#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

//Es para mostrar errores de manera ordenada
#define ERROR( classObj, method, errorMSG )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges
{
    XMMATRIX mView;
};

struct CBChangeOnResize
{
    XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};
//
enum ShaderType
{
    PIXEL_SHADER = 0,
    VERTEX_SHADER = 1
};

enum ExtensionType
{
    DDS = 0,
    PNG = 1,
    JPG = 2
};

struct Mesh {
    std::string name;
    std::vector <SimpleVertex> vertex;
    std::vector <unsigned int> index;
    int numVertex;
    int numIndex;
};