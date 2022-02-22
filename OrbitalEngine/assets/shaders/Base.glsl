// Vertex shader
#version 430 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;
  
out vec4 v_Color;
out vec2 v_TexCoords;

uniform mat4 u_VPMatrix;

void main()
{
    gl_Position = u_VPMatrix * vec4(a_Position, 1.0);
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
}

// Fragment shader
#version 430 core

in vec4 v_Color;
in vec2 v_TexCoords;

out vec4 o_Color;

uniform sampler2D u_TexId;
  
void main()
{
    o_Color = texture(u_TexId, v_TexCoords);
}
