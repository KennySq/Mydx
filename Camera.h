#pragma once
#include"IMemory.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace Mydx;

namespace Mydx
{
	class Viewport;
	struct Camera : IMemory
	{

		Viewport* GetViewport() const { return mViewport; }
		ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }

		Camera(XMVECTOR position, float fov, float aspectRatio, Viewport* viewport);
		Camera(float px, float py, float pz, float fov, float aspectRatio, Viewport* viewport);
		~Camera();

		virtual bool Update() override;

	private:
		struct CameraBuffer
		{
			XMFLOAT4X4 mView;
			XMFLOAT4X4 mProjection;
			XMFLOAT4 mForward;
			XMFLOAT4 mUp;
			XMFLOAT4 mRight;

			XMFLOAT4 mPosition;
		};

		Viewport* mViewport;

		ComPtr<ID3D11Buffer> mBuffer;

		CameraBuffer mRaw;

		float mFieldOfView;
		float mAspectRatio;

		// IMemory을(를) 통해 상속됨
		virtual bool Generate() override;
		virtual void Release() override;

	};
}