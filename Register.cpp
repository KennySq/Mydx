#include"pch.h"
#include"Register.h"

ID3D11Buffer* Mydx::Register::AsBuffer()
{
	return mBuffer;
}

ID3D11ShaderResourceView* Mydx::Register::AsResource()
{
	return mShaderResource;
}

Mydx::Register::Register(ID3D11Buffer* buffer) : mBuffer(buffer), mShaderResource(nullptr)
{}

Mydx::Register::Register(ID3D11ShaderResourceView* resource) : mShaderResource(resource), mBuffer(nullptr)
{}

Mydx::Register::~Register()
{}
