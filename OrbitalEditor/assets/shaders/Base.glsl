// Vertex shader
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
uniform mat4 u_MMatrix;
uniform vec2 u_TexCoordsMultiplicator;

void main()
{
    v_Color = a_Color;
    v_Normal = normalize(mat3(transpose(inverse(u_MMatrix))) * a_Normal);
    v_TexCoords = u_TexCoordsMultiplicator * a_TexCoords;

    gl_Position = u_MMatrix * vec4(a_Position, 1.0);
    v_FragmentPosition = vec3(gl_Position);
    gl_Position = u_VPMatrix * gl_Position;
}

// Fragment shader
#version 430 core

#define N_SPOT_LIGHTS 20
#define N_POINT_LIGHTS 30
#define N_DIR_LIGHTS 10

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

struct PointLight
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    
    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight
{
    vec3 Position;
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
  
    float Constant;
    float Linear;
    float Quadratic;
    float CutOff;
    float OuterCutOff;
};

struct LightResult
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct Material
{
	float Ambient;
	sampler2D DiffuseMap;
	vec3 DiffuseTint;
	sampler2D SpecularMap;
	vec3 SpecularTint;
	float Shininess;
};

uniform vec3 u_ViewPosition;
uniform DirectionalLight u_DirectionalLights[N_DIR_LIGHTS];
uniform PointLight u_PointLights[N_POINT_LIGHTS];
uniform SpotLight u_SpotLights[N_SPOT_LIGHTS];
uniform int u_nDirectionalLights;
uniform int u_nPointLights;
uniform int u_nSpotLights;
uniform Material u_Material;

LightResult CalculateDirectionalLight(DirectionalLight light, vec3 viewDirection)
{
	LightResult result;
	
	// Ambient
	result.Ambient 
		= light.Ambient
		* u_Material.Ambient
		* u_Material.DiffuseTint
		* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

	// Diffuse
	result.Diffuse 
		= light.Diffuse 
		* u_Material.DiffuseTint
		* max(dot(v_Normal, -light.Direction), 0.0)
		* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

	// Specular
	vec3 reflectionDirection = reflect(light.Direction, v_Normal);
	result.Specular
		= light.Specular
		* u_Material.SpecularTint
		* pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Material.Shininess)
		* vec3(texture(u_Material.SpecularMap, v_TexCoords));

    return result;
}

LightResult CalculatePointLight(PointLight light, vec3 viewDirection)
{
	LightResult result;
	vec3 directionNonNormalized = light.Position - v_FragmentPosition;
    vec3 direction = normalize(directionNonNormalized);

	// Ambient
	// result.Ambient
	// 	= light.Ambient
	// 	* u_Material.DiffuseTint
	// 	* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

    // Diffuse
    result.Diffuse
		= light.Diffuse
		* u_Material.DiffuseTint
		* max(dot(v_Normal, direction), 0.0)
		* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

    // Specular
	vec3 reflectionDirection = reflect(- direction, v_Normal);
	result.Specular
		= light.Specular
		* u_Material.SpecularTint
		* pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Material.Shininess)
		* vec3(texture(u_Material.SpecularMap, v_TexCoords));

    // Attenuation
    float dist = length(directionNonNormalized);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * dist * dist);    
    // combine results
    // result.Ambient *= attenuation;
    result.Diffuse *= attenuation;
    result.Specular *= attenuation;

    return result;
}

LightResult CalculateSpotLight(SpotLight light, vec3 viewDirection)
{
	LightResult result;
	vec3 directionNonNormalized = light.Position - v_FragmentPosition;
    vec3 direction = normalize(directionNonNormalized);

	// Ambient
	// result.Ambient
	// 	= light.Ambient
	// 	* u_Material.DiffuseTint
	// 	* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

    // Diffuse
    result.Diffuse
		= light.Diffuse
		* u_Material.DiffuseTint
		* max(dot(v_Normal, direction), 0.0)
		* vec3(texture(u_Material.DiffuseMap, v_TexCoords));

    // Specular
	vec3 reflectionDirection = reflect(- direction, v_Normal);
	result.Specular
		= light.Specular
		* u_Material.SpecularTint
		* pow(max(dot(viewDirection, reflectionDirection), 0.0), u_Material.Shininess)
		* vec3(texture(u_Material.SpecularMap, v_TexCoords));

    // Attenuation
    float dist = length(directionNonNormalized);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * dist * dist);    

	// Intensity
    float theta = dot(direction, normalize(- light.Direction));
    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    // combine results
    result.Ambient *= attenuation;
    result.Diffuse *= attenuation * intensity;
    result.Specular *= attenuation * intensity;

    return result;
}
  
void main()
{
	vec3 viewDirection = normalize(u_ViewPosition - v_FragmentPosition);
	LightResult result = { vec3(0.0), vec3(0.0), vec3(0.0) };

    for(int i = 0; i < u_nDirectionalLights; i++)
	{
		LightResult tempResult = CalculateDirectionalLight(u_DirectionalLights[i], viewDirection);
        result.Ambient += tempResult.Ambient;
		result.Diffuse += tempResult.Diffuse;
		result.Specular += tempResult.Specular;
	}

    for(int i = 0; i < u_nPointLights; i++)
	{
		LightResult tempResult = CalculatePointLight(u_PointLights[i], viewDirection);
        result.Ambient += tempResult.Ambient;
		result.Diffuse += tempResult.Diffuse;
		result.Specular += tempResult.Specular;
	}

    for(int i = 0; i < u_nSpotLights; i++)
	{
		LightResult tempResult = CalculateSpotLight(u_SpotLights[i], viewDirection);
        result.Ambient += tempResult.Ambient;
		result.Diffuse += tempResult.Diffuse;
		result.Specular += tempResult.Specular;
	}

    o_Color = vec4(result.Ambient + result.Diffuse + result.Specular, 1.0);
}
