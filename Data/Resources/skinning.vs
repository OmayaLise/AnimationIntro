
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	mat4 mvp = sm.projectionMatrix * modelViewMatrix;
	mat4 boneModel = float(boneWeights[0]) * skin.mat[int(boneIndices[0])] + float(boneWeights[1]) * skin.mat[int(boneIndices[1])] + float(boneWeights[2]) * skin.mat[int(boneIndices[2])] + float(boneWeights[3]) * skin.mat[int(boneIndices[3])];

	vec4 pos = boneModel * vec4(inputPosition, 1.0);
	gl_Position = mvp * pos;

	vec3 localNormal = mat3(boneModel) * normal; 
	outNormal = mat3(mvp) * localNormal;
}
