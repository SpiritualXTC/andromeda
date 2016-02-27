#version 400

// Uber Shader V0.1
// Used for rendering all game objects :)

uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix


layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

varying vec2 v_texture;

void main()
{
	// Setup Varying Interpolation
	v_texture = a_texture;
	

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
	//gl_Position = a_position;	
}