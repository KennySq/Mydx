#pragma once
#include"Utility.h"
#include<vector>
#include<unordered_map>
namespace Mydx
{
	class Pass;
	class Precache
	{
	public:
		static bool AddPass(Pass* pass);
		static Pass* GetPass(std::string name);

		static Precache* GetInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new Precache();
			}

			return mInstance;
		}

	private:
		unordered_map<std::string, Pass*> mShaderContainer;
		static Precache* mInstance;
	};


}