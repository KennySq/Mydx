#include"Lights.hlsli"
// Reference
// https://en.wikipedia.org/wiki/Schlick%27s_approximation
float FresnelDieelectric(float4 normal, float4 view, DirectionalLight light, float factor)
{
    float4 refracted = refract(normal, light.mDirection, factor);
    float4 lightDir = light.mDirection;
    float rfrcTrans = factor;
    float rfrcInci = 1.0f;
    
    float4 halfV = (lightDir + view) / normalize(lightDir + view);
    
    float ndl = dot(normal, light.mDirection);
    float ndr = dot(view, refracted);

    float tndl = rfrcTrans * ndl;                                                                                                                                   
    float indl = rfrcInci * ndl;
    
    float tndr = rfrcTrans * ndr;
    float indr = rfrcInci * ndr;
    
    float perpnum = tndl - indr;
    float perpdom = tndl + indr;
    
    float parlnum = indl - tndr;
    float parldom = indl + tndr;
    
    float perp = perpnum / perpdom;
    float parl = parlnum / parldom;
    
    float fr = ((perp * perp) + (parl * parl)) * 0.5f;
    
    return fr;
}