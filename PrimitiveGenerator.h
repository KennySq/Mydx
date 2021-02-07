#pragma once
#include"Vertices.h"
#include"Mesh.h"

namespace Mydx
{
	class PrimitiveGenerator
	{
	public:
		static const shared_ptr<Mesh> GenerateSphere(float radius, unsigned int sliceCount, unsigned int stackCount);
		static const Mesh& GenerateQuad();

		template<typename _VertTy>
		static bool GenerateMeshBuffer(std::vector<_VertTy>& vertices, std::vector<UINT>& indices, Mesh& const buffer);
	};
}