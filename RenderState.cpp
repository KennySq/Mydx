#include"pch.h"
#include"RenderState.h"

namespace Mydx
{
	bool RenderState::Bind()
	{
		static ID3D11DeviceContext* context = HW::GetContext();

		if (mVertexTextureRegisterCount != 0)
		{
			context->VSSetShaderResources(0, mVertexTextureRegisterCount, mVertexTextureRegister);
		}

		if (mVertexConstRegisterCount != 0);
		{
			context->VSSetConstantBuffers(0, mVertexConstRegisterCount, mVertexConstRegister);
		}

		if (mPixelTextureRegisterCount != 0)
		{
			context->PSSetShaderResources(0, mPixelTextureRegisterCount, mPixelTextureRegister);
		}

		if (mPixelConstRegisterCount != 0)
		{
			context->PSSetConstantBuffers(0, mPixelConstRegisterCount, mPixelConstRegister);
		}

		return true;
	}
	void RenderState::Add(ID3D11Buffer* buffer, ePassType passType)
	{
		switch (passType)
		{
			case VERTEX:
				if (mVertexConstRegisterCount >= MAX_VERTEX_CONSTANT_REGISTER)
				{
					return;
				}
				mVertexConstRegister[mVertexConstRegisterCount++] = buffer;
				break;
			case PIXEL:

				if (mPixelConstRegisterCount >= MAX_PIXEL_CONSTANT_REGISTER)
				{
					return;
				}
				mPixelConstRegister[mPixelConstRegisterCount++] = buffer;
				break;
			default:
				return;
				break;
		}
	}
	void RenderState::Add(ID3D11ShaderResourceView* resource, ePassType passType)
	{
		switch (passType)
		{
			case VERTEX:
				if (mVertexTextureRegisterCount >= MAX_VERTEX_TEXTURE_REGISTER)
				{
					return;
				}

				mVertexTextureRegister[mVertexTextureRegisterCount++] = resource;

				break;

			case PIXEL:
				if (mPixelTextureRegisterCount >= MAX_PIXEL_TEXTURE_REGISTER)
				{
					return;
				}

				mPixelTextureRegister[mPixelTextureRegisterCount++] = resource;

				break;
			default:
				return;
				break;
		}
	}
}