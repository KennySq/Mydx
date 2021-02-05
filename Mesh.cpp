#include"pch.h"
#include"Mesh.h"

bool Mydx::Mesh::Generate()
{
	

	return true;
}

void Mydx::Mesh::Release()
{}

Mydx::Mesh::Mesh(eMeshType meshType, eVertexType vertexType) : mMeshType(meshType), mVertexType(vertexType)
{
	
}

Mydx::Mesh::Mesh(const Mesh& rhs)
{
	mVertexBuffer = rhs.mVertexBuffer;
	mIndexBuffer = rhs.mIndexBuffer;

	mVertexCount = rhs.mVertexCount;
	mIndexCount = rhs.mIndexCount;
}

Mydx::Mesh::~Mesh()
{

}
