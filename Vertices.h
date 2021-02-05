#pragma once
#include<DirectXMath.h>

using namespace DirectX;

enum eVertexType
{
	STATIC,
	WEIGHTED,
	MINIMUM,
};

struct StaticVertex
{
	XMFLOAT4 mPosition;
	XMFLOAT3 mNormal;
	XMFLOAT2 mTexcoord;

	StaticVertex() {}

	StaticVertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v)
		: mPosition(px, py, pz, 1.0f), mNormal(nx, ny, nz), mTexcoord(u, v) {}

	StaticVertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 uv)
		: mPosition(position.x, position.y, position.z, 1.0f), mNormal(normal), mTexcoord(uv) {}
};

struct WeightVertex
{

};

struct MinimumVertex
{
	XMFLOAT4 mPosition;
	XMFLOAT2 mTexcoord;
};