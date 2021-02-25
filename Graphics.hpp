#include "pch.h"
#include "Graphics.h"
namespace Mydx
{
	template<typename T>
	bool Graphics::CommitResource(ID3D11Buffer* buffer, T raw)
	{
		if (buffer == nullptr)
		{
			return false;
		}

		mContext->UpdateSubresource(buffer, 0, nullptr, raw, 0, 0);

		return true;
	}

	Graphics::Graphics(ID3D11Device* device, ID3D11DeviceContext* context)
		: mDevice(device), mContext(context)
	{

	}

	Graphics::~Graphics()
	{}
}