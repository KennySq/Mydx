#pragma once

namespace Mydx
{
	class IFile
	{
		virtual bool Load(const char* path) = 0;
	};
}