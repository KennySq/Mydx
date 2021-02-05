#pragma once

inline unsigned long GetRefCount(IUnknown* unknown)
{
	unknown->AddRef();
	return unknown->Release();
}