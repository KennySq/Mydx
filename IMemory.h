#pragma once

namespace Mydx
{
	struct IMemory
	{
		virtual bool Update() { return true; }
		virtual bool Generate() = 0;
		virtual void Release() = 0;
	};
}