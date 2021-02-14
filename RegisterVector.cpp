#include"pch.h"
#include"RegisterVector.h"

namespace Mydx
{
	RegisterVector::RegisterVector(size_t size) : mMaxSize(size)
	{
	}

	RegisterVector::~RegisterVector()
	{}

	void RegisterVector::push_back(Register reg)
	{
		size_t currentSize = size();

		if (currentSize >= mMaxSize)
		{
			return;
		}

		vector::push_back(reg);

	}
}