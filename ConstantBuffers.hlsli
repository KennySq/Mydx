#include"Lights.hlsli"

cbuffer CameraBuffer : register(b0)
{
    row_major matrix gView;
    row_major matrix gProjection;
}

cbuffer Instance : register(b1)
{
    matrix gWorld;
}

cbuffer LightBuffer : register(b2)
{
    DirectionalLight gDirectionalLights[80]; // 2,880 byte
}