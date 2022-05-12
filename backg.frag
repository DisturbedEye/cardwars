#version 450

uniform vec2 u_res; // resolution
uniform float t; // time 

layout (location = 0) out vec4 outColor;


void main()
{
	vec2 uv = gl_FragCoord.xy / u_res;
	outColor = vec4(uv.x, cos(t*t*length(uv - 0.5)), sin(t*t*length(uv - 0.5)), 1.0);
}