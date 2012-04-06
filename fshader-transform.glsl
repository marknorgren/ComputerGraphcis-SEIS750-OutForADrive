#version 150
in vec4 color;
in vec4 ambient;
in vec3 normal;

out vec4  fColor;

uniform vec3 AmbientProduct, DiffiuseProduct, SpecularProduct;
uniform mat4 model_view;
uniform mat4 projection;
uniform vec4 light_position;
uniform vec4 light_color;
uniform vec4 ambient_light;

uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ka;            // Ambient reflectivity
uniform vec3 Ks;            // Specular reflectivity
uniform float Shininess;    // Specular shininess factor

void main()
{
    //fColor = color;
	// test for normal values
	// same normal values should have same color value
	//fColor = vec4(normal, 1.0);//color * ambient;
	fColor = color * ambient;
}