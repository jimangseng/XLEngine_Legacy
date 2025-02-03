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
			// 자원 생성 관련 함수
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