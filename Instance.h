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
		_Comp* AddComponent();

		template<typename _Comp>
		_Comp* GetComponent() const;
	private:
		unsigned long long mInstanceID;
		string mName;

		unordered_map<unsigned long long, Component*> mComponents;
		Transform mTransform;
	};

	template<typename _Comp>
	inline _Comp* Instance::AddComponent()
	{
		Component* comp = new _Comp();

		comp->SetRoot(this);
		mComponents.insert_or_assign(typeid(_Comp).hash_code(), comp);
		
		return static_cast<_Comp*>(comp);
	}

	template<typename _Comp>
	inline _Comp* Instance::GetComponent() const
	{
		size_t typeHash = typeid(_Comp).hash_code();

		Component* comp = mComponents.at(typeHash);

		return static_cast<_Comp*>(comp);
	}
}