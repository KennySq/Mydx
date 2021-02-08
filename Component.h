#pragma once
namespace Mydx
{
	class Component
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float delta) = 0;
		virtual void Render(float delta) = 0;
		virtual void Release() = 0;


		const char* GetName() const { return mName; }
		unsigned long long GetComponentID() const { return mComponentID; }

		template<typename _Ty>
		inline _Ty* As()
		{
			return dynamic_cast<_Ty*>(this);
		}

		Component(const char* componentName);
		virtual ~Component() {}
	private:

		const char* mName;
		unsigned long long mComponentID;
		bool operator>(const Component& rhs);

	};
}
