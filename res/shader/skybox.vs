// Skybox Shader V0.1
// Used for rendering the Skybox :)

// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix
uniform mat4 u_normalMatrix;	// Normal Matrix


// Vertex Data
layout(location=0) in vec4 a_position;

// Pass along the Pipeline
out vec3 v_position;
out vec3 v_cubeTexture;


// Entry Point
void main()
{
	// Texture Coordinates - Including Inversions
	v_cubeTexture = vec3(a_position);
	v_position = vec3(a_position);

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}