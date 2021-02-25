#pragma once


namespace Mydx
{
	typedef class Graphics
	{
		template<typename T>
		bool CommitResource(ID3D11Buffer* buffer, T raw);

		Graphics(ID3D11Device* device, ID3D11DeviceContext* context);
		~Graphics();

		Graphics* GetInstance() const
		{
			if (mInstance == nullptr)
			{
				mInstance = new Graphics(HW::GetDevice(), HW::GetContext());
			}

		}

	private:
		ID3D11Device* mDevice;
		ID3D11DeviceContext* mContext;

		static Graphics* mInstance;

	} GPU;



}