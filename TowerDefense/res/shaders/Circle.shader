#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 fragCoord;

out vec2 v_Coord;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_Coord = fragCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_Coord;

uniform vec4 u_Color;
uniform float u_Thickness;

void main()
{
	vec2 offset = vec2(0.5, 0.5);
	float distance = length(v_Coord - offset);
	if (distance > 0.5f || distance < 0.5f - u_Thickness)
		discard;
	color = u_Color;
};