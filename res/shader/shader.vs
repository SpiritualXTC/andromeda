#version 400

// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!

uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix


layout(location=0) in vec4 a_position;


void main()
{
	// Setup Varying Interpolation
	
	

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
	//gl_Position = a_position;	
}