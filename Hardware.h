#pragma once

using namespace Microsoft::WRL;
using namespace std;

namespace Mydx
{
	typedef class Hardware
	{
	public:
		inline static Hardware* const GetInstance(HWND hwnd = nullptr, HINSTANCE hInstance = nullptr)
		{
			if (mInstance == nullptr)
				mInstance = new Hardware(hwnd, hInstance);
			return mInstance;
		}

		inline static ID3D11Device* const GetDevice()
		{
			return mInstance->mDevice.Get();
		}

		inline static ID3D11DeviceContext* const GetContext() { return mInstance->mContext.Get(); }
		inline static IDXGISwapChain* const GetSwapChain() { return mInstance->mSwapChain.Get(); }

		Hardware(HWND hwnd, HINSTANCE hInstance);
		~Hardware();

		inline unsigned int GetWidth() const { return mInstance->mWidth; }
		inline unsigned int GetHeight() const { return mInstance->mHeight; }

	private:

		bool generateDeviceAndSwapChain();

		static Hardware* mInstance;

		ComPtr<ID3D11Device> mDevice;
		ComPtr<ID3D11DeviceContext> mContext;
		ComPtr<IDXGISwapChain> mSwapChain;

		HWND mWindow;
		HINSTANCE mHandle;

		unsigned int mWidth = 800;
		unsigned int mHeight = 600;
	} HW;

}