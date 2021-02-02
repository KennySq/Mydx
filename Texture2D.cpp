#include "pch.h"
#include "Texture2D.h"
#include"Hardware.h"

namespace Mydx
{
	bool Texture2D::Generate()
	{
		ID3D11Device* device = HW::GetDevice();
		
		auto result = device->CreateTexture2D(&mTextureDesc, nullptr, mTexture.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		DWORD bind = mTextureDesc.BindFlags;

		if (bind & D3D11_BIND_RENDER_TARGET)
		{
			auto result = device->CreateRenderTargetView(mTexture.Get(), &mRenderTargetDesc, mRenderTarget.GetAddressOf());
			assert(result == S_OK);
			
			if (result != S_OK)
				return false;
		}

		if (bind & D3D11_BIND_SHADER_RESOURCE)
		{
			auto result = device->CreateShaderResourceView(mTexture.Get(), &mShaderResourceDesc, mShaderResource.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}
		if (bind & D3D11_BIND_DEPTH_STENCIL)
		{
			auto result = device->CreateDepthStencilView(mTexture.Get(), &mDepthStencilDesc, mDepthStencil.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (bind & D3D11_BIND_UNORDERED_ACCESS)
		{
			auto result = device->CreateUnorderedAccessView(mTexture.Get(), &mUnordredAccessDesc, mUnorderedAccess.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		return true;
	}

	void Texture2D::Release()
	{
		if (mTexture != nullptr)
			mTexture->Release();

		if (mDepthStencil != nullptr)
			mDepthStencil->Release();

		if (mRenderTarget != nullptr)
			mRenderTarget->Release();

		if (mShaderResource != nullptr)
			mShaderResource->Release();

		if (mUnorderedAccess != nullptr)
			mUnorderedAccess->Release();
	}

	Texture2D::Texture2D(D3D11_TEXTURE2D_DESC& texDesc) : mTextureDesc(texDesc), mDepthStencilDesc(), mUnordredAccessDesc(), mRenderTargetDesc(), mShaderResourceDesc()
	{
		mRenderTargetDesc.Format = texDesc.Format;
		mRenderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		
		mDepthStencilDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		mDepthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		mUnordredAccessDesc.Format = texDesc.Format;
		mUnordredAccessDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

		mShaderResourceDesc.Format = texDesc.Format;
		mShaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	}

	Texture2D::~Texture2D()
	{}
}