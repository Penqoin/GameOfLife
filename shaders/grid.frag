#version 330 core
out vec4 FragColor;

uniform vec4 color;
uniform vec3 PosCamera;
uniform float time;

uniform sampler2D text;
in vec2 TexCoord;

in vec2 WorldPos;

uniform float gGridCellSize = 0.04f;
uniform vec4 gGridColorThin = vec4(0.5, 0.5, 0.5, 1.f);
uniform vec4 gGridColorThick = vec4(0.f, 0.f, 0.f, 1.f);
uniform float gGridMinPixelsBetweenCells = 2.f;

float max2(vec2 v)
{
    return max(v.x, v.y);
}
vec2 saturate(vec2 v) 
{
    return clamp(v, 0.0, 1.0);
}

float log10(float x)
{
    return log(x) / log(10.f);
}

void main()
{
    vec2 dvx = vec2(dFdx(WorldPos.x), dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdy(WorldPos.y), dFdy(WorldPos.y));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);
    
    float l = length(dudv);
    float LOD = max(0.f, log10(l * gGridMinPixelsBetweenCells / gGridCellSize) + 1.f);
    float GridCellSizeLod0 = gGridCellSize * pow(10.f, floor(LOD));

    dudv *= 4.0f;

    vec2 mod_div =  mod(WorldPos.xy, GridCellSizeLod0) / dudv;
    float Lod0a = max2(vec2(1.f) - abs(saturate(mod_div) * 2.f - vec2(1.f)));
    vec4 Color;
    
    Color = gGridColorThick;
    Color.a *= Lod0a;

    FragColor = Color;
} 
