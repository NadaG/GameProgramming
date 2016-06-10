
/////////////////////////////////////
//// Red Shader /////////////////////
/////////////////////////////////////

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraBuffer
{
	float3 cameraPosition;
	float padding;
};

struct VS_INPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mTexCoord : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input : POSITION ) : SV_POSITION
{
	VS_OUTPUT output;

	output.mPosition = mul(input.mPosition, worldMatrix);
	output.mPosition = mul(output.mPosition, viewMatrix);
	output.mPosition = mul(output.mPosition, projectionMatrix);

	output.mTexCoord = input.mTexCoord;

	return output;
}