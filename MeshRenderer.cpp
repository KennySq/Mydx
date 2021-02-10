#include "pch.h"
#include "MeshRenderer.h"
#include"Renderer.h"
#include"Shader.h"
#include"Texture2D.h"

namespace Mydx
{
	MeshRenderer::MeshRenderer() : Component("Mesh Renderer"), mContext(HW::GetContext())
	{

	}

	MeshRenderer::~MeshRenderer()
	{}

	void MeshRenderer::Init()
	{
		
	}

	void MeshRenderer::Update(float delta)
	{}

	void MeshRenderer::Render(float delta)
	{}

	void MeshRenderer::Release()
	{}

	void Mydx::MeshRenderer::SetMesh(Mesh* mesh)
	{
		if (mesh == nullptr)
		{
			mMesh = nullptr;
			return;
		}

		mMesh = mesh;

	}
	void MeshRenderer::SetPass(Pass* pass)
	{
		if (pass == nullptr)
		{
			pass = nullptr;
			return;
		}

		mPass = pass;
	
	}
	void MeshRenderer::DrawForward(Texture2D* target, Texture2D* depth, Viewport* viewport)
	{
		
		if (mMesh == nullptr || viewport == nullptr)
		{
			return;
		}

		ID3D11RenderTargetView* targetView = target->GetRenderTarget();
		ID3D11DepthStencilView* targetDepth = depth->GetDepthStencil();
		mContext->OMSetRenderTargets(1, &targetView, targetDepth);
		
		bindPass();
		bindResources();

		ID3D11Buffer* vertexBuffer = mMesh->GetVertexBuffer();
		ID3D11Buffer* indexBuffer = mMesh->GetIndexBuffer();

		unsigned int strides[1] = { mMesh->GetStride(), };
		unsigned int offsets[1] = { mMesh->GetOffset(), };

		mContext->RSSetViewports(1, viewport->GetViewport());
		mContext->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
		mContext->IASetIndexBuffer(mMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
		
		mContext->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}
	void MeshRenderer::bindPass()
	{
		auto vs = mPass->GetVS();
		auto gs = mPass->GetGS();
		auto ds = mPass->GetDS();
		auto hs = mPass->GetHS();
		auto ps = mPass->GetPS();
		auto il = mPass->GetIL();

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

		if (il != nullptr)
		{
			mContext->IASetInputLayout(il);
		}
	}
	void MeshRenderer::bindResources()
	{
		ID3D11ShaderResourceView* const* vertexResources = mPass->GetVertexResources();
		ID3D11Buffer* const* vertexConstBuffers = mPass->GetVertexConstBuffers();
		ID3D11ShaderResourceView* const* pixelResources = mPass->GetPixelResources();
		ID3D11Buffer* const* pixelConstBuffers = mPass->GetPixelConstBuffers();

		bindVertexShaderResources(vertexResources, mPass->GetVertexResourceCount());
		bindVertexConstBuffer(vertexConstBuffers, mPass->GetVertexConstBufferCount());

		bindPixelShaderResources(pixelResources, mPass->GetPixelResourceCount());
		bindPixelConstBuffer(pixelConstBuffers, mPass->GetPixelConstBufferCount());
	}
	void MeshRenderer::bindVertexShaderResources(ID3D11ShaderResourceView* const* shaderResources, unsigned int resourceCount)
	{
		mContext->VSSetShaderResources(0, resourceCount, shaderResources);
	}
	void MeshRenderer::bindPixelShaderResources(ID3D11ShaderResourceView* const* shaderResources, unsigned int resourceCount)
	{
		mContext->VSSetShaderResources(0, resourceCount, shaderResources);
	}

	void MeshRenderer::bindVertexConstBuffer(ID3D11Buffer* const* buffers, unsigned int bufferCount)
	{
		mContext->VSSetConstantBuffers(0, bufferCount, buffers);
	}

	void MeshRenderer::bindPixelConstBuffer(ID3D11Buffer* const* buffers, unsigned int bufferCount)
	{
		mContext->PSSetConstantBuffers(0, bufferCount, buffers);
	}	
}