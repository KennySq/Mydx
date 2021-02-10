#pragma once
#include"Texture2D.h"

namespace Mydx
{
	class Viewport
	{
	public:
		Viewport(unsigned int width, unsigned int height, float x, float y);
		Viewport(Texture2D* image, unsigned int width, unsigned int height, float x, float y);
		Viewport(Texture2D* image, Texture2D* depth, unsigned int width, unsigned int height, float x, float y);
		Viewport(const Viewport& rhs) = delete;
		~Viewport();

		void SetTexture2D(Texture2D* image) { mImage = image; }
		const D3D11_VIEWPORT* GetViewport() const { return &mViewport; }
	
		Texture2D* GetImage() const { return mImage; }
		Texture2D* GetDepth() const { return mDepth; }
	private:
		Texture2D* mImage;
		Texture2D* mDepth;
		D3D11_VIEWPORT mViewport;
	};

}