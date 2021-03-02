#include"pch.h"
#include"Shader.h"

namespace Mydx
{
	bool Pass::Generate()
	{
		if (bCompiled == true)
			return false;

		bool bResult = compile();

		return bResult;
	}

	void Pass::Release()
	{
		if (mVS != nullptr)
			mVS->Release();

		if (mGS != nullptr)
			mGS->Release();

		if (mDS != nullptr)
			mDS->Release();

		if (mHS != nullptr)
			mHS->Release();

		if (mPS != nullptr)
			mPS->Release();

		delete[] mName;

	}

	Pass::Pass(const char* path, const char* entry, unsigned long passType, unsigned long renderType)
		: mPath(path), mEntry(entry), mPassType(passType), mRenderType(static_cast<eRenderType>(renderType)),
		mVertexConstRegister(MAX_VERTEX_CONSTANT_REGISTER),
		mVertexTextureRegister(MAX_VERTEX_TEXTURE_REGISTER),
		mPixelConstRegister(MAX_PIXEL_CONSTANT_REGISTER),
		mPixelTextureRegister(MAX_PIXEL_TEXTURE_REGISTER)
	{
		string local = mPath;
		auto index = local.find_last_of('/') + 1;

		local = local.substr(index);

		mName = new char[local.size() + 1];

		strcpy(mName, local.c_str());

		Generate();
	}

	Pass::~Pass()
	{}

	bool Pass::operator<(const Pass* rhs)
	{
		if (mPath[0] < rhs->mPath[0])
		{
			return true;
		}

		return false;
	}

	bool Pass::compile()
	{
		USES_CONVERSION;

		unsigned long compileFlag = 0;

		HRESULT result = E_INVALIDARG;
		ID3DBlob* vBlob, * gBlob, * dBlob, * hBlob, * pBlob;
		ID3DBlob* errBlob = nullptr;

		ID3D11Device* device = HW::GetDevice();

	#ifdef _DEBUG
		compileFlag |= D3DCOMPILE_DEBUG;
	#endif

		if (mPassType & VERTEX)
		{
			string str = string(mEntry) + "VS";

			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "vs_5_0", compileFlag, 0, &vBlob, &errBlob);
	#ifdef _DEBUG
		if (result != S_OK && errBlob != nullptr)
		{
			std::cout << (const char*)errBlob->GetBufferPointer() << std::endl;
		}
	#endif

			assert(result == S_OK);

			if (result != S_OK)
				return false;

			ShaderReflection reflect(vBlob);

			for (unsigned int i = 0; i < reflect.mConstants.size(); i++)
			{
				string key = reflect.mConstants[i].Name;
				

			}

			result = device->CreateInputLayout(reflect.mInputElements.data(),
											   reflect.mInputElements.size(),
											   vBlob->GetBufferPointer(),
											   vBlob->GetBufferSize(),
											   mIL.GetAddressOf());


			result = device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (mPassType & GEOMETRY)
		{
			string str = string(mEntry) + "GS";
			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "gs_5_0", compileFlag, 0, &gBlob, &errBlob);
			assert(result == S_OK);

			if (result != S_OK)
				return false;

			result = device->CreateGeometryShader(gBlob->GetBufferPointer(), gBlob->GetBufferSize(), nullptr, mGS.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (mPassType & DMAIN)
		{
			string str = string(mEntry) + "DS";
			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "ds_5_0", compileFlag, 0, &dBlob, &errBlob);
			assert(result == S_OK);

			if (result != S_OK)
				return false;

			result = device->CreateDomainShader(dBlob->GetBufferPointer(), dBlob->GetBufferSize(), nullptr, mDS.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (mPassType & HULL)
		{
			string str = string(mEntry) + "HS";
			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "hs_5_0", compileFlag, 0, &hBlob, &errBlob);
			assert(result == S_OK);

			if (result != S_OK)
				return false;

			result = device->CreateHullShader(hBlob->GetBufferPointer(), hBlob->GetBufferSize(), nullptr, mHS.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (mPassType & PIXEL)
		{
			string str = string(mEntry) + "PS";
			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "ps_5_0", compileFlag, 0, &pBlob, &errBlob);
			assert(result == S_OK);

			if (result != S_OK)
				return false;

			result = device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, mPS.GetAddressOf());
			assert(result == S_OK);

			if (result != S_OK)
				return false;
		}

		if (result != S_OK)
			return false;

		return true;
	}

}