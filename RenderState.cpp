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

	RenderState::RenderState() 
		: mContext(HW::GetContext())
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