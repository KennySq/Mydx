#pragma once

namespace Mydx
{
	class Register
	{

	public:
		ID3D11Buffer* AsBuffer();
		ID3D11ShaderResourceView* AsResource();

		Register(ID3D11Buffer* buffer);
		Register(ID3D11ShaderResourceView* resource);
		~Register();

	private:
		ID3D11Buffer* mBuffer;
		ID3D11ShaderResourceView* mShaderResource;
	};
}