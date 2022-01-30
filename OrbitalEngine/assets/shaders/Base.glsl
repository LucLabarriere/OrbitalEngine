// Vertex shader
#version 430 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
  
out vec4 v_Color;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_Color = a_Color;
}


// Fragment shader
#version 430 core

in vec4 v_Color;
out vec4 o_Color;
  
void main()
{
    o_Color = v_Color;
} 