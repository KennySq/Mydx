#include"pch.h"
#include"Scene.h"
#include"RenderQueue.h"

#include"Instance.h"
#include"MeshRenderer.h"

#include"Camera.h"
#include"Renderer.h"

#include"DirectionalLight.h"

namespace Mydx
{
    void Scene::AddInstance(Instance* instance)
    {
        if (instance == nullptr)
        {   
            return;
        }
        mInstances.push_back(instance);

        MeshRenderer* mr = instance->GetComponent<MeshRenderer>();

        if (mr == nullptr)
        {
            return;
        }

        mRenderQueue.Push(mr);
    }

    Instance* Scene::GetInstance(unsigned int index) const
    {
        if (index < 0 || index >= mInstances.size())
        {
            return nullptr;
        }

        return mInstances[index];
    }
    void Scene::AddDirectionalLight(DirectionalLight* light)
    {
        if (light == nullptr)
        {
            return;
        }

        mDirectionalLights.push_back(light);
    }
    DirectionalLight* Scene::GetDirectionalLight(unsigned int index) const
    {
        if (index < 0 || index >= mDirectionalLights.size())
        {
            return nullptr;
        }
        return mDirectionalLights[index];
    }
    void Scene::Init()
    {
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
    {
        Renderer2D& r2d = Renderer2D::GetInstance();

        Texture2D* tex = r2d.GetTexture2D(0);
        Texture2D* depth = r2d.GetTexture2D(1);
        Viewport* viewport = new Viewport(tex, depth, 800, 600, 0, 0);
        mSelectedCamera = new Camera(5.0f, 0.0f, 0.0f, 60.0f, 1.333f, viewport);

    }
    Scene::~Scene()
    {}
    void Scene::renderScene()
    {
        static Renderer2D& r2d = Renderer2D::GetInstance();
        size_t renderCount = mRenderQueue.GetCount();
        Viewport* viewport = mSelectedCamera->GetViewport();

        mSelectedCamera->Update();

        for (int i = 0; i < renderCount; i++)
        {
            MeshRenderer* inst = mRenderQueue.Pop();
            Pass* pass = inst->GetPass();
            
            eRenderType type = pass->GetRenderType();
            bool bCriteria = pass == nullptr || mSelectedCamera == nullptr || viewport == nullptr;
            if (bCriteria == true)
            {
                continue;
            }

            switch (type)
            {
                case FORWARD:
                    inst->Update(0.0f);
                    inst->DrawForward(viewport->GetImage(), viewport->GetDepth(), viewport);
                    break;
                default:
                    break;
            }
            mRenderQueue.Push(inst);
        }
       


    }
}