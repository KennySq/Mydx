#include "pch.h"
#include "Renderer.h"
#include"Texture2D.h"


using namespace Mydx;

void Mydx::Renderer3D::DrawMesh(Mesh& mesh, Pass& pass)
{
	bindPass(pass);
}

void Mydx::Renderer3D::bindPass(Pass& pass)
{
	auto vs = pass.GetVS();
	auto gs = pass.GetGS();
	auto ds = pass.GetDS();
	auto hs = pass.GetHS();
	auto ps = pass.GetPS();

	if (vs != nullptr)
	{
		mContext->VSSetShader(vs, nullptr, 0);
	}

	if (gs != nullptr)
	{
		mContext->GSSetShader(gs, nullptr, 0);
	}

	if (ds != nullptr)
	{
		mContext->DSSetShader(ds, nullptr, 0);
	}

	if (hs != nullptr)
	{
		mContext->HSSetShader(hs, nullptr, 0);
	}

	if (ps != nullptr)
	{
		mContext->PSSetShader(ps, nullptr, 0);
	}
}

void Mydx::Renderer3D::bindVSResources(ID3D11ShaderResourceView*const * shaderResources, unsigned int resourceCount)
{
	mContext->VSSetShaderResources(0, resourceCount, shaderResources);
}

void Mydx::Renderer3D::bindPSResources(ID3D11ShaderResourceView* const* shaderResources, unsigned int resourceCount)
{
	mContext->PSSetShaderResources(0, resourceCount, shaderResources);
}

void Mydx::Renderer3D::bindVSConstBuffer(ID3D11Buffer* const* constBuffers, unsigned int bufferCount)
{
	mContext->VSSetConstantBuffers(0, bufferCount, constBuffers);
}

void Mydx::Renderer3D::bindPSConstBuffer(ID3D11Buffer* const* constBuffers, unsigned int bufferCount)
{
	mContext->PSSetConstantBuffers(0, bufferCount, constBuffers);
}



Mydx::Renderer3D::Renderer3D(ID3D11Device* device, ID3D11DeviceContext* context)
	: mDevice(device), mContext(context)
{
	
}

void Mydx::Renderer2D::AddTexture2D(Texture2D* const texture)
{
	if (texture == nullptr)
	{
		return;
	}

	mTextures.push_back(texture);
}

void Mydx::Renderer2D::AddSwapChainTexture2D(SwapChainTexture2D* const texture)
{
	if (texture == nullptr)
	{
		return;
	}

	mSwapChainTextures.push_back(texture);
}

Texture2D* Mydx::Renderer2D::GetTexture2D(unsigned int index) const
{
	if (index < 0 || index >= mTextures.size())
	{
		return nullptr;
	}
	return mTextures[index];
}

SwapChainTexture2D* Mydx::Renderer2D::GetSwapChainTexture2D(unsigned int index) const
{
	if (index < 0 || index >= mSwapChainTextures.size())
	{
		return nullptr;
	}
	return mSwapChainTextures[index];
}

Mydx::Renderer2D::Renderer2D(IDXGISwapChain* swapChain)
	: mSwapChain(swapChain)
{}