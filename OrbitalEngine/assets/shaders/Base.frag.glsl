// Fragment shader
#version 430 core

in vec4 v_Color;
in vec2 v_TexCoords;
out vec4 o_Color;
uniform sampler2D u_TexId;
  
void main()
{
    o_Color = texture(u_TexId, v_TexCoords) * v_Color;
}
