#pragma once
#include<functional>

using namespace std;

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
	template<typename T>
	inline unsigned long long MakeHash(T val)
	{
		hash<T> h;
		unsigned long long v = h(val);
		return v;
	}
}