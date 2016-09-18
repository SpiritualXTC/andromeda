// Deferred Shader
// Renders Geometry to a Series of RenderBuffers


uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_view;			// View Matrix
uniform mat4 u_model;			// Model Matrix

uniform mat4 u_modelview;		// ModelView Matrix
uniform mat3 u_normalMatrix;


// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

// Varying
out vec3 v_position;
out vec3 v_normal;
out vec2 v_diffuseTextureCoord;

// Varying for Refelections
//out vec3 v_eyePosition;
//out vec3 v_eyeNormal;


void main( void )
{
	// Setup Varyings
	v_position				= vec3(u_model * a_position);
	v_normal				= u_normalMatrix * a_normal;
	
	
	v_diffuseTextureCoord	= a_texture;



	// Environment Mapping Variables
	// TODO:: Optimize (v_eyePosition = v_position)
	//	   :: Normals will need to use the "normal matrix"
//	v_eyePosition = vec3 (u_modelview * a_position);
//	v_eyeNormal = u_normalMatrix * a_normal;


	// Calculate Position
	gl_Position = u_projection * u_view * u_model * a_position;	
}
