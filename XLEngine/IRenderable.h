#pragma once

#include "Common.h"

// todo: namespace 도입

class IRenderable
{

public:
	virtual void Initialize() = 0;
	virtual void Build() = 0;
	virtual void RenderUpdate() = 0;
	virtual void Draw() = 0;

protected:
	virtual void Bind() = 0;
	virtual void Unbind() = 0;

protected:
	// todo: 리소스와 빌드 로직이 혼재되어있는 것을 해소
	// 하지만, 게임오브젝트 종속적인데 어떻게 해결해야하나
	virtual void GetD3DResources() = 0;
	virtual HRESULT BuildVertexBuffer() = 0;
	virtual HRESULT BuildIndexBuffer() = 0;
	virtual HRESULT BuildInputLayout() = 0;
	virtual void BuildShader() = 0;

private:
	int VBSize = 0;
	int IBSize = 0;

protected:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	/// Buffer, InputLayout
	// Vertex Buffer
	com_ptr<ID3D11Buffer> vertexBuffer;
	vector<ID3D11Buffer*> VBs;

	// Index Buffer
	com_ptr<ID3D11Buffer> indexBuffer;
	vector<ID3D11Buffer*> IBs;

	// Constant Buffer
	com_ptr<ID3D11Buffer> constantBuffer;

	// Input Layout
	com_ptr<ID3D11InputLayout> inputLayout;

	// vs bytecode
	com_ptr<ID3DBlob> vertexShaderByteCode; // compiled shader bytecodes
	com_ptr<ID3DBlob> pixelShaderByteCode;


	com_ptr<ID3D11VertexShader> vertexShader;
	com_ptr<ID3D11PixelShader> pixelShader;


	HRESULT result;
};

