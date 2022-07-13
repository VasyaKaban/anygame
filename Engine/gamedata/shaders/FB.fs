#version 330 core

out vec4 color;
in vec2 TexCoord;

uniform sampler2D ScreenTexture;

void main()
{
	color = texture(ScreenTexture, TexCoord);
	float avg = color.g;
	color = vec4(avg, 0, 0, 1.0);
}