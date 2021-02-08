#pragma once
#include"Texture2D.h"

namespace Mydx
{
	class Viewport
	{
	public:
		Viewport(unsigned int width, unsigned int height, float x, float y);
		Viewport(Texture2D* image, unsigned int width, unsigned int height, float x, float y);
		Viewport(const Viewport& rhs) = delete;
		~Viewport();

		void SetTexture2D(Texture2D* image) { mImage = image; }
		const D3D11_VIEWPORT* GetViewport() { return &mViewport; }
	private:
		Texture2D* mImage;
		D3D11_VIEWPORT mViewport;
	};

}