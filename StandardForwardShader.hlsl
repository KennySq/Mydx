#include"Diffuse.hlsli"
#include"Reflection.hlsli"

SamplerState defaultSampler : register(s0);
SamplerState cubemapSampler : register(s1);

TextureCube<float4> sampleCubemap : register(t0);


struct VertexInput
{
    float4 mPosition : POSITION0;
    float3 mNormal : NORMAL0;
    float2 mTexcoord : TEXCOORD0;
};

struct PixelInput
{
    float4 mPosition : SV_Position;
    float4 mLocalPosition : POSITION0;
    float4 mNormal : TEXCOORD0;
    float2 mTexcoord : TEXCOORD1;
};

PixelInput SampleVS(VertexInput input)
{
    PixelInput output = (PixelInput) 0;
    
    input.mPosition.w = 1.0f;
    
    
    float4 world = mul(input.mPosition, gWorld);
    float4 view = mul(world, gView);
    float4 projection = mul(view, gProjection);
    
    
    float4 normal = float4(mul(input.mNormal, (float3x3) gWorld), 1.0f);
    
    float2 uv = input.mTexcoord;
    
    output.mPosition = projection;
    output.mNormal = normal;
    output.mTexcoord = uv;
    output.mLocalPosition = input.mPosition;
    
    return output;
}

float4 SamplePS(PixelInput input) : SV_Target0
{
    float4 position = input.mPosition;
    float4 worldNormal = input.mNormal;
    float4 normal = input.mNormal;
    float2 uv = input.mTexcoord;
    float viewDir = normalize(gViewForward);
    
    normal = normalize(normal);
    
    float fr = FresnelDieelectric(normal, viewDir, gDirectionalLights[0], 1.5f);
    
    float4 reflected = reflect(-normal, normalize(gDirectionalLights[0].mDirection));
    normal = normalize(normal);
    float diffuse = dot(normal, normalize(gDirectionalLights[0].mDirection));
    
    float4 cube = sampleCubemap.Sample(defaultSampler, input.mLocalPosition.xyz);
    
    return dot(viewDir, reflected);

}