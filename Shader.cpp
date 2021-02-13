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

void Mydx::Pass::AddCRegisterVertex(ID3D11Buffer* buffer)
{
	if (mVCCount >= 15 || mVCCount < 0 || buffer == nullptr)
	{
		return;
	}

	mVertexC[mVCCount++] = buffer;
}

void Mydx::Pass::AddTRegisterVertex(ID3D11ShaderResourceView* resource)
{
	if (mVTCount >= 15 || mVTCount < 0 || resource == nullptr)
	{
		return;
	}

	mVertexT[mVTCount++] = resource;
}

void Mydx::Pass::AddCRegisterPixel(ID3D11Buffer* buffer)
{
	if (mPCCount >= 15 || mPCCount < 0 || buffer == nullptr)
	{
		return;
	}

	mPixelC[mPCCount++] = buffer;
}

void Mydx::Pass::AddTRegisterPixel(ID3D11ShaderResourceView* resource)
{
	if (mPTCount >= 8 || mPTCount < 0 || resource == nullptr)
	{
		return;
	}

	mPixelT[mPTCount++] = resource;
}

Pass::Pass(const char* path, const char* entry, unsigned long passType, unsigned long renderType) : mPath(path), mEntry(entry), mPassType(passType), mRenderType(static_cast<eRenderType>(renderType))
{
	Generate();
}

Pass::~Pass()
{
}

bool Pass::compile()
{
	USES_CONVERSION;

	unsigned long compileFlag = 0;

	HRESULT result = E_INVALIDARG;
	ID3DBlob* vBlob, * gBlob, * dBlob, * hBlob, * pBlob;
	ID3DBlob* errBlob;

	ID3D11Device* device = HW::GetDevice();

#ifdef _DEBUG
	compileFlag |= D3DCOMPILE_DEBUG;
#endif

	if (mPassType & VERTEX)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "vs_5_0", compileFlag, 0, &vBlob, &errBlob);
		assert(result == S_OK);

		if (result != S_OK)
			return false;

		ComPtr<ID3D11ShaderReflection> sr;

		reflect(vBlob, mIL.GetAddressOf(), sr.GetAddressOf());

		result = device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), nullptr, mVS.GetAddressOf());
		assert(result == S_OK);

		if (result != S_OK)
			return false;
	}

	if (mPassType & GEOMETRY)
	{
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "gs_5_0", compileFlag, 0, &gBlob, &errBlob);
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
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "ds_5_0", compileFlag, 0, &dBlob, &errBlob);
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
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "hs_5_0", compileFlag, 0, &hBlob, &errBlob);
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
		result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, mEntry, "ds_5_0", compileFlag, 0, &pBlob, &errBlob);
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

bool Mydx::Pass::reflect(ID3DBlob* vertexBlob, ID3D11InputLayout** pInputLayout, ID3D11ShaderReflection** pReflection)
{
	HRESULT result;

	auto device = HW::GetDevice();

	result = D3DReflect(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), __uuidof(ID3D11ShaderReflection), (void**)pReflection);
	assert(result == S_OK);
	if (result != S_OK)
		return false;

	unsigned int byteOffset = 0;
	D3D11_SHADER_DESC shaderDesc{};
	vector<D3D11_INPUT_ELEMENT_DESC> inputElements;
	D3D11_SIGNATURE_PARAMETER_DESC signParam;
	pReflection[0]->GetDesc(&shaderDesc);
	for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
	{
		pReflection[0]->GetInputParameterDesc(i, &signParam);

		D3D11_INPUT_ELEMENT_DESC element;

		element.SemanticName = signParam.SemanticName;
		element.SemanticIndex = signParam.SemanticIndex;
		element.InputSlot = 0;
		element.AlignedByteOffset = byteOffset;
		element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		element.InstanceDataStepRate = 0;

		if (signParam.Mask == 1)
		{
			if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32_UINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32_SINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32_FLOAT;

			byteOffset += 4;
		}
		else if (signParam.Mask <= 3)
		{
			if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32_UINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32_SINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32_FLOAT;
			byteOffset += 8;
		}
		else if (signParam.Mask <= 7)
		{
			if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			byteOffset += 12;
		}

		else if (signParam.Mask <= 15)
		{
			if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			byteOffset += 16;
		}


		inputElements.push_back(element);
	}

	result = device->CreateInputLayout(inputElements.data(), inputElements.size(), vertexBlob->GetBufferPointer(), static_cast<unsigned int>(vertexBlob->GetBufferSize()), pInputLayout);
	assert(result == S_OK);

	if (result != S_OK)
		return false;

	return true;
}
