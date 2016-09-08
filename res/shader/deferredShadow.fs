// Deferred Shader
// Renders Shadows

// TODO: This should be the mask texture :)
uniform sampler2D g_diffuseTexture;

// Varying
in vec2 v_diffuseTextureCoord;


out vec4 o_color;

void main()
{
	// Sample Texture Mask
	vec4 diffuseRGB = texture(g_diffuseTexture, v_diffuseTextureCoord);
	
	// Discard if Transparent
	if (diffuseRGB.a == 0.0) discard;

	// Output
	o_color = vec4(0.0, 0.0, 0.0, 0.0);
}