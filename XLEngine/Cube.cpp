#include "XLMath.h"
#include "Cube.h"
#include "DirectXMath.h"

using namespace XL::Math;

void Cube::SetPosition(float x, float y, float z)
{
	//wPosition = Vector3(x, y, z);
	
	translation = XMMatrixTranslation(x, y, z);
}

void Cube::Translate(float x, float y, float z)
{
	//Vector3 vector = Vector3(x, y, z);
	//wPosition = wPosition + vector;

	//Matrix translation(vector);
	
	translation = XMMatrixMultiply(translation, XMMatrixTranslation(x, y, z));
	//translation = XMMatrixTranslation(x, y, z);
}

void Cube::Rotate(float x, float y, float z)
{
	rotation = XMMatrixRotationRollPitchYaw(x, y, z);	
}

void Cube::Scale(float x, float y, float z)
{
	scale = XMMatrixScaling(x, y, z);
}

// todo: 수학 라이브러리에 직접 구현해보기?
//void Cube::Yaw(float _angle)
//{
//	// 각도를 라디안으로 변환
//	float radian = _angle * 3.14159265358979323846f / 180.0f;
//
//	float cosTheta = cos(radian);
//	float sinTheta = sin(radian);
//
//	// 모든 버텍스에 회전 적용
//	for (auto& vertex : vertices)
//	{
//
//		float x = vertex.localPosition.x;
//		float z = vertex.localPosition.x;
//
//		float newX = x * cosTheta + z * sinTheta;
//		float newZ = -x * sinTheta + z * cosTheta;
//
//		vertex.localPosition.x = newX;
//		vertex.localPosition.z = newZ;
//
//
//	}
//}
//
//void Cube::Pitch(float _angle)
//{
//
//}
//
//void Cube::Roll(float _angle)
//{
//
//}
//
//void Cube::Scale(XMFLOAT3 _value)
//{
//
//}

//////
//////
/////// Game Scene
void Cube::Start()
{
	worldMatrix = XMMatrixMultiply(scale, XMMatrixMultiply(rotation, translation));
	viewMatrix = XMMatrixIdentity();


	WVPMatrix = XMMatrixMultiply(worldMatrix, viewMatrix);

	for (auto& vertex : vertices)
	{

		vertex.localPosition*= size;

		vertex.worldPosition = vertex.localPosition + wPosition;

		vertex.color = color;
	}

}

void Cube::Update()
{
	worldMatrix = XMMatrixMultiply(scale, XMMatrixMultiply(rotation, translation));
	viewMatrix = XMMatrixIdentity();
	projectionMatrix = XMMatrixPerspectiveFovLH(20.0f, static_cast<float>(resources.ScreenWidth / resources.ScreenHeight), 0.0001f, 100.0f);

	WVPMatrix = XMMatrixMultiply(worldMatrix, XMMatrixMultiply(viewMatrix, projectionMatrix));

	for (auto& vertex : vertices)
	{
		vertex.worldPosition = vertex.localPosition + wPosition;
	}
}

void Cube::Finish()
{

}


///////////////////////////
//////////////////////////
/////////////RenderScene

void Cube::Initialize()
{
	GetD3DResources();
}

void Cube::Build()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
	BuildConstantBuffer();
	BuildShader();
	BuildInputLayout();
}

void Cube::RenderUpdate()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
	BuildConstantBuffer();
	BuildShader();
	BuildInputLayout();
}

void Cube::Draw()
{
	Bind();

	deviceContext->DrawIndexed(36, 0, 0);

	Unbind();
}


void Cube::GetD3DResources()
{
	device = resources.device.get();
	deviceContext = resources.deviceContext.get();
}

HRESULT Cube::BuildVertexBuffer()
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

HRESULT Cube::BuildIndexBuffer()
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

HRESULT Cube::BuildConstantBuffer()
{
	D3D11_BUFFER_DESC cbDesc
	{
		sizeof(WVPMatrix),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_CONSTANT_BUFFER,
		NULL,
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

HRESULT Cube::BuildInputLayout()
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

void Cube::BuildShader()
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

void Cube::Bind()
{
	BuildVertexBuffer();

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

void Cube::Unbind()
{
	//wVertices.clear();

	//for (auto& vertex : lVertices)
	//{
	//	wVertices.emplace_back(vertex);
	//}

}