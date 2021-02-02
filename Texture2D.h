#pragma once

#include"IMemory.h"

using namespace Microsoft::WRL;

namespace Mydx
{
	typedef struct Texture2D : IMemory
	{
		virtual bool Generate() override;
		virtual void Release() override;

		Texture2D(D3D11_TEXTURE2D_DESC& texDesc);
		~Texture2D();
	private:

		D3D11_TEXTURE2D_DESC mTextureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC mRenderTargetDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC mShaderResourceDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC mDepthStencilDesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC mUnordredAccessDesc;

		ComPtr<ID3D11Texture2D> mTexture = nullptr;
		ComPtr<ID3D11RenderTargetView> mRenderTarget = nullptr;
		ComPtr<ID3D11DepthStencilView> mDepthStencil = nullptr;

		ComPtr<ID3D11ShaderResourceView> mShaderResource = nullptr;
		ComPtr<ID3D11UnorderedAccessView> mUnorderedAccess = nullptr;

	} Tex2D;
}