#pragma once
#include"Texture2D.h"

namespace Mydx
{

	class Viewport
	{
	public:
		Viewport(unsigned int width, unsigned int height, float x, float y);
		Viewport(const Texture2D& image, unsigned int width, unsigned int height, float x, float y);
		Viewport(const Viewport& rhs) = delete;
		~Viewport();



	private:
		ComPtr<ID3D11RenderTargetView> mImage;
		D3D11_VIEWPORT mViewport;
	};

}