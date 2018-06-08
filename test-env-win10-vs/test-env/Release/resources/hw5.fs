#version 330 core
out vec4 FragColor;

// in vec2 TexCoords;
in vec3 normal;
in vec3 FragPos;

// uniform sampler2D texture_diffuse1;

uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objectCol;


void main()
{
    float add = 0.7;
	vec3 e = normal;
	vec3 norm = normalize(e);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff + add) * lightCol;
	vec3 result = diffuse * objectCol;
	FragColor = vec4(result,1.0);
}