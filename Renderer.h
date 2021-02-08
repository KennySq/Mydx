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
		void AddSwapChainTexture2D(SwapChainTexture2D* const texture);
		Texture2D* GetTexture2D(unsigned int index) const;
		SwapChainTexture2D* GetSwapChainTexture2D(unsigned int index) const;
	private:
		vector<Texture2D*> mTextures;
		vector<SwapChainTexture2D*> mSwapChainTextures;
		vector<Viewport*> mViewports;

		Renderer2D(const Renderer2D& rhs) = delete;
		Renderer2D(IDXGISwapChain* swapChain);
		~Renderer2D() {}

		unsigned int mWidth;
		unsigned int mHeight;

		const IDXGISwapChain* mSwapChain;
	};

	class Renderer3D
	{
	public:
		static Renderer3D& GetInstance()
		{
			static Renderer3D inst(HW::GetDevice(), HW::GetContext());
			return inst;
		}

		void DrawMesh(Mesh& mesh, Pass& pass);
		
	private:
		void bindPass(Pass& pass);
		void bindVSResources(ID3D11ShaderResourceView*const * shaderResources, unsigned int resourceCount);
		void bindPSResources(ID3D11ShaderResourceView* const* shaderResources, unsigned int resourceCount);
		
		void bindVSConstBuffer(ID3D11Buffer* const* constBuffers, unsigned int bufferCount);
		void bindPSConstBuffer(ID3D11Buffer* const* constBuffers, unsigned int bufferCount);

		Renderer3D(const Renderer3D& rhs) = delete;
		Renderer3D(ID3D11Device* const device, ID3D11DeviceContext* const context);
		~Renderer3D() {}

		Scene* mRenderScene = nullptr;

		ID3D11Device* const mDevice;
		ID3D11DeviceContext* const mContext;
	};
}

