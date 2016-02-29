#version 400

// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!


// Color
uniform vec4 u_color;
//uniform Material u_material;

// Texture
uniform sampler2D u_texture;



// Passed Along the Pipe
in vec2 v_texture;
in vec3 v_normal;

// Output
out vec4 o_color;


// Entry Point
void main()
{
	// Get Texture Color
	vec4 texColor = texture2D(u_texture, v_texture);
	
	
	// Set Output Color
	o_color = texColor * vec4(1.0, 1.0, 1.0, 1.0);
}