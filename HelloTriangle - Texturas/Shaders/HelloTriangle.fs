#version 400

out vec4 color;
in vec3 vertexColor;
in vec2 texcoord;

uniform sampler2D texBuffer;

void main()
{
	color = texture(texBuffer, texcoord);//vec4(vertexColor, 1.0);
}