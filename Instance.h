#pragma once

#include"Shader.h"
#include"Utility.h"
#include"Component.h"
#include"Transform.h"

using namespace std;

namespace Mydx
{
	class Transform;
	class Instance
	{
	public:

		Instance();
		Instance(const Instance& rhs);
		~Instance();

		inline Transform* const GetTransform() { return &mTransform; }

		template<typename _Comp>
		bool AddComponent();

		template<typename _Comp>
		_Comp* GetComponent();
	private:
		unsigned long long mInstanceID;
		const char* mName;

		unordered_map<unsigned long long, Component*> mComponents;
		Transform mTransform;
	};

	template<typename _Comp>
	inline bool Instance::AddComponent()
	{
		Component* comp = new _Comp();

		mComponents.insert_or_assign(typeid(_Comp).hash_code(), comp);

		return true;
	}

	template<typename _Comp>
	inline _Comp* Instance::GetComponent()
	{
		size_t typeHash = typeid(_Comp).hash_code();

		return dynamic_cast<_Comp*>(mComponents[typeHash]);
	}



}