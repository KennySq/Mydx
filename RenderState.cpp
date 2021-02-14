#include"pch.h"
#include"RenderState.h"

namespace Mydx
{
	void RenderState::ChangeDrawMode(D3D11_FILL_MODE fillMode)
	{
		ID3D11Device* device = HW::GetDevice();
		D3D11_RASTERIZER_DESC desc{};

		mRaster->GetDesc(&desc);
		desc.FillMode = fillMode;

		mRaster->Release();

		device->CreateRasterizerState(&desc, mRaster.GetAddressOf());
	}
	void RenderState::ChangeCullMode(D3D11_CULL_MODE cullMode)
	{
		ID3D11Device* device = HW::GetDevice();
		D3D11_RASTERIZER_DESC desc{};

		mRaster->GetDesc(&desc);
		desc.CullMode = cullMode;

		mRaster->Release();

		device->CreateRasterizerState(&desc, mRaster.GetAddressOf());
	}
	bool RenderState::Bind()
	{
		static ID3D11DeviceContext* context = HW::GetContext();

		ID3D11Buffer* vBuffer[MAX_VERTEX_CONSTANT_REGISTER];
		ID3D11Buffer* pBuffer[MAX_PIXEL_CONSTANT_REGISTER];
		ID3D11ShaderResourceView* vTexture[MAX_VERTEX_TEXTURE_REGISTER];
		ID3D11ShaderResourceView* pTexture[MAX_PIXEL_TEXTURE_REGISTER];

		for (size_t i = 0; i < mVertexConstRegister.size(); i++)
		{
			vBuffer[i] = mVertexConstRegister[i].AsBuffer();
		}

		for (size_t i = 0; i < mVertexTextureRegister.size(); i++)
		{
			vTexture[i] = mVertexTextureRegister[i].AsResource();
		}

		for (size_t i = 0; i < mPixelConstRegister.size(); i++)
		{
			pBuffer[i] = mPixelConstRegister[i].AsBuffer();
		}

		for (size_t i = 0; i < mPixelTextureRegister.size(); i++)
		{
			pTexture[i] = mPixelTextureRegister[i].AsResource();
		}

		context->VSSetShaderResources(0, mVertexTextureRegister.size(), vTexture);
		context->VSSetConstantBuffers(0, mVertexConstRegister.size(), vBuffer);
		context->PSSetShaderResources(0, mPixelTextureRegister.size(), pTexture);
		context->PSSetConstantBuffers(0, mPixelConstRegister.size(), pBuffer);

		return true;
	}
	void RenderState::AddResource(ID3D11Buffer* buffer, ePassType passType, unsigned int index)
	{
		switch (passType)
		{
			case VERTEX:
				if (index >= MAX_VERTEX_CONSTANT_REGISTER)
				{
					return;
				}
				mVertexConstRegister.push_back(buffer);
				break;
			case PIXEL:

				if (index >= MAX_PIXEL_CONSTANT_REGISTER)
				{
					return;
				}
				mPixelConstRegister.push_back(buffer);
				break;
			default:
				return;
				break;
		}
	}
	void RenderState::AddResource(ID3D11ShaderResourceView* resource, ePassType passType, unsigned int index)
	{
		switch (passType)
		{
			case VERTEX:
				if (index >= MAX_VERTEX_TEXTURE_REGISTER)
				{
					return;
				}

				mVertexTextureRegister.push_back(resource);

				break;

			case PIXEL:
				if (index >= MAX_PIXEL_TEXTURE_REGISTER)
				{
					return;
				}

				mPixelTextureRegister.push_back(resource);

				break;
			default:
				return;
				break;
		}
	}

	RenderState::RenderState() 
		: mContext(HW::GetContext()),
		mVertexConstRegister(MAX_VERTEX_CONSTANT_REGISTER),
		mVertexTextureRegister(MAX_VERTEX_TEXTURE_REGISTER),
		mPixelConstRegister(MAX_PIXEL_CONSTANT_REGISTER),
		mPixelTextureRegister(MAX_PIXEL_TEXTURE_REGISTER)
	{
		ID3D11Device* device = HW::GetDevice();
		D3D11_RASTERIZER_DESC rasterDesc;

		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		device->CreateRasterizerState(&rasterDesc, mRaster.GetAddressOf());
	}

	RenderState::~RenderState()
	{

	}

}