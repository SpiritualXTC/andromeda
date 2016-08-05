// Deferred Shader
// Renders Geometry to a Series of RenderBuffers

uniform sampler2D Diffuse;


// Material
uniform vec3 g_ambient;
uniform vec3 g_diffuse;
uniform vec3 g_specular;
uniform float g_opacity;

// Textures
uniform sampler2D g_diffuseTexture;




// Varying
varying vec3		v_position;
varying vec3		v_normal;
varying vec2		v_diffuseTextureCoord;

// TODO: Add a binary input image mask that can be used to discard pixels
// TODO: Add a specular output image that contains the specular color (rgb) and specular power (alpha)
// TOOD: Add a second diffuse Texture Channel

void main( void )
{
	vec4 difTexRGB = texture2D(g_diffuseTexture, v_diffuseTextureCoord);

	// Alpha Discard
	if (difTexRGB.a == 0.0) discard;

	// Output to Diffuse Texture :: Can the gl_Position.w be used here to show depth?? (in the alpha channel)
	gl_FragData[0]		= difTexRGB * vec4(g_diffuse, 1.0);

	// Output to Position Texture
	gl_FragData[1]		= vec4(v_position, 1.0);

	// Output to Normal Texture
	gl_FragData[2]		= vec4(v_normal, 1.0);
}
