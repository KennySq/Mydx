#pragma once
#include"Vertices.h"

namespace Mydx
{
	namespace gen
	{
		const Mesh& GenerateSphere(float radius, unsigned int sliceCount, unsigned int stackCount);
		const Mesh& GenerateQuad();

		template<typename _VertTy>
		bool GenerateMeshBuffer(std::vector<_VertTy>& vertices, std::vector<UINT>& indices, Mesh& const buffer);
	}
}