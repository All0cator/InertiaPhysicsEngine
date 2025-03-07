#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
	vec3 projectedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // perspective division
	projectedCoords = projectedCoords * 0.5f + 0.5f; // ndc

	float closestDepth;

	float currentDepth = projectedCoords.z;

	float shadow = 0.0f;

	float bias = max(0.05f * (1.0f - dot(normal, lightDir)), 0.005f);

	vec2 texelSize = 1.0f / textureSize(shadowMap, 0);

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			closestDepth = texture(shadowMap, projectedCoords.xy + vec2(x, y) * texelSize).r;

			if (currentDepth - bias > closestDepth)
				shadow += 1.0f;
		}
	}

	shadow /= 9.0f;

	if (projectedCoords.z > 1.0f)
		shadow = 0.0f;

	return shadow;
}

in VS_OUT
{
	vec3 fragNormal;
	vec3 fragPos;
	vec4 fragPosLightSpace;
} fs_in;

out vec4 fragOut;

uniform Material material;
uniform DirectionalLight light;

uniform vec3 viewPos; // world space

void main()
{
	// assuming directional light
	vec3 result = vec3(1.0f);
	vec3 lightContribution = vec3(0.0f);

	vec3 normal = fs_in.fragNormal;
	vec3 viewDir = normalize(viewPos - fs_in.fragPos);

	float shadow = ShadowCalculation(fs_in.fragPosLightSpace, normal, -light.direction);

	// Phong Shading 
	float diffuseStrength = max(dot(normal, -light.direction), 0.0f);

	vec3 reflectDir = reflect(-light.direction, normal);
	vec3 halfWay = normalize(reflectDir + normal);
	float specularStrength = pow(max(dot(halfWay, viewDir), 0.0f), material.shininess);

	vec3 ambient = material.ambient * light.ambient;
	vec3 diffuse = material.diffuse * light.diffuse * diffuseStrength;
	vec3 specular = material.specular * light.specular * specularStrength;

	lightContribution = ambient + (1.0f - shadow) * (diffuse + specular);

	result *= lightContribution;

	fragOut = vec4(result, 1.0f);
}