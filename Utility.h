#pragma once

namespace Mydx
{
	inline unsigned long GetRefCount(IUnknown* unknown)
	{
		unknown->AddRef();
		return unknown->Release();
	}

	inline unsigned long long GenerateInstanceID()
	{
		static unsigned long long iid = -1;

		return ++iid;
	}

	inline unsigned long long GenerateComponentID()
	{
		static unsigned long long cid = -1;

		return ++cid;
	}
}