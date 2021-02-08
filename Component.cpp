#include "pch.h"
#include "Component.h"

namespace Mydx
{
    Component::Component(const char* componentName) : mName(componentName), mComponentID(GenerateComponentID())
    {}

    bool Component::operator>(const Component& rhs)
    {
        return mComponentID > rhs.mComponentID;
    }
}