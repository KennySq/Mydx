#pragma once

using namespace std;
#include"RenderQueue.h"
namespace Mydx
{
	class MeshRenderer;
	class Instance;
	class Camera;
	class DirectionalLight;
	class Scene
	{
	public:
		void AddInstance(Instance* instance);
		Instance* GetInstance(unsigned int index) const;

		void AddDirectionalLight(DirectionalLight* light);
		DirectionalLight* GetDirectionalLight(unsigned int index) const;

		Camera* GetCamera() const { return mSelectedCamera; }
	
		void Init();
		void Update(float delta);
		void Render(float delta);
		void Release();

		Scene(const char* name);
		~Scene();

	private:
		void renderScene();

		string mName;
		unsigned long long mSceneID;

		Camera* mSelectedCamera;

		vector<Instance*> mInstances;
		vector<MeshRenderer*> mRenderInstances;
		vector<DirectionalLight*> mDirectionalLights;

		RenderQueue mRenderQueue;

	};
}