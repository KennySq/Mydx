#include"pch.h"
#include"Shader.h"
#include<atlbase.h>

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

}

Pass::Pass(const char* path, const char* entry, unsigned long flag) : mPath(path), mEntry(entry), mFlag(flag)
{

}

Pass::~Pass()
{

}

bool Pass::compile()
{
	USES_CONVERSION;

	unsigned long compileFlag = 0;

	HRESULT result = E_INVALIDARG;
	ID3DBlob* VBlob, * GBlob, * DBlob, * HBlob, * PBlob;
	ID3DBlob* ErrBlob;

	ID3D11Device* device = HW::GetDevice();

#ifdef _DEBUG
	compileFlag |= D3DCOMPILE_DEBUG;
#endif

	if (mFlag & eVertex)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "vs_5_1", compileFlag, 0, &VBlob, &ErrBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		result = device->CreateVertexShader(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (mFlag & eGeometry)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "gs_5_1", compileFlag, 0, &GBlob, &ErrBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		result = device->CreateGeometryShader(GBlob->GetBufferPointer(), GBlob->GetBufferSize(), nullptr, mGS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (mFlag & eDomain)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "ds_5_1", compileFlag, 0, &DBlob, &ErrBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		result = device->CreateDomainShader(DBlob->GetBufferPointer(), DBlob->GetBufferSize(), nullptr, mDS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (mFlag & eHull)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "hs_5_1", compileFlag, 0, &HBlob, &ErrBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		result = device->CreateHullShader(HBlob->GetBufferPointer(), HBlob->GetBufferSize(), nullptr, mHS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (mFlag & ePixel)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "ds_5_1", compileFlag, 0, &PBlob, &ErrBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		result = device->CreatePixelShader(PBlob->GetBufferPointer(), PBlob->GetBufferSize(), nullptr, mPS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (result != S_OK)
		return false;

	return true;
}
