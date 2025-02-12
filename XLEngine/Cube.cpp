#include "Cube.h"
#include "XLMath.h"
#include "DirectXMath.h"

using namespace XL::Math;

XL::GameObjects::Cube::Cube()
	: Cube(0.1f, { 1.0f, 1.0f, 1.0f, 1.0f })
{
}

XL::GameObjects::Cube::Cube(XL::Math::Vector4 _color)
	: Cube(0.1f, _color)
{
}

XL::GameObjects::Cube::Cube(float _size, XL::Math::Vector4 _color)
	: size(_size), color(_color)
{
	vertices.emplace_back(Vertex{ {-1.0, 1.0, 0.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {1.0, 1.0, 0.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {-1.0, -1.0, 0.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {1.0, -1.0, 0.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {-1.0, 1.0, 1.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {1.0, 1.0, 1.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {-1.0, -1.0, 1.0f}, {}, {} });
	vertices.emplace_back(Vertex{ {1.0, -1.0, 1.0f}, {}, {} });

}

void XL::GameObjects::Cube::UpdateMatrices()
{
	float aspectRatio = static_cast<float>(resources.ScreenWidth / resources.ScreenHeight);

	worldMatrix = XMMatrixMultiply(scale, XMMatrixMultiply(rotation, translation));
	viewMatrix = XMMatrixIdentity();
	projectionMatrix = XMMatrixPerspectiveFovLH(20.0f, aspectRatio, 0.0001f, 100.0f);

	WVPMatrix = XMMatrixMultiply(worldMatrix, XMMatrixMultiply(viewMatrix, projectionMatrix));
}

//////
//////
/////// Game Scene
void XL::GameObjects::Cube::InitializeGameObject()
{
	for (auto& vertex : vertices)
	{
		vertex.localPosition *= size;
		vertex.color = color;
	}

	UpdateMatrices();
}

void XL::GameObjects::Cube::UpdateGameObject()
{
	UpdateMatrices();
}

void XL::GameObjects::Cube::FinalizeGameObject()
{
}

///////////////////////////
//////////////////////////
/////////////RenderScene

void XL::GameObjects::Cube::InitializeRendeable()
{
	GetD3DResources();
	BuildVertexBuffer();
	BuildIndexBuffer();
	BuildConstantBuffer();
	BuildShader();
	BuildInputLayout();
}

void XL::GameObjects::Cube::UpdateRenderable()
{
	deviceContext->UpdateSubresource(constantBuffer.get(), 0, NULL, &WVPMatrix, 0, 0);
}

void XL::GameObjects::Cube::DrawRenderable()
{
	Bind();

	deviceContext->DrawIndexed(36, 0, 0);

	Unbind();
}

void XL::GameObjects::Cube::FinalizeRenderable()
{
}

void XL::GameObjects::Cube::GetD3DResources()
{
	device = resources.device.get();
	deviceContext = resources.deviceContext.get();
}

HRESULT XL::GameObjects::Cube::BuildVertexBuffer()
{
	D3D11_BUFFER_DESC vbDesc
	{
		(UINT)vertices.size() * sizeof(Vertex),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		NULL,
		NULL,
		sizeof(Vertex)
	};

	D3D11_SUBRESOURCE_DATA vbData
	{
		vertices.data(),
		0,
		0
	};

	result = device->CreateBuffer(&vbDesc, &vbData, vertexBuffer.put());

	VBs.clear(); //
	VBs.emplace_back(vertexBuffer.get());

	return result;
}

HRESULT XL::GameObjects::Cube::BuildIndexBuffer()
{

	D3D11_BUFFER_DESC ibDesc
	{
		sizeof(indices),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_INDEX_BUFFER,
		NULL,
		NULL,
		sizeof(int)
	};

	D3D11_SUBRESOURCE_DATA ibData
	{
		indices,
		0,
		0
	};

	result = device->CreateBuffer(&ibDesc, &ibData, indexBuffer.put());

	IBs.emplace_back(indexBuffer.get());

	return result;
}

HRESULT XL::GameObjects::Cube::BuildConstantBuffer()
{
	D3D11_BUFFER_DESC cbDesc =
	{
		sizeof(WVPMatrix),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_CONSTANT_BUFFER,
		NULL,
		NULL,
		sizeof(XMMATRIX)
	};

	D3D11_SUBRESOURCE_DATA cbData =
	{
		&WVPMatrix,
		0,
		0
	};

	result = device->CreateBuffer(&cbDesc, &cbData, constantBuffer.put());

	return result;
}

HRESULT XL::GameObjects::Cube::BuildInputLayout()
{
	// Create Input Layout
	D3D11_INPUT_ELEMENT_DESC intputElementDesc[] =
	{
		{"LOCALPOSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	result = device->CreateInputLayout
	(
		intputElementDesc,
		3,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		inputLayout.put()
	);

	return result;
}

void XL::GameObjects::Cube::BuildShader()
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

}

void XL::GameObjects::Cube::Bind()
{
	// binding InputLayout to pipline IA Stage 
	deviceContext->IASetInputLayout(inputLayout.get());

	// binding Buffers to pipeline IA Stage
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, (UINT)VBs.size(), VBs.data(), &strides, &offsets);
	deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

	ID3D11Buffer* CBs[1] = { constantBuffer.get() };

	deviceContext->VSSetConstantBuffers(0, 1, CBs);
	deviceContext->VSSetShader(vertexShader.get(), NULL, NULL);
	deviceContext->PSSetShader(pixelShader.get(), NULL, NULL);
}

void XL::GameObjects::Cube::Unbind()
{

}