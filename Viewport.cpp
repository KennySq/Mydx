#include "pch.h"
#include "Viewport.h"

Viewport::Viewport(const Texture2D& image, unsigned int width, unsigned int height, float x, float y)
{
	mViewport.TopLeftX = x - (width / 2);
	mViewport.TopLeftY = y - (height / 2);

	mViewport.MaxDepth = 1.0f;
	mViewport.MinDepth = 0.0f;

	mViewport.Width = static_cast<float>(width);
	mViewport.Height = static_cast<float>(height);
}

Viewport::~Viewport()
{
}
