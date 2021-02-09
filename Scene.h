#pragma once

using namespace std;

namespace Mydx
{
	class MeshRenderer;
	class Instance;
	class Scene
	{
	public:
		void AddInstance(Instance* instance);
		Instance* GetInstance(unsigned int index) const;
	
		void Init();
		void Update(float delta);
		void Render(float delta);
		void Release();

		Scene(const char* name);
		~Scene();

	private:
		const char* mName;
		unsigned long long mSceneID;

		vector<Instance*> mInstances;
		vector<MeshRenderer*> mRenderInstances;

	};
}