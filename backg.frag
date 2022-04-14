#version 450

uniform vec2 u_res; // resolution
uniform float t; // time 

layout (location = 0) out vec4 outColor;
const float pi = 3.14159265;
const float e = 2.71828182; 

bool f(vec2 p)
{
	return pow(p.x, t) + pow(p.y, t) < pow(1/t, t);
}


void main()
{
	vec2 uv = gl_FragCoord.xy / u_res - 0.5;

	if (f(uv) || f(vec2(-uv.x, uv.y)) || f(vec2(uv.x, -uv.y)) || f(-uv))
		outColor = vec4(sin(t), cos(t), sin(t), 1.0); 
}