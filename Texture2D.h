#pragma once

#include"IFile.h"
#include"IMemory.h"

using namespace Microsoft::WRL;

namespace Mydx
{
	typedef struct Texture2D : IMemory, IFile
	{
		void ClearRenderTarget(DirectX::XMVECTORF32 clearColor);
		void ClearDepthStencil();

		inline unsigned int GetWidth() const { mTextureDesc.Width; }
		inline unsigned int GetHeight() const { mTextureDesc.Height; }

		ID3D11RenderTargetView* GetRenderTarget() const { return mRenderTarget.Get(); }
		ID3D11ShaderResourceView* GetShaderResource() const { return mShaderResource.Get(); }
		ID3D11UnorderedAccessView* GetUnorderedAccess() const { return mUnorderedAccess.Get(); }
		ID3D11DepthStencilView* GetDepthStencil() const { return mDepthStencil.Get(); }

		Texture2D(D3D11_TEXTURE2D_DESC& texDesc, bool bSwapChain = false, bool bCubemap = false);
		Texture2D(const Texture2D& rhs);
		Texture2D(const char* path);

		~Texture2D();
	private:

		bool generateFromSwapChain();
		bool generateViews();
		virtual bool Generate() override;
		virtual void Release() override;

		D3D11_TEXTURE2D_DESC mTextureDesc;
		D3D11_RENDER_TARGET_VIEW_DESC mRenderTargetDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC mShaderResourceDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC mDepthStencilDesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC mUnorderedAccessDesc;
		
		ComPtr<ID3D11Texture2D> mTexture = nullptr;
		ComPtr<ID3D11RenderTargetView> mRenderTarget = nullptr;
		ComPtr<ID3D11DepthStencilView> mDepthStencil = nullptr;

		ComPtr<ID3D11ShaderResourceView> mShaderResource = nullptr;
		ComPtr<ID3D11UnorderedAccessView> mUnorderedAccess = nullptr;



		// IFile을(를) 통해 상속됨
		virtual bool Load(const char* path) override;

	} Tex2D;
}