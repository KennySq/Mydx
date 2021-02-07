#pragma once
#include"IMemory.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace Mydx;

namespace Mydx
{
	struct Camera : IMemory
	{


		static Camera& GetMainCamera()
		{
			static Camera camera(5.0f, 0.0f, 0.0f, XMConvertToDegrees(60.0f), 800.0f / 600.0f);
			return camera;
		}

		Camera(XMVECTOR position, float fov, float aspectRatio);
		Camera(float px, float py, float pz, float fov, float aspectRatio);
		~Camera();

	private:
		struct CameraBuffer
		{
			XMFLOAT4X4 mView;
			XMFLOAT4X4 mProjection;
		};

		ComPtr<ID3D11Buffer> mBuffer;

		CameraBuffer mRaw;

		float mFieldOfView;
		float mAspectRatio;

		// IMemory을(를) 통해 상속됨
		virtual bool Generate() override;
		virtual void Release() override;

	};
}