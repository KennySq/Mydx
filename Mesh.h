#pragma once
#include"IMemory.h"
#include"eMeshType.h"
#include"Vertices.h"
namespace Mydx
{
	struct Mesh : IMemory
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

	private:

		ComPtr<ID3D11Buffer> mVertexBuffer;
		ComPtr<ID3D11Buffer> mIndexBuffer;

		unsigned int mStride;
		unsigned int mOffset;

		unsigned int mVertexCount = 0;
		unsigned int mIndexCount = 0;

		eMeshType mMeshType;
		eVertexType mVertexType;

	};
}