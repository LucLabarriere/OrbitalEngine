#version 430 core

in vec4 v_Color;
in vec2 v_TexCoords;

out vec4 o_Color;

uniform sampler2D u_TexId;

vec3 getDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    // Normalization of the direction
    light.direction = normalize(-light.Direction);
    
}
  
void main()
{
    o_Color = v_Color * texture(u_TexId, v_TexCoords);
}
