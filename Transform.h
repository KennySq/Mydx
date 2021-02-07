#pragma once

using namespace DirectX;

namespace Mydx
{
	class Transform
	{
	public:

		void Translate(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void SetScale(float x, float y, float z);

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


	};
}


