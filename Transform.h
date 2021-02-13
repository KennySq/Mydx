#pragma once
#include"IMemory.h"

using namespace DirectX;

namespace Mydx
{
	class Transform : IMemory
	{
	public:

		void Translate(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void SetScale(float x, float y, float z);

		ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }

		Transform();
		Transform(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale);
		Transform(const Transform& rhs);
		Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
		~Transform();

	private:
		XMFLOAT4X4 mTransform;
		XMFLOAT4 mPosition;
		XMFLOAT4 mRotation;
		XMFLOAT4 mScale;

		ComPtr<ID3D11Buffer> mBuffer;

		// IMemory을(를) 통해 상속됨
		virtual bool Generate() override;

		virtual void Release() override;

	};
}


