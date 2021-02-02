#pragma once

using namespace Microsoft::WRL;
using namespace std;

namespace Mydx
{
	typedef class Hardware
	{
	public:
		inline static Hardware* const GetInstance() { if (mInstance == nullptr) mInstance = new Hardware(); return mInstance; }
		inline static ID3D11Device* const GetDevice()
		{
			if (mInstance->mDevice == nullptr)
				mInstance->generateDeviceAndSwapChain();

			return mInstance->mDevice.Get();

		}
		Hardware();
		~Hardware();

	private:

		bool generateDeviceAndSwapChain();

		static Hardware* mInstance;

		ComPtr<ID3D11Device> mDevice;
		ComPtr<ID3D11DeviceContext> mContext;
		ComPtr<IDXGISwapChain> mSwapChain;

		HWND mWindow;
		HINSTANCE mHandle;

		unsigned int mWidth;
		unsigned int mHeight;
	} HW;

}