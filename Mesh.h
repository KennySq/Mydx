#pragma once
#include"IMemory.h"
#include"IFile.h"
#include"eMeshType.h"
#include"Vertices.h"
namespace Mydx
{
	class MeshLoader;
	struct Mesh : IMemory, IFile
	{
		virtual bool Generate() override;
		virtual void Release() override;

		Mesh(eMeshType meshType, eVertexType vertexType);

		Mesh(const Mesh& rhs);
		~Mesh();

		inline ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer.Get(); }
		inline ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer.Get(); }

		inline unsigned int GetStride() const { return mStride; }
		inline unsigned int GetOffset() const { return mOffset; }
		inline unsigned int GetVertexCount() const { return mVertexCount; }
		inline unsigned int GetIndexCount() const { return mIndexCount; }
		

		friend class PrimitiveGenerator;
		friend class MeshLoader;
	private:
	
		ComPtr<ID3D11Buffer> mVertexBuffer;
		ComPtr<ID3D11Buffer> mIndexBuffer;

		unsigned int mStride = 0;
		unsigned int mOffset = 0;

		unsigned int mVertexCount = 0;
		unsigned int mIndexCount = 0;

		eMeshType mMeshType;
		eVertexType mVertexType;


		// IFile을(를) 통해 상속됨
		virtual bool Load(const char* path) override;

	};
}