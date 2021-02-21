#include "pch.h"
#include "Transform.h"

namespace Mydx
{
	void Transform::Translate(float x, float y, float z)
	{
		XMMATRIX mat = XMLoadFloat4x4(&mTransform);
		XMMATRIX translate = XMMatrixIdentity();

		translate.r[3].m128_f32[0] = x;
		translate.r[3].m128_f32[1] = y;
		translate.r[3].m128_f32[2] = z;

		mat *= translate;

		XMStoreFloat4x4(&mTransform, XMMatrixTranspose(mat));
		Update();

		return;
	}
	void Transform::Rotate(float x, float y, float z)
	{}
	void Transform::SetScale(float x, float y, float z)
	{
		mTransform._11 = x;
		mTransform._22 = y;
		mTransform._33 = z;

		Update();
	}

	Transform::Transform()
	{
		XMStoreFloat4x4(&mTransform, XMMatrixIdentity());
		Generate();
	}

	Mydx::Transform::Transform(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale)
	{
		XMMATRIX transform = XMMatrixTransformation(scale, XMVectorZero(), XMVectorZero(), rotation, XMVectorZero(), position);

		XMStoreFloat4x4(&mTransform, transform);

		XMStoreFloat4(&mPosition, position);
		XMStoreFloat4(&mRotation, rotation);
		XMStoreFloat4(&mScale, scale);

		Generate();
	}

	Mydx::Transform::Transform(const Transform& rhs) : mPosition(rhs.mPosition), mRotation(rhs.mRotation), mScale(rhs.mScale), mTransform(rhs.mTransform)
	{
		if (mBuffer != nullptr)
		{
			mBuffer->Release();
		}

		Generate();
	}

	Mydx::Transform::Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
		: mPosition(px,py,pz,1.0f), mRotation(rx,ry,rz,0.0f), mScale(sx,sy,sz,1.0f)
	{
		XMVECTOR position = XMLoadFloat4(&mPosition);
		XMVECTOR rotation = XMLoadFloat4(&mRotation);
		XMVECTOR scale = XMLoadFloat4(&mScale);

		XMMATRIX transform = XMMatrixTransformation(scale, XMVectorZero(), XMVectorZero(), rotation, XMVectorZero(), position);
	}

	Mydx::Transform::~Transform()
	{}

	bool Transform::Generate()
	{
		HRESULT hresult;
		ID3D11Device* device = HW::GetDevice();
		D3D11_BUFFER_DESC bufferDesc{};
		D3D11_SUBRESOURCE_DATA subData{};

		bufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		subData.pSysMem = &mTransform;

		hresult = device->CreateBuffer(&bufferDesc, &subData, mBuffer.GetAddressOf());
		assert(hresult == S_OK);
		if (hresult != S_OK)
		{
			return false;
		}

		return true;
	}

	bool Transform::Update()
	{
		static ID3D11DeviceContext* context = HW::GetContext();

		context->UpdateSubresource(mBuffer.Get(), 0, nullptr, &mTransform, 0, 0);

		return true;
	}

	Transform Transform::operator=(const XMMATRIX& rhs)
	{
		XMStoreFloat4x4(&mTransform, rhs);

		return *this;
	}

	void Transform::Release()
	{}

}