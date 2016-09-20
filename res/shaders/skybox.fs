// Skybox Shader V0.2
// Used for rendering the Skybox :)


uniform samplerCube u_diffuseTexture;

// Pass along the Pipeline
in vec3 v_cubeTextureCoords;

// Output
out vec4 o_color;

// Entry Point
void main()
{
	// Sample Cube
	vec4 skybox = texture(u_diffuseTexture, normalize(v_cubeTextureCoords));

	// Set Output Color
	o_color = skybox;
}