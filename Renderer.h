#pragma once

#include"Mesh.h"
#include"Shader.h"
#include"Viewport.h"


using namespace DirectX;
namespace Mydx
{
	class Scene;
	class Renderer2D
	{
	public:
		static Renderer2D& GetInstance()
		{
			static Renderer2D inst(HW::GetSwapChain());
			
			return inst;
		}

		void AddTexture2D(Texture2D* const texture);
		Texture2D* GetTexture2D(unsigned int index) const;
	
		void AddViewport(Viewport* viewport);
		Viewport* GetCurrentViewport() const { return mCurrentViewport; }
	
	private:
		vector<Texture2D*> mTextures;
		vector<Viewport*> mViewports;
		Viewport* mCurrentViewport;

		Renderer2D(const Renderer2D& rhs) = delete;
		Renderer2D(IDXGISwapChain* swapChain);
		~Renderer2D() {}

		unsigned int mWidth;
		unsigned int mHeight;

		const IDXGISwapChain* mSwapChain;
	};
}

