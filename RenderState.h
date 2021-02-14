#pragma once

#include"ePassType.h"
#include"RegisterVector.h"

namespace Mydx
{
	constexpr unsigned int MAX_VERTEX_CONSTANT_REGISTER = 15;
	constexpr unsigned int MAX_VERTEX_TEXTURE_REGISTER = 128;
	constexpr unsigned int MAX_PIXEL_CONSTANT_REGISTER = 15;
	constexpr unsigned int MAX_PIXEL_TEXTURE_REGISTER = 8;

	class RenderState
	{
	public:
		void ChangeDrawMode(D3D11_FILL_MODE fillMode);
		void ChangeCullMode(D3D11_CULL_MODE cullMode);

		bool Bind();

		void AddResource(ID3D11Buffer* buffer, ePassType passType, unsigned int index);
		void AddResource(ID3D11ShaderResourceView* resource, ePassType passType, unsigned int index);

		ID3D11RasterizerState* GetState() const { return mRaster.Get(); }

		RenderState();
		~RenderState();

	private:
		ComPtr<ID3D11RasterizerState> mRaster;

		RegisterVector mVertexConstRegister;
		RegisterVector mVertexTextureRegister;

		RegisterVector mPixelConstRegister;
		RegisterVector mPixelTextureRegister;

		ID3D11DeviceContext* mContext;

	};
}