
#version 430 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in vec2 a_TexCoords;

out vec3 v_FragmentPosition;  
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_VPMatrix;

void main()
{
	v_FragmentPosition = a_Position;
    v_Color = a_Color;
	v_Normal = a_Normal;
    v_TexCoords = a_TexCoords;

    gl_Position = u_VPMatrix * vec4(a_Position, 1.0);
}