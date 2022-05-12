#version 450

uniform vec2 u_res; // resolution
uniform float t; // time 

layout (location = 0) out vec4 outColor;
const float pi = 3.14159265;
const float e = 2.71828182; 


void main()
{
	vec2 uv = gl_FragCoord.xy / u_res - 0.5;
	vec2 cursor = vec2(cos(t), sin(t));
	vec2 warp = (cursor.xy - uv.xy) * distance(cursor.xy, uv.xy) * 512.0;
	warp.y = -warp.y;
	uv += warp;
	
	float light = abs(warp.x - warp.y);
	outColor = vec4(uv, sin(t), 1.0) * light/16.0;
}