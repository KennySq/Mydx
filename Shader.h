#pragma once

#include"IMemory.h"
#include"ePassType.h"
#include"eRenderType.h"
#include"ShaderReflection.h"
#include"RegisterMap.h"

using namespace Microsoft::WRL;
using namespace Mydx;

namespace Mydx
{
	constexpr unsigned int MAX_VERTEX_CONSTANT_REGISTER = 15;
	constexpr unsigned int MAX_VERTEX_TEXTURE_REGISTER = 128;
	constexpr unsigned int MAX_PIXEL_CONSTANT_REGISTER = 15;
	constexpr unsigned int MAX_PIXEL_TEXTURE_REGISTER = 8;

	struct Pass : IMemory
	{
		virtual bool Generate() override;
		virtual void Release() override;

		ID3D11VertexShader* GetVS() const { return mVS.Get(); }
		ID3D11GeometryShader* GetGS() const { return mGS.Get(); }
		ID3D11DomainShader* GetDS()const { return mDS.Get(); }
		ID3D11HullShader* GetHS() const { return mHS.Get(); }
		ID3D11PixelShader* GetPS()const { return mPS.Get(); }
		ID3D11InputLayout* GetIL() const { return mIL.Get(); }

		eRenderType GetRenderType() const { return mRenderType; }

		const char* GetName() const { return mName; }
		
		Pass(const char* path, const char* entry, unsigned long passType, unsigned long renderType);
		~Pass();

		bool operator<(const Pass* rhs);

	private:
		char* mName;
		const char* mPath;
		const char* mEntry;
		unsigned long mPassType;
		bool bCompiled = false;

		eRenderType mRenderType;

		ComPtr<ID3D11VertexShader> mVS;
		ComPtr<ID3D11InputLayout> mIL;
		ComPtr<ID3D11GeometryShader> mGS;
		ComPtr<ID3D11DomainShader> mDS;
		ComPtr<ID3D11HullShader> mHS;
		ComPtr<ID3D11PixelShader> mPS;

		RegisterMap mVertexConstRegister;
		RegisterMap mVertexTextureRegister;

		RegisterMap mPixelConstRegister;
		RegisterMap mPixelTextureRegister;

		bool compile();
	
	};

	template<typename _BufTy>
	struct Compute : IMemory
	{
		bool bCompiled = false;
		const char* mPath;
		const char* mEntry;

		ComPtr<ID3D11ComputeShader> mCS;
		ComPtr<ID3D11Buffer> mConstBuffer[15];
		ComPtr<ID3D11ShaderResourceView> mTextures[8];

		unsigned int mConstRegister = 0;
		unsigned int mTextureRegister = 0;

		unsigned int mBufferCount = 0;

		// IMemory을(를) 통해 상속됨
		virtual bool Generate() override
		{
			ID3D11Device* device = HW::GetDevice();
			D3D11_BUFFER_DESC bufferDesc{};

			bufferDesc.ByteWidth = sizeof(_BufTy) * mBufferCount;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

			//	device->CreateBuffer(&bufferDesc, nullptr, mConstBuffer)

			return true;
		}

		virtual void Release() override
		{
			if (mCS != nullptr)
				mCS->Release();

			for (int i = 0; i < mConstRegister; i++)
				mConstBuffer[i]->Release();

			for (int i = 0; i < mTextureRegister; i++)
				mTextures[i]->Release();

		}

	};
}