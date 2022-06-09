#version 120

uniform vec2 res;
uniform sampler2D uTexture;

void main()
{
	vec2 uv = gl_FragCoord.xy/res;
	vec4 pixel = texture2D(uTexture, uv);
	gl_FragColor = pixel;
}