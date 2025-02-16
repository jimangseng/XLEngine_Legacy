#include "Mesh.h"
#include "../WICTextureLoader/WICTextureLoader11.h"

void XL::Components::Mesh::GetD3DResources()
{
	device = resources.device.get();
	deviceContext = resources.deviceContext.get();
}

HRESULT XL::Components::Mesh::BuildVertexBuffer()
{
	D3D11_BUFFER_DESC vbDesc
	{
		vertices.size * vertices.count,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		NULL,
		NULL,
		vertices.size
	};

	D3D11_SUBRESOURCE_DATA vbData
	{
		vertices.data,
		0,
		0
	};

	result = device->CreateBuffer(&vbDesc, &vbData, vertexBuffer.put());

	VBs.emplace_back(vertexBuffer.get());

	return result;
}

HRESULT XL::Components::Mesh::BuildIndexBuffer()
{

	D3D11_BUFFER_DESC ibDesc
	{
		static_cast<UINT>(indices.size() * sizeof(UINT)),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_INDEX_BUFFER,
		NULL,
		NULL,
		sizeof(UINT)
	};

	D3D11_SUBRESOURCE_DATA ibData
	{
		indices.data(),
		0,
		0
	};

	result = device->CreateBuffer(&ibDesc, &ibData, indexBuffer.put());

	IBs.emplace_back(indexBuffer.get());

	return result;
}

HRESULT XL::Components::Mesh::BuildConstantBuffer()
{
	D3D11_BUFFER_DESC cbDesc
	{
		sizeof(WVPMatrix),
		D3D11_USAGE_DYNAMIC,
		D3D11_BIND_CONSTANT_BUFFER,
		D3D11_CPU_ACCESS_WRITE,
		NULL,
		sizeof(XMMATRIX)
	};

	D3D11_SUBRESOURCE_DATA cbData
	{
		&WVPMatrix,
		0,
		0
	};

	result = device->CreateBuffer(&cbDesc, &cbData, constantBuffer.put());

	return result;
}

HRESULT XL::Components::Mesh::BuildInputLayout()
{
	result = device->CreateInputLayout
	(
		inputElementDesc.data(),
		static_cast<UINT>(inputElementDesc.size()),
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		inputLayout.put()
	);

	return result;
}

HRESULT XL::Components::Mesh::BuildShader()
{
	// Loading Shader ByteCode
	result = D3DReadFileToBlob(TEXT("../Shader/VertexShader.cso"), vertexShaderByteCode.put());
	result = D3DReadFileToBlob(TEXT("../Shader/PixelShader.cso"), pixelShaderByteCode.put());
	// Create Vertex Shader
	result = device->CreateVertexShader
	(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		NULL,
		vertexShader.put()
	);

	// Create Pixel Shader
	result = device->CreatePixelShader
	(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		NULL,
		pixelShader.put()
	);

	return result;
}

HRESULT XL::Components::Mesh::BuildTexture()
{
	result = CreateWICTextureFromFile
	(	// todo:
		device,
		texturePath,
		(ID3D11Resource**)(texture.put()),
		(shaderResourceView.put())
	);

	//D3D11_TEXTURE2D_DESC desc =
	//{
	//	256,
	//	256,
	//	0,
	//	1,
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	{ 1, 0 },
	//	D3D11_USAGE_DEFAULT,
	//	D3D11_BIND_SHADER_RESOURCE,
	//	D3D11_CPU_ACCESS_READ,
	//	0
	//};
	//result = device->CreateTexture2D(&desc, nullptr, texture.put());

	//D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc =
	//{
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	D3D11_SRV_DIMENSION_TEXTURE2D,
	//	{0, -1}
	//};

	//device->CreateShaderResourceView(texture.get(), &SRVDesc, shaderResourceView.put());

	return result;
}

void XL::Components::Mesh::Bind()
{
	// binding InputLayout to pipline IA Stage 
	deviceContext->IASetInputLayout(inputLayout.get());

	// binding Buffers to pipeline IA Stage
	UINT strides = vertices.size;
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, static_cast<UINT>(VBs.size()), VBs.data(), &strides, &offsets);
	deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

	ID3D11Buffer* CBs[1] = { constantBuffer.get() };

	deviceContext->VSSetConstantBuffers(0, 1, CBs);
	deviceContext->VSSetShader(vertexShader.get(), NULL, NULL);
	deviceContext->PSSetShader(pixelShader.get(), NULL, NULL);

	ID3D11ShaderResourceView* SRVs[1] = { shaderResourceView.get() };
	deviceContext->PSSetShaderResources(0, 1, SRVs);

	ID3D11SamplerState* samplerStates[1] = { resources.samplerState.get() };
	deviceContext->PSSetSamplers(0, 1, samplerStates);
}

void XL::Components::Mesh::Unbind()
{

}

void XL::Components::Mesh::Initialize()
{
	GetD3DResources();
	BuildVertexBuffer();
	BuildIndexBuffer();
	BuildConstantBuffer();
	BuildShader();
	BuildInputLayout();
	BuildTexture();
}

void XL::Components::Mesh::Update()
{
	// 자원(상수버퍼)을 변수에 맵핑
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	deviceContext->Map(constantBuffer.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// CPU가 직접 상수 버퍼 데이터를 갱신
	memcpy(mappedResource.pData, &WVPMatrix, sizeof(WVPMatrix));

	// 맵핑 해제
	deviceContext->Unmap(constantBuffer.get(), 0);
}

void XL::Components::Mesh::Draw()
{
	Bind();

	deviceContext->DrawIndexed(static_cast<UINT>(indices.size()), 0, 0);

	Unbind();
}

void XL::Components::Mesh::Finalize()
{
}