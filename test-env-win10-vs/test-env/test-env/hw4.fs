#version 330 core

in vec3 FragPos;
out vec4 FragColor;


uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objectCol;


void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	vec3 e = vec3(0,0,1);
	vec3 norm = normalize(e);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightCol;
	vec3 result = diffuse * objectCol;
	FragColor = vec4(result,1.0);
}