#include "Cube.h"

Cube::Cube(float _size, XMFLOAT4 _color)
	: size(_size), color(_color)
{
	vertices.push_back(Vertex{ {-1.0, 1.0, 0.0f}, {}, color });
	vertices.push_back(Vertex{ {1.0, 1.0, 0.0f}, {}, color });
	vertices.push_back(Vertex{ {-1.0, -1.0, 0.0f}, {}, color });
	vertices.push_back(Vertex{ {1.0, -1.0, 0.0f}, {}, color });
	vertices.push_back(Vertex{ {-1.0, 1.0, 1.0f}, {}, color });
	vertices.push_back(Vertex{ {1.0, 1.0, 1.0f}, {}, color });
	vertices.push_back(Vertex{ {-1.0, -1.0, 1.0f}, {}, color });
	vertices.push_back(Vertex{ {1.0, -1.0, 1.0f}, {}, color });
}

void Cube::SetPosition(XMFLOAT3 _value)
{
	wPosition = _value;
}

void Cube::Translate(XMFLOAT3 _value)
{
	wPosition.x += _value.x;
	wPosition.y += _value.y;
	wPosition.z += _value.z;
}

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

void Cube::Scale(XMFLOAT3 _value)
{

}

//////
//////
/////// Game Scene
void Cube::Start()
{
	for (auto& vertex : vertices)
	{
		vertex.localPosition.x *= size;
		vertex.localPosition.y *= size;
		vertex.localPosition.z *= size;

		vertex.worldPosition.x = vertex.localPosition.x + wPosition.x;
		vertex.worldPosition.y = vertex.localPosition.y + wPosition.y;
		vertex.worldPosition.z = vertex.localPosition.z + wPosition.z;

		vertex.color = color;
	}

}

void Cube::Update()
{
	for (auto& vertex : vertices)
	{
		vertex.worldPosition.x = vertex.localPosition.x + wPosition.x;
		vertex.worldPosition.y = vertex.localPosition.y + wPosition.y;
		vertex.worldPosition.z = vertex.localPosition.z + wPosition.z;
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
	BuildShader();
	BuildInputLayout();
}

void Cube::RenderUpdate()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
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
		vertices.size() * sizeof(Cube::Vertex),
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		NULL,
		NULL,
		sizeof(Cube::Vertex)
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
	UINT strides = sizeof(Cube::Vertex);
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, VBs.size(), VBs.data(), &strides, &offsets);
	deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);

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