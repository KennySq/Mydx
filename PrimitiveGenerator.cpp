#include "pch.h"
#include "PrimitiveGenerator.h"


namespace Mydx
{
		Mesh* PrimitiveGenerator::GenerateSphere(float radius, unsigned int sliceCount, unsigned int stackCount)
		{
			std::vector<StaticVertex> vertices;
			std::vector<UINT> indices;

			Mesh* mesh = new Mesh(eMeshType::PRIMITIVE, eVertexType::STATIC);

			StaticVertex topVertex(0.0f, +radius, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			StaticVertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);

			vertices.push_back(topVertex);

			float phiStep = 3.141592f / stackCount;
			float thetaStep = 2.0f * 3.141592f / sliceCount;

			// Compute vertices for each stack ring (do not count the poles as rings).
			for (UINT i = 1; i <= stackCount - 1; ++i)
			{
				float phi = i * phiStep;

				// Vertices of ring.
				for (UINT j = 0; j <= sliceCount; ++j)
				{
					float theta = j * thetaStep;

					StaticVertex v;

					// spherical to cartesian
					v.mPosition.x = radius * sinf(phi) * cosf(theta);
					v.mPosition.y = radius * cosf(phi);
					v.mPosition.z = radius * sinf(phi) * sinf(theta);

					//// Partial derivative of P with respect to theta
					//v.TangentU.x = -radius * sinf(phi)*sinf(theta);
					//v.TangentU.y = 0.0f;
					//v.TangentU.z = +radius * sinf(phi)*cosf(theta);

					//XMVECTOR T = XMLoadFloat3(&v.TangentU);
					//XMStoreFloat3(&v.TangentU, XMVector3Normalize(T));

					XMVECTOR p = XMLoadFloat4(&v.mPosition);
					XMStoreFloat3(&v.mNormal, XMVector3Normalize(p));

					v.mTexcoord.x = theta / XM_2PI;
					v.mTexcoord.y = phi / XM_PI;

					vertices.push_back(v);
				}
			}

			vertices.push_back(bottomVertex);

			//
			// Compute indices for top stack.  The top stack was written first to the vertex buffer
			// and connects the top pole to the first ring.
			//

			for (UINT i = 1; i <= sliceCount; ++i)
			{
				indices.push_back(0);
				indices.push_back(i + 1);
				indices.push_back(i);
			}

			//
			// Compute indices for inner stacks (not connected to poles).
			//

			// Offset the indices to the index of the first vertex in the first ring.
			// This is just skipping the top pole vertex.
			UINT baseIndex = 1;
			UINT ringVertexCount = sliceCount + 1;
			for (UINT i = 0; i < stackCount - 2; ++i)
			{
				for (UINT j = 0; j < sliceCount; ++j)
				{
					indices.push_back(baseIndex + i * ringVertexCount + j);
					indices.push_back(baseIndex + i * ringVertexCount + j + 1);
					indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

					indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
					indices.push_back(baseIndex + i * ringVertexCount + j + 1);
					indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
				}
			}

			//
			// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
			// and connects the bottom pole to the bottom ring.
			//

			// South pole vertex was added last.
			UINT southPoleIndex = (UINT)vertices.size() - 1;

			// Offset the indices to the index of the first vertex in the last ring.
			baseIndex = southPoleIndex - ringVertexCount;

			for (UINT i = 0; i < sliceCount; ++i)
			{
				indices.push_back(southPoleIndex);
				indices.push_back(baseIndex + i);
				indices.push_back(baseIndex + i + 1);
			}

			generateMeshBuffer<StaticVertex>(vertices, indices, *mesh);

			return mesh;
		}

		template<typename _VertTy>
		bool PrimitiveGenerator::generateMeshBuffer(std::vector<_VertTy>& vertices, std::vector<UINT>& indices, Mesh& const buffer)
		{
			HRESULT hresult;
			ID3D11Device* device = HW::GetDevice();

			size_t vertCount = vertices.size();
			size_t indCount = indices.size();

			D3D11_BUFFER_DESC vDesc{}, iDesc{};
			D3D11_SUBRESOURCE_DATA vSub{}, iSub{};

			vDesc.ByteWidth = static_cast<unsigned int>(sizeof(_VertTy) * vertCount);
			vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vDesc.Usage = D3D11_USAGE_DEFAULT;

			iDesc.ByteWidth = static_cast<unsigned int>(sizeof(unsigned int) * indCount);
			iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			iDesc.Usage = D3D11_USAGE_DEFAULT;

			vSub.pSysMem = vertices.data();
			iSub.pSysMem = indices.data();

			buffer.mVertexCount = static_cast<unsigned int>(vertices.size());
			buffer.mIndexCount = static_cast<unsigned int>(indices.size());

			hresult = device->CreateBuffer(&vDesc, &vSub, buffer.mVertexBuffer.GetAddressOf());
			assert(hresult == S_OK);
			if (hresult != S_OK)
			{
				return false;
			}

			hresult = device->CreateBuffer(&iDesc, &iSub, buffer.mIndexBuffer.GetAddressOf());
			assert(hresult == S_OK);
			if (hresult != S_OK)
			{
				return false;
			}

			return true;
		}

}