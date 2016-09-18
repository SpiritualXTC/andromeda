// Uber Shader V0.1
// Vertex Shader
// Outputs a constant color

uniform vec4 u_color = vec4(1.0,1.0,1.0,1.0);

// Output
out vec4 o_color;

void main(void)
{
	// Set Output Color
	//o_color = vec4(1.0, 0.0, 1.0, 1.0);
	o_color = u_color;//vec4(RED, GREEN, BLUE, ALPHA);
}