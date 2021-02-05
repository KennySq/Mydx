#pragma once
#include<fstream>

namespace Mydx
{
	struct IFile
	{
		virtual bool Load(const char* path) = 0;
		virtual void Unload() = 0;
	};
}