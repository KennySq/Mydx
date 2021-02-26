#include"Lights.hlsli"

cbuffer CameraBuffer : register(b0)
{
    matrix gView;
    matrix gProjection;
    
    float4 gViewForward;
    float4 gViewUp;
    float4 gViewRight;

    float4 gViewPosition;
}

cbuffer Instance : register(b1)
{
    matrix gWorld;
}
cbuffer LightBuffer : register(b2)
{
    DirectionalLight gDirectionalLights[80]; // 2,880 byte
}