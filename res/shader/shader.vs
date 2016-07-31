// Uber Shader V0.1
// Used for rendering all game objects :)

// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix
uniform mat4 u_normalMatrix;	// Normal Matrix


// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

// Pass along the Pipeline
out vec3 v_position;
out vec2 v_diffuseTextureCoord;
out vec3 v_normal;

// Entry Point
void main()
{
	// Texture Coordinates - Including Inversions
	v_diffuseTextureCoord = vec2(a_texture.x, a_texture.y);
	
	// Normals
	// TODO: This needs the normal matrix as well
	v_normal = a_normal; //* u_normalMatrix;
	v_position = vec3(u_modelview * a_position);

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}