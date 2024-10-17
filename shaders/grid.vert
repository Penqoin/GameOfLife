#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

uniform vec3 PosCamera;
uniform float time;

out vec2 TexCoord;
out vec2 WorldPos;

uniform float gGridSize = 100.f;

const vec2 Pos[4] = vec2[4](
    vec2(-1.f, -1.f),
    vec2(1.f, -1.f),
    vec2(1.f, 1.f),
    vec2(-1.f, 1.f)
);

const int Indices[6] = int[6](1, 0, 3, 2, 0, 3);

void main()
{
    int Index = Indices[gl_VertexID];

    vec2 vPos = vec2(Pos[Index]) * gGridSize;

    vPos += PosCamera.xy;

    gl_Position = proj * model * view * vec4(vPos, 0.f, 1.f);
    TexCoord = aTexCoord;
    WorldPos = vPos;
}
