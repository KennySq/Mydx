#include "pch.h"
#include "Viewport.h"

namespace Mydx
{
	Viewport::Viewport(unsigned int width, unsigned int height, float x, float y) : mImage(nullptr)
	{
		mViewport.TopLeftX = x;
		mViewport.TopLeftY = y;

		mViewport.MaxDepth = 1.0f;
		mViewport.MinDepth = 0.0f;

		mViewport.Width = static_cast<float>(width);
		mViewport.Height = static_cast<float>(height);

	}
	Viewport::Viewport(Texture2D* image, unsigned int width, unsigned int height, float x, float y) :
		mImage(image)
	{
		mViewport.TopLeftX = x;
		mViewport.TopLeftY = y;

		mViewport.MaxDepth = 1.0f;
		mViewport.MinDepth = 0.0f;

		mViewport.Width = static_cast<float>(width);
		mViewport.Height = static_cast<float>(height);
	}

	Viewport::Viewport(Texture2D* image, Texture2D* depth, unsigned int width, unsigned int height, float x, float y)
		: mImage(image), mDepth(depth)
	{
		mViewport.TopLeftX = x;
		mViewport.TopLeftY = y;

		mViewport.MaxDepth = 1.0f;
		mViewport.MinDepth = 0.0f;

		mViewport.Width = static_cast<float>(width);
		mViewport.Height = static_cast<float>(height);

	}

	Viewport::~Viewport()
	{}
}