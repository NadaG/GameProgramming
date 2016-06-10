
sampler2D shaderTexture;

struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	//float4 albedo = tex2D(shaderTexture, input.mTexCoord);
	float4 albedo = { 1.0f, 1.0f, 1.0f, 1.0f };
	return albedo.rgba;
}