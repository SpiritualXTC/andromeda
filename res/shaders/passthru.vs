// Uber Shader V0.1
// Vertex Shader
// Passthrough

// The Passthrough vertex shader DOES NOT transform the position by any Matrices.
// Suitable for Geometry Shader Computations


// Vertex Data
layout(location=0) in vec4 a_position;

out vec4 o_position;

// Entry Point
void main()
{
	// Calculate Position
	o_position = a_position;	
}