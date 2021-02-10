#include"pch.h"
#include "Instance.h"


namespace Mydx
{
	Instance::Instance() : mInstanceID(GenerateInstanceID()),
		mName((string("New Object") + std::to_string(mInstanceID))),
		mTransform()
	{
	}

	Instance::Instance(const Instance& rhs) : mInstanceID(GenerateInstanceID()) ,mName(rhs.mName), mTransform(rhs.mTransform)
	{

	}

	Instance::~Instance()
	{
	}
}