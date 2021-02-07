#include "pch.h"
#include "Transform.h"

void Mydx::Transform::SetScale(float x, float y, float z)
{}

Mydx::Transform::Transform(XMVECTOR position, XMVECTOR rotation, XMVECTOR scale)
{
	mTransform = XMMatrixTransformation(scale, XMVectorZero(), XMVectorZero(), rotation, XMVectorZero(), position);

	XMStoreFloat4(&mPosition, position);
	XMStoreFloat4(&mRotation, rotation);
	XMStoreFloat4(&mScale, scale);
}

Mydx::Transform::Transform(const Transform& rhs)
{
	
}

Mydx::Transform::Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
{}

Mydx::Transform::~Transform()
{}
