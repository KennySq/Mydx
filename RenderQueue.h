#pragma once
#include<queue>

using namespace std;

namespace Mydx
{
	class Instance;
	class MeshRenderer;
	typedef class RenderQueue
	{
	public:
		void Push(Instance* renderInstance);
		MeshRenderer* Pop();

		inline size_t GetCount() const { return mInstances.size(); }
		
	private:
		queue<MeshRenderer*> mInstances;

	} RQF;
}