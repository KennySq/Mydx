#pragma once
#include"Register.h"

using namespace std;

namespace Mydx
{
	class RegisterVector : public vector<Register>
	{
	public:
		RegisterVector(size_t size);
		RegisterVector(const RegisterVector& rhs) = delete;
		~RegisterVector();

		void push_back(Register reg);

	private:
		size_t mMaxSize;
	};
}
