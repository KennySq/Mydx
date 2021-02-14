#include "pch.h"
#include "RenderQueue.h"
#include"MeshRenderer.h"
#include"Instance.h"

namespace Mydx
{
    void RenderQueue::Push(MeshRenderer* renderInstance)
    {
        if (renderInstance == nullptr)
        {
            return;
        }

        mInstances.push(renderInstance);
    }
    MeshRenderer* RenderQueue::Pop()
    {
        if (mInstances.size() == 0)
        {
            return nullptr;
        }
        MeshRenderer* mr = mInstances.front();
        mInstances.pop();
        return mr;
    }

}