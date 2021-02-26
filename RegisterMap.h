#pragma once
#include"Register.h"

namespace Mydx
{
	
	class RegisterMap
		: public std::unordered_map<unsigned long long, Register>
	{
	public:
		
		inline void Alloc(unsigned long long key) {
			assert(size() < mMaxSize);
			
			if(size() < mMaxSize)
				insert_or_assign(key, Register());
		}

		RegisterMap(unsigned int maxSize);
		~RegisterMap();
	private:
		unsigned int mMaxSize;
	};
}