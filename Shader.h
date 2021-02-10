#pragma once

#include"IMemory.h"
#include"ePassType.h"
#include"eRenderType.h"

using namespace Microsoft::WRL;
using namespace Mydx;

namespace Mydx
{
	constexpr int REGISTER_CAPACITY = 8;

	struct Pass : IMemory
	{
		
		// IMemory을(를) 통해 상속됨
		virtual bool Generate() override;
		virtual void Release() override;

		ID3D11VertexShader* GetVS() const { return mVS.Get(); }
		ID3D11GeometryShader* GetGS() const { return mGS.Get(); }
		ID3D11DomainShader* GetDS()const { return mDS.Get(); }
		ID3D11HullShader* GetHS() const { return mHS.Get(); }
		ID3D11PixelShader* GetPS()const { return mPS.Get(); }
		ID3D11InputLayout* GetIL() const { return mIL.Get(); }

		ID3D11ShaderResourceView* const* GetVertexResources() { return mVertexT; }
		ID3D11Buffer* const* GetVertexConstBuffers() { return mVertexC; }

		ID3D11ShaderResourceView* const* GetPixelResources() { return mPixelT; }
		ID3D11Buffer* const* GetPixelConstBuffers() { return mPixelC; }

		inline unsigned int GetVertexResourceCount() const { return mVTCount; }
		inline unsigned int GetPixelResourceCount() const { return mPTCount; }
		inline unsigned int GetVertexConstBufferCount()const { return mVCCount; }
		inline unsigned int GetPixelConstBufferCount() const { return mPCCount; }

		eRenderType GetRenderType() const { return mRenderType; }

		Pass(const char* path, const char* entry, unsigned long passType, unsigned long renderType);
		~Pass();

		

	private:
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

		// Registers
		// Vertex
		ID3D11ShaderResourceView* mVertexT[128];
		ID3D11Buffer* mVertexC[15];
		unsigned int mVTCount = 0;
		unsigned int mVCCount = 0;

		// Pixel 
		ID3D11ShaderResourceView* mPixelT[8];
		ID3D11Buffer* mPixelC[15];
		unsigned int mPTCount = 0;
		unsigned int mPCCount = 0;

		bool compile();
		bool reflect(ID3DBlob* vertexBlob, ID3D11InputLayout** pInputLayout, ID3D11ShaderReflection** pReflection);
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