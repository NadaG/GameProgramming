
sampler2D shaderTexture;

struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 albedo = tex2D(shaderTexture, input.mTexCoord);
	return albedo.rgba;
}