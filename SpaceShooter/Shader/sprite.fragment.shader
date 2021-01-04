#version 330 core

in vec2 v_TexCoord;

out vec4 color;

uniform vec4 v_Color;
uniform sampler2D tex;

void main()
{
	color = texture(tex, v_TexCoord) * v_Color;
	if (color.w < 1)
		discard;
};