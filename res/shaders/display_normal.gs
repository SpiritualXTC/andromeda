// Uber Shader V0.1
// Geometry Shader
// Displays Normals



// Matrix Constants
uniform mat4 u_projection;		// Projection Matrix
uniform mat4 u_modelview;		// ModelView Matrix

uniform float u_length = 0.1;			// Line Length

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;



// Pass along the Pipeline
out gl_PerVertex 
{
    vec4 gl_Position;
};
	
in vec4 o_position[3];
	

void main(void)
{
	// Get Position
	vec3 v0 = o_position[0].xyz;
	vec3 v1 = o_position[1].xyz;
	vec3 v2 = o_position[2].xyz;
	
	// Calculate Normal :: Dependancy
	vec3 normal = calcNormal(v0, v1, v2);

	// Calc Center of Face
	vec3 p0 = (v0 + v1 + v2) / 3.0;
	vec3 p1 = p0 + normalize(normal) * u_length;

	// Emit Vertex A
	gl_Position = u_projection * u_modelview * vec4(p0, 1);
	EmitVertex();

	// Emit Vertex B
	gl_Position = u_projection * u_modelview * vec4(p1, 1);
	EmitVertex();

	EndPrimitive();
}