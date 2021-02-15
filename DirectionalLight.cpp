#include"pch.h"
#include"DirectionalLight.h"

namespace Mydx
{
	DirectionalLight::DirectionalLight()
	{
		XMVECTOR direction = XMVectorSet(0, 0, 0, 1) - XMVectorSet(5, 5, 0, 1);
		XMVECTOR color = Colors::White;
		float intensity = 1;

		XMStoreFloat4(&mRaw.mDirection, direction);
		XMStoreFloat3(&mRaw.mColor, color);
		mRaw.mIntensity = intensity;

		Generate();
	}

	DirectionalLight::DirectionalLight(XMFLOAT4 direction, XMVECTORF32 color, float intensity)
		: mRaw(direction, color, intensity)
	{
		Generate();
	}

	DirectionalLight::DirectionalLight(const DirectionalLight& rhs)
	{
		mRaw = rhs.mRaw;
		
		Generate();
	}

	DirectionalLight::~DirectionalLight()
	{}

	bool DirectionalLight::Update()
	{
		static ID3D11DeviceContext* context = HW::GetContext();

		context->UpdateSubresource(mBuffer.Get(), 0, nullptr, &mRaw, 0, 0);

		return true;
	}

	bool DirectionalLight::Generate()
	{
		HRESULT result;
		ID3D11Device* device = HW::GetDevice();

		D3D11_BUFFER_DESC desc{};
		D3D11_SUBRESOURCE_DATA subData{};

		desc.ByteWidth = sizeof(DirectionalLightData);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		subData.pSysMem = &mRaw;

		result = device->CreateBuffer(&desc, &subData, mBuffer.GetAddressOf());
		if (result != S_OK)
		{
			return false;
		}
		
		return true;
	}

	void DirectionalLight::Release()
	{
		if (mBuffer != nullptr)
		{
			mBuffer->Release();
		}
	}
}