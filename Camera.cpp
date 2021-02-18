#include"pch.h"
#include"Camera.h"
#include"Viewport.h"

namespace Mydx
{
	Camera::Camera(XMVECTOR position, float fov, float aspectRatio, Viewport* viewport) : mViewport(viewport)
	{
		float newFov = XMConvertToRadians(fov);

		XMMATRIX view = XMMatrixLookAtLH(position,
										 position - XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f),
										 XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

		XMMATRIX projection = XMMatrixPerspectiveFovLH(newFov, aspectRatio, 0.01f, 1000.0f);

		XMStoreFloat4x4(&mRaw.mView, XMMatrixTranspose(view));
		XMStoreFloat4x4(&mRaw.mProjection, XMMatrixTranspose(projection));
		XMStoreFloat4(&mRaw.mForward, position - XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f));

		Generate();
	}

	Camera::Camera(float px, float py, float pz, float fov, float aspectRatio, Viewport* viewport) : mViewport(viewport)
	{
		float newFov = XMConvertToRadians(fov);

		XMMATRIX view = XMMatrixLookAtLH(XMVectorSet(px, py, pz, 1.0f),
										 XMVectorSet(px - 1.0f, py, pz, 1.0f),
										 XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

		XMMATRIX projection = XMMatrixPerspectiveFovLH(newFov, aspectRatio, 0.01f, 1000.0f);

		XMStoreFloat4x4(&mRaw.mView, XMMatrixTranspose(view));
		XMStoreFloat4x4(&mRaw.mProjection, XMMatrixTranspose(projection));
		XMStoreFloat4(&mRaw.mForward, XMVectorSet(px - 1.0f, py, pz, 1.0f));


		Generate();

	}

	Camera::~Camera()
	{}

	bool Camera::Update()
	{
		static const XMVECTOR up = XMVectorSet(0, 1, 0, 1);
		static const XMVECTOR right = XMVectorSet(0, 0, 1, 1);
		static const XMVECTOR forward = XMVectorSet(1, 0, 0, 1);

		XMVECTOR deter;
		XMMATRIX view = XMLoadFloat4x4(&mRaw.mView);

		//XMMatrixDeterminant(view);
		XMMATRIX inverse = XMMatrixInverse(&deter, view);

		float x = inverse.r[3].m128_f32[0];
		float y = inverse.r[3].m128_f32[1];
		float z = inverse.r[3].m128_f32[2];

		mRaw.mPosition.x = x;
		mRaw.mPosition.y = y;
		mRaw.mPosition.z = z;

		XMVECTOR worldUp = XMVector4Transform(up, inverse);
		XMVECTOR worldForward = XMVector4Transform(forward, inverse);
		XMVECTOR worldRight = XMVector4Transform(right, inverse);

		XMStoreFloat4(&mRaw.mForward, worldForward);
		XMStoreFloat4(&mRaw.mUp, worldUp);
		XMStoreFloat4(&mRaw.mRight, worldRight);

		return true;
	}

	bool Camera::Generate()
	{
		HRESULT result;
		ID3D11Device* device = HW::GetDevice();
		D3D11_BUFFER_DESC bufferDesc{};
		D3D11_SUBRESOURCE_DATA subData{};

		bufferDesc.ByteWidth = sizeof(CameraBuffer);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;

		subData.pSysMem = &mRaw;

		result = device->CreateBuffer(&bufferDesc, &subData, mBuffer.GetAddressOf());
		if (result != S_OK)
		{
			return false;
		}

		return true;
	}

	void Camera::Release()
	{}

}