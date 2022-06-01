#version 120
uniform vec2 res;
uniform sampler2D uTexture;

void main()
{
	vec2 uv = gl_FragCoord.xy/res;
	uv.x -= 0.5; // i dont know why it is so
	uv.y -= 0.5; // too
	vec4 pixel = texture2D(uTexture, uv);
	gl_FragColor = pixel;
}