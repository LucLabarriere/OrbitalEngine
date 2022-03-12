// Vertex shader
#version 430 core
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

void main()
{
    gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0); 
    v_TexCoords = a_TexCoords;
}

// Fragment shader
#version 430 core
out vec4 o_Color;
  
in vec2 v_TexCoords;

uniform sampler2D u_ScreenTexture;

void main()
{ 
    o_Color = texture(u_ScreenTexture, v_TexCoords);
}