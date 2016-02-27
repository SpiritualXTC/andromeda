#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec3 v_position[1];
in vec3 v_velocity[1];


void main()
{
	gl_Position = vec4(-0.5, 0.5, 0.0, 1.0);
	EmitVertex();
	
	gl_Position = vec4( 0.5, 0.5, 0.0, 1.0);
	EmitVertex();
		
	gl_Position = vec4(-0.5,-0.5, 0.0, 1.0);
	EmitVertex();
			
	gl_Position = vec4( 0.5,-0.5, 0.0, 1.0);
	EmitVertex();
}