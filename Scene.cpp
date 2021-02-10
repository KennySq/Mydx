#include"pch.h"
#include"Scene.h"

#include"Instance.h"
#include"MeshRenderer.h"
#include"Camera.h"
#include"Renderer.h"

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
        Renderer2D& r2d = Renderer2D::GetInstance();
        
        Texture2D* tex = r2d.GetTexture2D(0);
        Texture2D* depth = r2d.GetTexture2D(1);
        Viewport* viewport = new Viewport(tex, depth, 800, 600, 0, 0);
        mSelectedCamera = new Camera(5.0f, 0.0f, 0.0f, 60.0f, 1.333f, viewport);
    }
    void Scene::Update(float delta)
    {
        renderScene();
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
    void Scene::renderScene()
    {
        static Renderer2D& r2d = Renderer2D::GetInstance();
        for (auto i : mRenderInstances)
        {
            Pass* pass = i->GetPass();
            if (pass == nullptr || mSelectedCamera == nullptr)
            {
                continue;
            }
            eRenderType type = pass->GetRenderType();
            
            Viewport* viewport = mSelectedCamera->GetViewport();
            if (viewport == nullptr)
            {
                continue;
            }
            switch (type)
            {
                case FORWARD:
                    i->DrawForward(viewport->GetImage(), viewport->GetDepth(), viewport);
                    break;
            }
        }
    }
}