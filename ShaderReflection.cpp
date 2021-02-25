#include"pch.h"
#include"ShaderReflection.h"

namespace Mydx
{
	ShaderReflection::ShaderReflection(ID3DBlob* blob)
	{
		void** ptr = reinterpret_cast<void**>(mReflection.GetAddressOf());
		D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), __uuidof(ID3D11ShaderReflection), ptr);

		mReflection->GetDesc(&mShader);

		reflectInputLayout();
		reflectBoundResources();


	}

	ShaderReflection::~ShaderReflection()
	{}

	bool ShaderReflection::reflectInputLayout()
	{
		HRESULT result;

		unsigned int byteOffset = 0;
		D3D11_SHADER_DESC shaderDesc{};

		D3D11_SIGNATURE_PARAMETER_DESC signParam;
		mReflection->GetDesc(&shaderDesc);
		for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
		{
			mReflection->GetInputParameterDesc(i, &signParam);

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

			mInputElements.push_back(element);
		}

		return true;
	}

	bool ShaderReflection::reflectBoundResources()
	{
		unsigned int resource = mShader.BoundResources;

		for (unsigned int i = 0; i < resource; i++)
		{
			D3D11_SHADER_INPUT_BIND_DESC inputDesc;

			mReflection->GetResourceBindingDesc(i, &inputDesc);
			


			mTextures.emplace_back(inputDesc);

		}
		D3D11_SHADER_INPUT_BIND_DESC cubeDesc;
		mReflection->GetResourceBindingDescByName("sampleCubemap", &cubeDesc);
			
		mTextures.emplace_back(cubeDesc);

		return true;
	}
}