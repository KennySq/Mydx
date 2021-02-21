#include"pch.h"
#include"MeshLoader.h"
#include"Mesh.h"


using namespace std;

namespace Mydx
{
	HRESULT MeshLoader::loadStaticModelFromFile(const char* path)
	{
		Mesh mesh = Mesh(eMeshType::FILE, eVertexType::STATIC);

		vector<XMFLOAT4> Positions;
		vector<XMFLOAT2> UVs;
		vector<XMFLOAT3> Normals;

		vector<unsigned int> PositionIndices, UVIndices, NormalIndices;



		std::FILE* file = fopen(path, "r");
		//fstream file = fstream(Path.c_str());

		auto e = feof(file);
		int res = 0;
		while (res != EOF)
		{
			char Header[128];
			res = fscanf(file, "%s", Header);

			if (strcmp(Header, "v") == 0)
			{
				XMFLOAT4 Position;
				fscanf(file, "%f %f %f\n", &Position.x, &Position.y, &Position.z);



				Positions.emplace_back(Position);
			}
			else if (strcmp(Header, "vt") == 0)
			{
				XMFLOAT2 UV;
				fscanf(file, "%f %f\n", &UV.x, &UV.y);
				UVs.emplace_back(UV);
			}
			else if (strcmp(Header, "vn") == 0)
			{
				XMFLOAT3 Normal;
				fscanf(file, "%f %f %f\n", &Normal.x, &Normal.y, &Normal.z);
				Normals.emplace_back(Normal);
			}
			else if (strcmp(Header, "f") == 0)
			{
				string V1, V2, V3;
				unsigned int VertexIndex[3], UVIndex[3], NormalIndex[3];

				int Matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
									 &VertexIndex[0], &UVIndex[0], &NormalIndex[0],
									 &VertexIndex[1], &UVIndex[1], &NormalIndex[1],
									 &VertexIndex[2], &UVIndex[2], &NormalIndex[2]);

				if (Matches == -1)
					break;

				if (Matches != 9)
				{
					return E_FAIL;
				}

				PositionIndices.emplace_back(VertexIndex[0]);
				PositionIndices.emplace_back(VertexIndex[1]);
				PositionIndices.emplace_back(VertexIndex[2]);

				UVIndices.emplace_back(UVIndex[0]);
				UVIndices.emplace_back(UVIndex[1]);
				UVIndices.emplace_back(UVIndex[2]);

				NormalIndices.emplace_back(NormalIndex[0]);
				NormalIndices.emplace_back(NormalIndex[1]);
				NormalIndices.emplace_back(NormalIndex[2]);
			}



		}

		for (unsigned int i = 0; i < PositionIndices.size(); i++)
		{
			StaticVertex Vertex;

			unsigned int PositionIndex = PositionIndices[i];
			unsigned int UVIndex = UVIndices[i];
			unsigned int NormalIndex = NormalIndices[i];

			XMFLOAT4 Position = Positions[PositionIndex - 1];
			XMFLOAT2 UV = UVs[UVIndex - 1];
			XMFLOAT3 Normal = Normals[NormalIndex - 1];

			Vertex.mPosition = Position;
			Vertex.mTexcoord = UV;
			Vertex.mNormal = Normal;

			mVertices.emplace_back(Vertex);
		}

		for (unsigned int i = 0; i < mVertices.size(); i++)
			mIndices.emplace_back(i);

		clearerr(file);

		createStaticMeshBuffer();

		mVertices.clear();
		mIndices.clear();

		return S_OK;
	}

	HRESULT MeshLoader::createStaticMeshBuffer()
	{
		auto Device = HW::GetDevice();

		HRESULT Result;
		D3D11_BUFFER_DESC Desc{};
		D3D11_SUBRESOURCE_DATA Sub{};

		Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		Desc.ByteWidth = sizeof(StaticVertex) * mVertices.size();
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Sub.pSysMem = mVertices.data();

		Result = Device->CreateBuffer(&Desc, &Sub, mMesh->mVertexBuffer.GetAddressOf());

		Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		Desc.ByteWidth = sizeof(unsigned int) * mIndices.size();
		Desc.Usage = D3D11_USAGE_DEFAULT;
		Sub.pSysMem = mIndices.data();

		Result = Device->CreateBuffer(&Desc, &Sub, mMesh->mIndexBuffer.GetAddressOf());

		return Result;
	}

	MeshLoader::MeshLoader(const char* path)
	{
		mMesh = new Mesh(FILE, STATIC);

		loadStaticModelFromFile(path);
	}

	MeshLoader::~MeshLoader()
	{}


}