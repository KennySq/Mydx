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

	}

	Pass::Pass(const char* path, const char* entry, unsigned long passType, unsigned long renderType)
		: mPath(path), mEntry(entry), mPassType(passType), mRenderType(static_cast<eRenderType>(renderType))
	{
		Generate();
	}

	Pass::~Pass()
	{}

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
			string str = string(mEntry) + "VS";

			result = D3DCompileFromFile(A2W(mPath), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, str.c_str(), "vs_5_0", compileFlag, 0, &vBlob, &errBlob);
		#ifdef _DEBUG
			if (result != S_OK)
			{
				std::cout << (const char*)errBlob->GetBufferPointer() << std::endl;
			}
		#endif

			assert(result == S_OK);

			if (result != S_OK)
				return false;

			reflect(vBlob, mIL.GetAddressOf(), mReflection.GetAddressOf());

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

	bool Pass::reflectRegisters()
	{
		D3D11_SHADER_INPUT_BIND_DESC varDesc{};
		
		mReflection->GetResourceBindingDesc(0, &varDesc);
		

		return true;
	}

}