#include"Lights.hlsli"
// Reference
// https://en.wikipedia.org/wiki/Schlick%27s_approximation
float FresnelDieelectric(float4 normal, float4 view, DirectionalLight light, float factor)
{
    float r;
    float n1 = 1;
    float n2 = factor;
	
    float cosTheta = dot(-normal, view);
    float omCosTheta = 1 - cosTheta;
	
    float r0sqrt = (n1 - n2) / (n1 + n2);
    float r0 = r0sqrt * r0sqrt;
	
    float omR0 = 1 - r0;
	
    float final = r0 + omR0 * pow(omCosTheta, 5);
	
    return final;
}