#version 330 core

out vec4 color;

uniform vec3 RGBid;

void main()
{
	color = vec4(RGBid, 1.0);
};