#include "Cube.h"

void Cube::Initialize()
{
	device = XLD3DResources::GetDevice();
	deviceContext = XLD3DResources::GetDeviceContext();
}

void Cube::Translate(XMFLOAT3 _value)
{
	localPosition.x += _value.x;
	localPosition.y += _value.y;
	localPosition.z += _value.z;
}

void Cube::Rotation(XMFLOAT3 _value)
{
}

void Cube::Scale(XMFLOAT3 _value)
{
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

HRESULT Cube::BuildInputLayout(ID3DBlob*_vsByteCode)
{
	// Create Input Layout
	D3D11_INPUT_ELEMENT_DESC intputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	result = device->CreateInputLayout
	(
		intputElementDesc,
		2,
		_vsByteCode->GetBufferPointer(),
		_vsByteCode->GetBufferSize(),
		inputLayout.put()
	);

	return result;
}

void Cube::Build(ID3DBlob* _vsByteCode)
{
	Initialize();
	BuildVertexBuffer();
	BuildIndexBuffer();
	BuildInputLayout(_vsByteCode);
}

void Cube::Draw()
{
	Bind();

	deviceContext->DrawIndexed(36, 0, 0);

	UnBind();
}

void Cube::Bind()
{
	for (auto& vertex : vertices)
	{
		// Update Position and Color
		vertex.position.x *= size;
		vertex.position.y *= size;
		vertex.position.z *= size;

		vertex.color = color;

		// Update Translate
		vertex.position.x += localPosition.x;
		vertex.position.y += localPosition.y;
		vertex.position.z += localPosition.z;
	}

	BuildVertexBuffer();

	// binding InputLayout to pipline IA Stage 
	deviceContext->IASetInputLayout(inputLayout.get());

	// binding Buffers to pipeline IA Stage
	UINT strides = sizeof(Cube::Vertex);
	UINT offsets = 0;
	deviceContext->IASetVertexBuffers(0, VBs.size(), VBs.data(), &strides, &offsets);
	deviceContext->IASetIndexBuffer(indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);
}

void Cube::UnBind()
{
	for (auto& vertex : vertices)
	{
		vertex.position.x /= size;
		vertex.position.y /= size;
		vertex.position.z /= size;
	}
}
