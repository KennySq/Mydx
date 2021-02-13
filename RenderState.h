#pragma once

#include"ePassType.h"

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

		bool Bind();

		void Add(ID3D11Buffer* buffer, ePassType passType);
		void Add(ID3D11ShaderResourceView* resource, ePassType passType);

	private:
		ComPtr<ID3D11RasterizerState> mRaster;

		ID3D11Buffer* mVertexConstRegister[15];
		ID3D11ShaderResourceView* mVertexTextureRegister[128];

		ID3D11Buffer* mPixelConstRegister[15];
		ID3D11ShaderResourceView* mPixelTextureRegister[8];

		unsigned int mVertexConstRegisterCount = 0;
		unsigned int mVertexTextureRegisterCount = 0;
		unsigned int mPixelConstRegisterCount = 0;
		unsigned int mPixelTextureRegisterCount = 0;



	};
}