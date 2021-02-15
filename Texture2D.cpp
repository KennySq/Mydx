#include "pch.h"
#include "Texture2D.h"
#include"Hardware.h"

namespace Mydx
{
	bool Texture2D::generateFromSwapChain()
	{
		if (mTexture != nullptr)
		{
			return false;
		}

		ID3D11Device* device = HW::GetDevice();
		IDXGISwapChain* swapChain = HW::GetSwapChain();

		auto result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mTexture.GetAddressOf()));
		assert(result == S_OK);

		if (result != S_OK)
		{
			return false;
		}

		return true;
	}
	bool Texture2D::generateViews()
	{
		ID3D11Device* device = HW::GetDevice();
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
			auto result = device->CreateUnorderedAccessView(mTexture.Get(), &mUnorderedAccessDesc, mUnorderedAccess.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		return true;
	}
	bool Texture2D::Generate()
	{
		if (mTexture != nullptr)
		{
			return false;
		}

		ID3D11Device* device = HW::GetDevice();
		
		auto result = device->CreateTexture2D(&mTextureDesc, nullptr, mTexture.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
		{
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

	void Texture2D::ClearRenderTarget(DirectX::XMVECTORF32 clearColor)
	{
		if (mRenderTarget == nullptr)
		{
			return;

		}

		static ID3D11DeviceContext* context = HW::GetContext();

		context->ClearRenderTargetView(mRenderTarget.Get(), clearColor);
	}

	void Texture2D::ClearDepthStencil()
	{
		if (mDepthStencil == nullptr)
		{
			return;

		}

		static ID3D11DeviceContext* context = HW::GetContext();

		context->ClearDepthStencilView(mDepthStencil.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	Texture2D::Texture2D(D3D11_TEXTURE2D_DESC& texDesc, bool bSwapChain) : mTextureDesc(texDesc), mDepthStencilDesc(), mUnorderedAccessDesc(), mRenderTargetDesc(), mShaderResourceDesc()
	{
		mRenderTargetDesc.Format = texDesc.Format;
		mRenderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		
		mDepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		mDepthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		mUnorderedAccessDesc.Format = texDesc.Format;
		mUnorderedAccessDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

		mShaderResourceDesc.Format = texDesc.Format;
		mShaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		if (bSwapChain == false)
		{
			Generate();
		}
		else
		{
			generateFromSwapChain();
		}

		generateViews();
	}

	Texture2D::Texture2D(const Texture2D& rhs)
	{
		ID3D11Device* device = HW::GetDevice();

		mTextureDesc = rhs.mTextureDesc;
		mDepthStencilDesc = rhs.mDepthStencilDesc;
		mShaderResourceDesc = rhs.mShaderResourceDesc;
		mUnorderedAccessDesc = rhs.mUnorderedAccessDesc;

		Generate();
		generateViews();
	}

	Texture2D::~Texture2D()
	{}


	//SwapChainTexture2D& SwapChainTexture2D::operator=(const Texture2D& rhs)
	//{
	//	this->mDepthStencil = rhs.mDepthStencil;
	//	this->mRenderTarget = rhs.mRenderTarget;
	//	this->mShaderResource = rhs.mShaderResource;
	//	this->mUnorderedAccess = rhs.GetUnorderedAccess();

	//	this->mTextureDesc = rhs.

	//	return *this;
	//}

	//bool SwapChainTexture2D::Generate()
	//{
	//	if (mTexture != nullptr)
	//		return false;

	//	ID3D11Device* device = HW::GetDevice();
	//	IDXGISwapChain* swapchain = HW::GetSwapChain();

	//	auto result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mTexture.GetAddressOf()));
	//	assert(result == S_OK);

	//	if (result != S_OK)
	//		return false;

	//	DWORD bind = mTextureDesc.BindFlags;

	//	if (bind & D3D11_BIND_RENDER_TARGET)
	//	{
	//		auto result = device->CreateRenderTargetView(mTexture.Get(), &mRenderTargetDesc, mRenderTarget.GetAddressOf());
	//		assert(result == S_OK);

	//		if (result != S_OK)
	//			return false;
	//	}

	//	if (bind & D3D11_BIND_SHADER_RESOURCE)
	//	{
	//		auto result = device->CreateShaderResourceView(mTexture.Get(), &mShaderResourceDesc, mShaderResource.GetAddressOf());
	//		assert(result == S_OK);

	//		if (result != S_OK)
	//			return false;
	//	}
	//	if (bind & D3D11_BIND_DEPTH_STENCIL)
	//	{
	//		auto result = device->CreateDepthStencilView(mTexture.Get(), &mDepthStencilDesc, mDepthStencil.GetAddressOf());
	//		assert(result == S_OK);

	//		if (result != S_OK)
	//			return false;
	//	}

	//	if (bind & D3D11_BIND_UNORDERED_ACCESS)
	//	{
	//		auto result = device->CreateUnorderedAccessView(mTexture.Get(), &mUnordredAccessDesc, mUnorderedAccess.GetAddressOf());
	//		assert(result == S_OK);

	//		if (result != S_OK)
	//			return false;
	//	}

	//	return true;
	//}

	//void SwapChainTexture2D::Release()
	//{
	//	if (mTexture != nullptr)
	//		mTexture->Release();

	//	if (mDepthStencil != nullptr)
	//		mDepthStencil->Release();

	//	if (mRenderTarget != nullptr)
	//		mRenderTarget->Release();

	//	if (mShaderResource != nullptr)
	//		mShaderResource->Release();

	//	if (mUnorderedAccess != nullptr)
	//		mUnorderedAccess->Release();
	//}

	//void SwapChainTexture2D::ClearTexture(DirectX::XMVECTORF32 clearColor)
	//{
	//	if (mRenderTarget == nullptr)
	//		return;

	//	ID3D11DeviceContext* context = HW::GetContext();

	//	context->ClearRenderTargetView(mRenderTarget.Get(), clearColor);

	//}

	//SwapChainTexture2D::SwapChainTexture2D(D3D11_TEXTURE2D_DESC& texDesc) : mTextureDesc(texDesc), mDepthStencilDesc(), mUnordredAccessDesc(), mRenderTargetDesc(), mShaderResourceDesc()
	//{
	//	mRenderTargetDesc.Format = texDesc.Format;
	//	mRenderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	//	mDepthStencilDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	//	mDepthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	//	mUnordredAccessDesc.Format = texDesc.Format;
	//	mUnordredAccessDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

	//	mShaderResourceDesc.Format = texDesc.Format;
	//	mShaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	//	bool bResult = Generate();
	//	assert(bResult == true);
	//	
	//}

	//SwapChainTexture2D::~SwapChainTexture2D()
	//{}
}