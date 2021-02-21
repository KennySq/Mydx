#pragma once
#include<iostream>
#include<fstream>
#include"eMeshType.h"
#include"eRenderType.h"
#include"Vertices.h"

using namespace std;

namespace Mydx
{
	class Mesh;
	class MeshLoader
	{
	public:
		MeshLoader(const char* path);
		MeshLoader(const MeshLoader& rhs) = delete;
		~MeshLoader();
		
		Mesh* GetMesh() const { return mMesh; }

	private:
		HRESULT loadStaticModelFromFile(const char* path);
		HRESULT createStaticMeshBuffer();

		vector<StaticVertex> mVertices;
		vector<unsigned int> mIndices;
		Mesh* mMesh;
	};
}