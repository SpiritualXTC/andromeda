// Uber Shader V0.1
// Used for rendering all game objects :)

// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix






// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=2) in vec2 a_texture;

// Varying
out vec2 v_bezier;



// Entry Point
void main()
{
	v_bezier = a_texture;

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}

