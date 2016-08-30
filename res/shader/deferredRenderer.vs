// Deferred Shader : Light Shader
//



uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_view;			// View Matrix
uniform mat4 u_model;			// Model Matrix

//uniform mat4 u_modelview;		// ModelView Matrix





layout(location=0) in vec4 a_position;
layout(location=2) in vec2 a_texture;

out vec2 v_textureCoordinate; 

void main( void )
{
	v_textureCoordinate = a_texture;

	// Calculate Position
	gl_Position = u_projection * u_view * u_model * a_position;	
}