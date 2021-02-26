#pragma once

#include"ePassType.h"
#include"RegisterVector.h"
#include"RegisterMap.h"
#include"Utility.h"

namespace Mydx
{


	class RenderState
	{
	public:
		void ChangeDrawMode(D3D11_FILL_MODE fillMode);
		void ChangeCullMode(D3D11_CULL_MODE cullMode);

		ID3D11RasterizerState* GetState() const { return mRaster.Get(); }

		RenderState();
		~RenderState();

	private:
		ComPtr<ID3D11RasterizerState> mRaster;

		ID3D11DeviceContext* mContext;

	};
}