#version 400

// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!

uniform sampler2D u_texture;
uniform vec4 u_color;


varying vec2 v_texture;



out vec4 o_color;

void main()
{
	//gl_FragColor = u_color;
	
	vec4 c = texture2D(u_texture, v_texture);
	
	
	o_color = c * vec4(1.0, 1.0, 1.0, 1.0);
	
	//gl_FragColor = c * vec4(1.0, 1.0, 1.0, 1.0);
}