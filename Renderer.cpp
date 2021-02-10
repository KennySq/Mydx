#include "pch.h"
#include "Renderer.h"
#include"Texture2D.h"


using namespace Mydx;

void Mydx::Renderer2D::AddTexture2D(Texture2D* const texture)
{
	if (texture == nullptr)
	{
		return;
	}

	mTextures.push_back(texture);
}

Texture2D* Mydx::Renderer2D::GetTexture2D(unsigned int index) const
{
	if (index < 0 || index >= mTextures.size())
	{
		return nullptr;
	}
	return mTextures[index];
}

void Mydx::Renderer2D::AddViewport(Viewport* viewport)
{
	if (viewport == nullptr)
	{
		return;
	}

	mViewports.emplace_back(viewport);
}

Mydx::Renderer2D::Renderer2D(IDXGISwapChain* swapChain)
	: mSwapChain(swapChain)
{
	mCurrentViewport = new Viewport(mWidth, mHeight, 0, 0);
	AddViewport(mCurrentViewport);

}