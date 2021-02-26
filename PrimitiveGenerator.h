#pragma once
#include"Vertices.h"
#include"Mesh.h"

namespace Mydx
{
	class PrimitiveGenerator
	{
	public:
		static Mesh* GenerateSphere(float radius, unsigned int sliceCount, unsigned int stackCount);
		static const Mesh& GenerateQuad();


	private:
		template<typename _VertTy>
		static bool generateMeshBuffer(std::vector<_VertTy>& vertices, std::vector<UINT>& indices, Mesh& const buffer);
	};
}