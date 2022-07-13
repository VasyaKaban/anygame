#version 330 core

out vec4 color;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform bool isPicked;

void main()
{
	//color = texture(ourTexture, TexCoord);
	//if(isPicked == true)
	//{
	//	color = vec4(0.5, 0.0, 0.0, 1.0);
	//}
	//else
	//{
		color = vec4(Normal, 1.0);
		//color = texture(ourTexture, TexCoord);
	//}
};