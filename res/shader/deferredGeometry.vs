// Deferred Shader
// Renders Geometry to a Series of RenderBuffers


uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix



// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

// Varying
out vec3 v_position;
out vec3 v_normal;
out vec2 v_diffuseTextureCoord;

// Varying for Refelections
out vec3 v_eyePosition;
out vec3 v_eyeNormal;


void main( void )
{

	// Option for the Normal Matrix ???
	//mat3 worldRotationInverse = transpose(mat3(WorldMatrix));
	//normals			= normalize(worldRotationInverse * gl_NormalMatrix * gl_Normal);



	// Setup Varyings
	v_position				= vec3(u_modelview * a_position);
	v_normal				= a_normal;					// Niave normals. This doesn't account for any matrix transformations on the model. INCORRECT!!!
	v_diffuseTextureCoord	= a_texture;



	// Environment Mapping Variables
	// TODO:: Optimize (v_eyePosition = v_position)
	//	   :: Normals will need to use the "normal matrix"
	v_eyePosition = vec3 (u_modelview * a_position);
	v_eyeNormal = vec3 (mat3(u_modelview) * a_normal);


	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}
