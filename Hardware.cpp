#include "pch.h"
#include "Hardware.h"

namespace Mydx
{
	Hardware* Hardware::mInstance = nullptr;
	Hardware::Hardware(HWND hwnd, HINSTANCE hInstance) : mWindow(hwnd), mHandle(hInstance), mWidth(800), mHeight(600)
	{
		generateDeviceAndSwapChain();
	}

	Hardware::~Hardware()
	{}

	bool Hardware::generateDeviceAndSwapChain()
	{
		DWORD flag = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		D3D_FEATURE_LEVEL featureLevel[] =
		{
			D3D_FEATURE_LEVEL_11_1
		};

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = mWidth;
		swapChainDesc.BufferDesc.Height = mHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = mWindow;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = true;

	#ifdef _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

		auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag,
													nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc,
													mSwapChain.GetAddressOf(), mDevice.GetAddressOf(),
													featureLevel, mContext.GetAddressOf());

		assert(result == S_OK);
		return true;
	}

}