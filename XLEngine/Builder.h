#pragma once

#include "Common.h"
#include "Resources.h"

namespace XL
{
	namespace D3D11
	{
		class Builder
		{
		public:
			Builder() = default;

			Builder(const Builder& _builder) = delete;
			Builder& operator = (const Builder& _builder) = delete;

		public:
			// �ڿ� ���� ���� �Լ�
			void BuildDeviceAndSwapChain();
			void SetRasterizerState();
			void BuildRenderTargetView();
			void BuildDepthStencilView();
			void SetDepthStencilState();
			void SetBlendState();

		private:
			HRESULT result;
		};
	}
}