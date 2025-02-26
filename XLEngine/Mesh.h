#pragma once

#include <vector>
#include "Resources.h"
#include <d3d11.h>
#include "assimp\vector3.h"
#include "assimp\vector2.h"

namespace XL
{
	namespace Components
	{
		struct Vertices
		{
			void* data;
			UINT count;
			UINT size;
		};

		struct aiVertex
		{
			aiVector3D vertex;
			aiVector2D texCoord;
		};

		class Mesh
		{
		public:

			vector<XL::Components::aiVertex> aiVertexdata;
			//vector<aiVector3D> aiVertices;
			//vector<aiVector3D> aiTexCoords;
			vector<UINT> aiIndices;

			Vertices vertices;
			vector<UINT> indices;
			vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
			const wchar_t* texturePath;

		private:
			XMMATRIX WVPMatrix = XMMatrixIdentity();

		public:
			template <typename Vertex>
			void SetVertexBufferData(vector<Vertex>& _vertices)
			{
				vertices.data = _vertices.data();
				vertices.count = static_cast<UINT>(_vertices.size());
				vertices.size = sizeof(Vertex);
			}
			void SetIndexBufferData(vector<UINT>& _indices)
			{
				indices = _indices;
			}
			void SetInputLayout(vector<D3D11_INPUT_ELEMENT_DESC>& _inputElementDesc)
			{
				inputElementDesc = _inputElementDesc;
			}
			void SetMatrix(XMMATRIX _matrix) { WVPMatrix = _matrix; }
			void SetTexturePath(const wchar_t* _path) { texturePath = _path; }


		public:
			void Bind();
			void Unbind();
		private:
			void GetD3DResources();
			HRESULT BuildVertexBuffer();
			HRESULT BuildIndexBuffer();
			HRESULT BuildConstantBuffer();
			HRESULT BuildInputLayout();
			HRESULT BuildShader();
			HRESULT BuildTexture();

		public:
			void Initialize();
			void Update();
			void Draw();
			void Finalize();

		private:
			ID3D11Device* device;
			ID3D11DeviceContext* deviceContext;

			/// Buffer, InputLayout
			// Vertex Buffer
			com_ptr<ID3D11Buffer> vertexBuffer;
			vector<ID3D11Buffer*> VBs;

			// Index Buffer
			com_ptr<ID3D11Buffer> indexBuffer;
			vector<ID3D11Buffer*> IBs;

			// Input Layout
			com_ptr<ID3D11InputLayout> inputLayout;

			// constant Buffer
			com_ptr<ID3D11Buffer> constantBuffer;

			// vs bytecode
			com_ptr<ID3DBlob> vertexShaderByteCode; // compiled shader bytecodes
			com_ptr<ID3DBlob> pixelShaderByteCode;

			com_ptr<ID3D11VertexShader> vertexShader;
			com_ptr<ID3D11PixelShader> pixelShader;

			com_ptr<ID3D11Texture2D> texture;
			com_ptr<ID3D11ShaderResourceView> shaderResourceView;

			HRESULT result;

		private:
			XL::Graphics::D3D11::Resources& resources = XL::Graphics::D3D11::Resources::GetInstance();
		};
	}
}