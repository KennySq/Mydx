#include"pch.h"
#include"Mesh.h"
#include"MeshLoader.h"

namespace Mydx
{

	bool Mesh::Generate()
	{


		return true;
	}

	void Mesh::Release()
	{}

	Mesh::Mesh(eMeshType meshType, eVertexType vertexType) : mMeshType(meshType), mVertexType(vertexType)
	{
		switch (vertexType)
		{
			case eVertexType::STATIC:
				mStride = sizeof(StaticVertex);
				break;

		}

		mOffset = 0;

	}

	Mesh::Mesh(const Mesh& rhs)
	{
		mVertexBuffer = rhs.mVertexBuffer;
		mIndexBuffer = rhs.mIndexBuffer;

		mVertexCount = rhs.mVertexCount;
		mIndexCount = rhs.mIndexCount;

		mStride = rhs.mStride;
		mOffset = rhs.mOffset;
	}

	Mesh::~Mesh()
	{

	}

	bool Mesh::Load(const char* path)
	{


		return true;
	}
}