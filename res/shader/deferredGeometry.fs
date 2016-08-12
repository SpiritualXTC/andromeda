// Deferred Shader
// Renders Geometry to a Series of RenderBuffers

uniform sampler2D Diffuse;


// Material
uniform vec3 g_ambient;
uniform vec3 g_diffuse;
uniform vec3 g_specular;
uniform float g_opacity;

// Textures
uniform sampler2D u_alphaMask;
uniform sampler2D g_diffuseTexture;


uniform samplerCube u_envReflection;


// Varying
varying vec3		v_position;
varying vec3		v_normal;
varying vec2		v_diffuseTextureCoord;

// TODO: Add a binary input image mask that can be used to discard pixels
// TODO: Add a specular output image that contains the specular color (rgb) and specular power (alpha)
// TOOD: Add a second diffuse Texture Channel

void main( void )
{
	// Sample Alpha Mask

	// Alpha Discard from the Mask


	// Sample Diffuse Texture :: Currently using this texture for the AlphaMask as well
	vec4 difTexRGB = texture2D(g_diffuseTexture, v_diffuseTextureCoord);

	// Alpha Discard :: This might be better to be done from the Alpha Mask Image
	if (difTexRGB.a == 0.0) discard;


	// Sample the Environment map for Reflections




	// Output to Diffuse Texture :: Can the gl_Position.w be used here to show depth?? (in the alpha channel)
	gl_FragData[0]		= difTexRGB * vec4(g_diffuse, 1.0);

	// Output to Position Texture
	gl_FragData[1]		= vec4(v_position, 1.0);

	// Output to Normal Texture
	gl_FragData[2]		= vec4(v_normal, 1.0);

	// Output to Specular Texture
	//gl_fragData[x]	= vec4(g_specular, shininess);
}
