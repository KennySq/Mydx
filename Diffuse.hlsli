#include"Lights.hlsli"
#include"Math.hlsli"

float Lambertian(float4 normal, DirectionalLight light)
{
    return dot(normal, light.mDirection) / PI;
}

float OrenNayar(float4 normal,float4 view, DirectionalLight light, float roughness)
{
    float roughSq = roughness * roughness;
    
    float a = 1.0 - (roughSq / (2.0 * (roughSq + 0.33)));
    float b = (0.45 * roughSq) / (roughSq + 0.09);
    
    
    
    float4 lightDir = light.mDirection;
    float4 reflected = reflect(normal, light.mDirection);
    
    float sinThetaIn = dot(-normal, light.mDirection);
    float sinThetaOut = dot(-reflected, view);
        
    float phi = pow(cos(lightDir.z), -1);
    float phir = pow(cos(reflected.z), -1);
    
    float theta = pow(tan(lightDir.y / lightDir.x), -1);
    float thetar = pow(tan(reflected.y / reflected.x), -1);
    
    float alpha = max(theta, thetar);
    float beta = min(theta, thetar);
    
    float radiance = cos(theta) * (a + b * max(0, cos(phi - phir)) * sin(alpha) * tan(beta));
    
    return radiance;
    
}