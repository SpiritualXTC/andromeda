// Deferred Shader
// Renders Shadows


uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix


// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=2) in vec2 a_texture;	// Masking

// Varying
out vec2 v_diffuseTextureCoord;



void main( void )
{
	// Diffuse :: Used for Masking
	v_diffuseTextureCoord	= a_texture;

	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}