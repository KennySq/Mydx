#include"pch.h"
#include"Scene.h"

#include"Instance.h"
#include"MeshRenderer.h"

namespace Mydx
{
    void Scene::AddInstance(Instance* instance)
    {
        if (instance == nullptr)
        {
            return;
        }
        mInstances.push_back(instance);

        MeshRenderer* renderComponent = instance->GetComponent<MeshRenderer>();

        if (renderComponent == nullptr)
        {
            return;
        }

        mRenderInstances.push_back(renderComponent);
    }

    Instance* Scene::GetInstance(unsigned int index) const
    {
        if (index < 0 || index >= mInstances.size())
        {
            return nullptr;
        }

        return mInstances[index];
    }
    void Scene::Init()
    {
        
    }
    void Scene::Update(float delta)
    {
        for (auto i : mRenderInstances)
        {
            
        }
    }
    void Scene::Render(float delta)
    {
        
    }
    void Scene::Release()
    {
        
    }
    Scene::Scene(const char* name) : mName(name)
    {}
    Scene::~Scene()
    {}
}