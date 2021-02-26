#pragma once

namespace Mydx
{
	class Scene;
	class DirectionalLight;
	typedef class Graphics
	{
	public:
		void DefaultRenderState(Scene* scene);

		template<typename T>
		bool CommitResource(ID3D11Buffer* buffer, T raw);

		Graphics(ID3D11Device* device, ID3D11DeviceContext* context);
		~Graphics();

		static Graphics* GetInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new Graphics(HW::GetDevice(), HW::GetContext());
			}

			return mInstance;

		}

	private:
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mContext;

		static Graphics* mInstance;

	} GPU;

	

}