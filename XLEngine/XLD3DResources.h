#pragma once

#include "Common.h"

class XLD3DResources
{
private:
	XLD3DResources() {}
	XLD3DResources(const XLD3DResources& ref) = delete;
	XLD3DResources& operator= (const XLD3DResources& ref) = delete;
	~XLD3DResources() {}

public:
	//static Helper& GetInstance()
	//{
	//	static Helper instance;

	//	return instance;
	//}

	static ID3D11Device* const GetDevice()
	{
		return device.get();
	}

	static ID3D11DeviceContext* const GetDeviceContext()
	{
		return deviceContext.get();
	}

	static ID3D11Device** PutDevice()
	{
		return device.put();
	}

	static ID3D11DeviceContext** PutDeviceContext()
	{
		return deviceContext.put();
	}

private:
	static com_ptr<ID3D11Device> device;
	static com_ptr<ID3D11DeviceContext> deviceContext;
};

