#version 430 core

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoords;

out vec4 o_Color;

struct DirectionalLight
{
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct LightResult
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

uniform sampler2D u_TexId;
uniform DirectionalLight u_DirectionalLight;
uniform vec3 u_ViewPosition;

LightResult CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
	LightResult result;

    // Normalization of the direction
    light.Direction = normalize(- light.Direction);
	
	// Ambient
	result.Ambient = light.Ambient; // Add material response here
	// Diffuse
	result.Diffuse = light.Diffuse * max(dot(normal, light.Direction), 0.0); // Add material response here;
	// Specular
	vec3 reflectionDirection = reflect(- light.Direction, normal);
	result.Specular
		= light.Specular
		* pow(max(dot(viewDirection, reflectionDirection), 0.0), 2.0); // Replace 2.0 by the material shininess here
		// Multiply by the material response here

    return result;
}
  
void main()
{
	vec3 viewDirection = normalize(u_ViewPosition - v_FragmentPosition);
	LightResult result = CalculateDirectionalLight(u_DirectionalLight, v_Normal, viewDirection);

    o_Color
		= vec4(result.Ambient + result.Diffuse + result.Specular, 1.0)
		* v_Color
		* texture(u_TexId, v_TexCoords); // Remove this, it should be defined in the material
}