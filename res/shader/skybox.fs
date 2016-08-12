// Skybox Shader V0.1
// Used for rendering the Skybox :)


uniform samplerCube g_diffuseTexture;
//uniform sampler2D g_diffuseTexture;

// Pass along the Pipeline
in vec3 v_position;
in vec3 v_cubeTexture;

// Output
out vec4 o_color;

// Entry Point
void main()
{
	// Sample Cube
	vec4 skybox = texture(g_diffuseTexture, v_cubeTexture);
	//vec4 skybox = texture(g_diffuseTexture, vec2(v_cubeTexture));

	// Set Output Color
	o_color = skybox;
}