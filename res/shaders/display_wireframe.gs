// Uber Shader V0.1
// Geometry Shader
// Displays Wireframe



// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix


layout(triangles) in;
layout(line_strip, max_vertices = 4) out;



// Pass along the Pipeline
out gl_PerVertex 
{
    vec4 gl_Position;
};
	
in vec4 o_position[3];
	

void main(void)
{
	vec3 v0 = o_position[0].xyz;
	vec3 v1 = o_position[1].xyz;
	vec3 v2 = o_position[2].xyz;
	
	// Emit Vertex A
	gl_Position = u_projection * u_modelview * vec4(v0, 1);
	EmitVertex();

	// Emit Vertex B
	gl_Position = u_projection * u_modelview * vec4(v1, 1);
	EmitVertex();

	// Emit Vertex C
	gl_Position = u_projection * u_modelview * vec4(v2, 1);
	EmitVertex();

	// Emit Vertex A [Loop]
	gl_Position = u_projection * u_modelview * vec4(v0, 1);
	EmitVertex();

	EndPrimitive();
}