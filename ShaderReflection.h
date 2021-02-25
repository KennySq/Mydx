#pragma once
#include"ePassType.h"
namespace Mydx
{
	class ShaderReflection
	{
	public:

		vector<D3D11_SHADER_VARIABLE_DESC> mVariables;
		vector<D3D11_SHADER_INPUT_BIND_DESC> mTextures;

		vector<D3D11_INPUT_ELEMENT_DESC> mInputElements;

		D3D11_SHADER_DESC mShader;

		ShaderReflection(ID3DBlob* blob);
		ShaderReflection(const ShaderReflection& rhs) = delete;
		~ShaderReflection();

	private:
		ComPtr<ID3D11ShaderReflection> mReflection;
		vector<ID3D11ShaderReflectionConstantBuffer*> mConstantBufers;
		vector<ID3D11ShaderReflectionVariable*> mConstantBufferVariables;

		bool reflectInputLayout();
		bool reflectBoundResources();

	};
}