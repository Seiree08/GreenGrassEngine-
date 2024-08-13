#include "ShaderProgram.h"
#include "Device.h"
#include "DeviceContext.h"

void 
ShaderProgram::init(Device device, 
                         std::string fileName, 
                         std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    //Verifica que el recurso device est� correcto o bine creado
    if (device.m_device == nullptr) {
        ERROR("ShaderProgram", "init", "CHECK FOR Device device");
        exit(1);
    }
    //Verifica que el vector sea v�lido
    else if (Layout.size() <= 1) {
        ERROR("ShaderProgram", "init", "CHECK FOR std::vector<D3D11_INPUT_ELEMENT_DESC> Layout.size()");
        exit(1);
    }
    // Store the shade file name
    m_shaderFileName = fileName;
    // Create the vertex shader
    CreateShader(device, ShaderType::VERTEX_SHADER);
    // Create the Input Layout
    CreateInputLayout(device, Layout);
    // Create the pixel shader
    CreateShader(device, ShaderType::PIXEL_SHADER);
}

void 
ShaderProgram::update()
{
}

void 
ShaderProgram::render(DeviceContext& deviceContext)
{
    // Establecer el InputLayout
    m_inputLayout.render(deviceContext);
    // // Establecer los shaders
    deviceContext.VSSetShader(m_VertexShader, nullptr, 0);
    deviceContext.PSSetShader(m_PixelShader, nullptr, 0);
}

void 
ShaderProgram::destroy()
{
    SAFE_RELEASE(m_VertexShader);
    m_inputLayout.destroy();
    SAFE_RELEASE(m_PixelShader);
}

HRESULT 
ShaderProgram::CompileShaderFromFile(char* szFileName,
								                             LPCSTR szEntryPoint, 
								                             LPCSTR szShaderModel, 
								                             ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
        if (pErrorBlob != NULL)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void 
ShaderProgram::CreateInputLayout(Device device, 
                                      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout)
{
    m_inputLayout.init(device, Layout, m_vertexShaderData);
    m_vertexShaderData->Release();
}

void 
ShaderProgram::CreateShader(Device device, 
                                 ShaderType type)
{
    HRESULT hr = S_OK;
    //Este es un recurso pa' saber si hacemos pixelShader o vertexSahder
    ID3DBlob* shaderData = nullptr;
    const char* shaderEntryPoint = (type == PIXEL_SHADER) ? "PS" : "VS";
    const char* shaderModel = (type == PIXEL_SHADER) ? "ps_4_0" : "vs_4_0";

    // Compile the shader
    hr = CompileShaderFromFile(m_shaderFileName.data(),
                               shaderEntryPoint,
                               shaderModel,
                               &shaderData);
    //Si el shader no se com�ila bien manda error o no se asigna bien el shaderEntryPoint o el shaderModel
    if (FAILED(hr)) {
        MessageBox(nullptr, "The FX file cannot be compiled. Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR CompileShaderFromFile()");
        exit(1);
    }
    // Create the shader seg�in el dato asignado
    if (type == PIXEL_SHADER) {
        hr = device.CreatePixelShader(shaderData->GetBufferPointer(),
                                      shaderData->GetBufferSize(),
                                      nullptr,
                                      &m_PixelShader);
    }
    else {
        hr = device.CreateVertexShader(shaderData->GetBufferPointer(),
                                       shaderData->GetBufferSize(),
                                       nullptr,
                                       &m_VertexShader);
    }
    //  Si no se crea bien el shader y que cheque en ambos
    if (FAILED(hr)) 
    {
        shaderData->Release();
        ERROR("ShaderProgram", "CreateShader", "CHECK FOR device.CreateShader()");
        exit(1);
    }

    // Store the compiled shader data en los blobs, donde  da la referencia a inputlayout y que luego 
    //pixel tranforme lainfo en pixeles visibles en la pantalla
    if (type == PIXEL_SHADER) 
    {
        m_pixelShaderData = shaderData;
    }
    else 
    {
        m_vertexShaderData = shaderData;
    }
}