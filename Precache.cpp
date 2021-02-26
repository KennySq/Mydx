#include "pch.h"
#include "Precache.h"
#include"Shader.h"

namespace Mydx
{
	Precache* Mydx::Precache::mInstance = nullptr;

	bool Precache::AddPass(Pass* pass)
	{
		Precache* cache = GetInstance();

		if (pass == nullptr)
		{
			return false;
		}

		const char* name = pass->GetName();

		if (cache->mShaderContainer.find(name) != cache->mShaderContainer.end())
		{
			return false;
		}

		cache->mShaderContainer.insert_or_assign(name, pass);

	}
	Pass* Precache::GetPass(const char* name)
	{
		return GetInstance()->mShaderContainer.find(name)->second;
	}
}