#include "pch.h"
#include "Graphics.h"
#include"Scene.h"
#include"Camera.h"
#include"DirectionalLight.h"
namespace Mydx
{
	Graphics* Graphics::mInstance = nullptr;

	template<typename T>
	bool Graphics::CommitResource(ID3D11Buffer* buffer, T raw)
	{
		if (buffer == nullptr)
		{
			return false;
		}

		mContext->UpdateSubresource(buffer, 0, nullptr, raw, 0, 0);

		return true;
	}

	void Graphics::DefaultRenderState(Scene* scene)
	{
		Camera* camera = scene->GetCamera();

		ID3D11Buffer* cameraBuffer = camera->GetBuffer();
		ID3D11Buffer* group[] = { cameraBuffer };

		mContext->VSSetConstantBuffers(0, ARRAYSIZE(group), group);


	}

	Graphics::Graphics(ID3D11Device* device, ID3D11DeviceContext* context)
		: mDevice(device), mContext(context)
	{

	}

	Graphics::~Graphics()
	{}
}