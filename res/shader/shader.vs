#version 400

// Uber Shader V0.1
// Used for rendering all game objects :)

#define MAX_LIGHT 8


// Data Structures
struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} MATERIAL;


struct Light
{
	vec4 position;
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
} LIGHT;



// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix

// Material
uniform Material u_material;

// Lighting
uniform Light u_lights[MAX_LIGHT];
uniform int u_lightCount;


// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

// Pass along the Pipeline
out vec2 v_texture;
out vec3 v_normal;

// Entry Point
void main()
{
	// Setup Varying Interpolation
	v_texture = a_texture;
	

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
	//gl_Position = a_position;	
}