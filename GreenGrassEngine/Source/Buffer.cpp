#include "Buffer.h"
#include "Device.h"
#include "DeviceContext.h"
#include "MeshComponent.h"

// Private method to create buffer


void Buffer::createBuffer(Device& device,
						  D3D11_BUFFER_DESC& desc, 
						  D3D11_SUBRESOURCE_DATA* initData)
{ 
    HRESULT hr = device.CreateBuffer(&desc, initData, &m_buffer);
    if (FAILED(hr)) {
        ERROR("Buffer", "createBuffer", "CHECK FOR method createBuffer()");
    }
}

void
Buffer::init(Device device, MeshComponent mesh, unsigned int bindFlag) 
{
    if (device.m_device == nullptr) {
        ERROR("Buffer", "init", "CHECK FOR Device device");
    }

    // Validate mesh data based on bindFlag que no estèn vacìos pues 
    if ((bindFlag == D3D11_BIND_VERTEX_BUFFER && mesh.m_vertex.empty()) ||
        (bindFlag == D3D11_BIND_INDEX_BUFFER && mesh.m_index.empty())) {
        ERROR("Buffer", "init", "CHECK FOR Mesh mesh");
    }
    //Define info del buffer  
    D3D11_BUFFER_DESC desc = {};
    D3D11_SUBRESOURCE_DATA InitData = {};

    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.CPUAccessFlags = 0;
    m_bindFlag = bindFlag;

    if (bindFlag == D3D11_BIND_VERTEX_BUFFER) 
    {
        m_stride = sizeof(SimpleVertex);                                            /*El espacio de los modelos */
        desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_vertex.size());  /*El ancho que recibe el stride, que es del tamaño de la estructura*/
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        InitData.pSysMem = mesh.m_vertex.data();
    }
    else if (bindFlag == D3D11_BIND_INDEX_BUFFER) 
    {
        m_stride = sizeof(unsigned int);
        desc.ByteWidth = m_stride * static_cast<unsigned int>(mesh.m_index.size());
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        InitData.pSysMem = mesh.m_index.data();
    }
    //Si todo sale bien se crea el buffer 
    createBuffer(device, desc, &InitData);
}

void Buffer::init(Device device, unsigned int ByteWidth)
{
    //Checa si los paràmetros del init estàn bien
     if (device.m_device == nullptr || ByteWidth == 0) {
        ERROR("Buffer", "init", "CHECK FOR parameters");
    }

    m_stride = ByteWidth;

    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = ByteWidth;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    m_bindFlag = desc.BindFlags;

    createBuffer(device, desc, nullptr);
}

void Buffer::update(DeviceContext& deviceContext, 
                    unsigned int DstSubresource, 
                    const D3D11_BOX* pDstBox, 
                    const void* pSrcData, 
                    unsigned int SrcRowPitch, 
                    unsigned int SrcDepthPitch)
{
    deviceContext.UpdateSubresource(m_buffer,
                                    DstSubresource,
                                    pDstBox,
                                    pSrcData,
                                    SrcRowPitch,
                                    SrcDepthPitch);
}

//Este render establece la memoria para que se visualice
void 
Buffer::render(DeviceContext& deviceContext, 
               unsigned int StartSlot, 
               unsigned int NumBuffers)
{
    switch (m_bindFlag) /*bindFlag, es el còmo se va a utilizar un buffer, VERTEX_BUFFER o CONSTANT_BUFFER*/
    {
    case D3D11_BIND_VERTEX_BUFFER:
        deviceContext.IASetVertexBuffers(StartSlot,
                                         NumBuffers,
                                         &m_buffer,  /*Nuestro buffer*/
                                         &m_stride,  /*Tamaño del buffer*/
                                         &m_offset); /*Còmo se va a desplazar el buffer*/
        break;
    case D3D11_BIND_CONSTANT_BUFFER:
        deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot,
                                                            NumBuffers,
                                                            &m_buffer);
        break;
    default:
        ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");
        break;
    }
}

void 
Buffer::render(DeviceContext& deviceContext, 
               DXGI_FORMAT format)
{
    //Este render registra los valores que van a acomodar los valores en el espacio
    if (m_bindFlag == D3D11_BIND_INDEX_BUFFER) {
        deviceContext.IASetIndexBuffer(m_buffer, format, m_offset);
    }
    else {
        ERROR("Buffer", "render", "CHECK FOR Unsupported BindFlag");
    }
}

//WEste es especìfico para modelos 
void 
Buffer::renderModel(DeviceContext& deviceContext, 
                    unsigned int StartSlot, 
                    unsigned int NumBuffers)
{
    deviceContext.m_deviceContext->VSSetConstantBuffers(StartSlot,
                                                        NumBuffers,
                                                        &m_buffer);

    deviceContext.m_deviceContext->PSSetConstantBuffers(StartSlot,
                                                        NumBuffers,
                                                        &m_buffer);
}

void Buffer::destroy()
{
    SAFE_RELEASE(m_buffer);
}