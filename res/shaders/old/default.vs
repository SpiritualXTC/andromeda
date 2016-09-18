// Vertex Data
layout(location=0) in vec4 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec2 a_texture;

// Pass along the Pipeline
out gl_PerVertex 
{
    vec4 gl_Position;
};
	
out vec2 v_diffuseTextureCoord;
out vec3 v_normal;

// Entry Point
void main()
{
	// Setup Varying Interpolation
	v_diffuseTextureCoord = vec2(a_texture.x, 1.0 - a_texture.y);
		
	// Calculate Position
	gl_Position = u_projection * u_modelview * a_position;	
}
