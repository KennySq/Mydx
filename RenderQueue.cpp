#include "pch.h"
#include "RenderQueue.h"
#include"MeshRenderer.h"
#include"Instance.h"

namespace Mydx
{
    void RenderQueue::Push(Instance* renderInstance)
    {
        if (renderInstance == nullptr)
        {
            return;
        }

        MeshRenderer* mr = renderInstance->GetComponent<MeshRenderer>();

        if (mr == nullptr)
        {
            return;
        }

        mInstances.push(mr);
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