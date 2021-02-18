#pragma once
#include"IMemory.h"

using namespace DirectX;

namespace Mydx
{
	struct DirectionalLightData
	{
		XMFLOAT4 mDirection;
		XMFLOAT3 mColor;
		float mIntensity;

		DirectionalLightData() : mDirection(0,0,0,0), mColor(0,0,0), mIntensity(0) {}

		DirectionalLightData(XMFLOAT4 direction, XMFLOAT3 color, float intensity)
			: mDirection(direction), mColor(color), mIntensity(intensity) { }

		DirectionalLightData(XMFLOAT4 direction, XMVECTORF32 color, float intensity)
			: mDirection(direction), mColor(color), mIntensity(intensity) { }
	};

	class DirectionalLight : IMemory
	{
	public:
		DirectionalLight();
		DirectionalLight(XMFLOAT4 direction, XMVECTORF32 color, float intensity);
		DirectionalLight(const DirectionalLight& rhs);
		~DirectionalLight();

		ID3D11Buffer* AsBuffer() const { return mBuffer.Get(); }

	private:
		ComPtr<ID3D11Buffer> mBuffer;
		DirectionalLightData mRaw;

		// IMemory을(를) 통해 상속됨
		virtual bool Update() override;
		virtual bool Generate() override;

		virtual void Release() override;

	};
}