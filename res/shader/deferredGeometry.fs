// Deferred Shader
// Renders Geometry to a Series of RenderBuffers

uniform mat4 u_view;		// View Matrix




// Material
uniform vec3 u_ambientMaterial;
uniform vec3 u_diffuseMaterial;
uniform vec3 u_specularMaterial;
uniform vec3 u_shininessMaterial;

uniform float u_materialOpacity;



// Textures
uniform sampler2D u_alphaMask;
uniform sampler2D g_diffuseTexture;


// Environment
uniform samplerCube u_envReflection;


// Varying
in vec3	v_position;
in vec3	v_normal;
in vec2	v_diffuseTextureCoord;

// Varying for Refelections
in vec3 v_eyePosition;
in vec3 v_eyeNormal;


// TODO: Add a binary input image mask that can be used to discard pixels
// TODO: Add a specular output image that contains the specular color (rgb) and specular power (alpha)
// TOOD: Add a second diffuse Texture Channel

void main( void )
{
	// Sample Alpha Mask

	// Alpha Discard from the Mask


	// Sample Diffuse Texture :: Currently using this texture for the AlphaMask as well
	vec4 diffuseRGB = texture(g_diffuseTexture, v_diffuseTextureCoord);

	// Alpha Discard :: This might be better to be done from the Alpha Mask Image
	if (diffuseRGB.a == 0.0) discard;






	// Sample the Environment map for Reflections

	vec3 incident_eye = normalize (v_eyePosition);
	vec3 normal = normalize (v_eyeNormal);

	vec3 reflected = reflect (incident_eye, normal);

  // convert from eye to world space
	reflected = vec3 (inverse (u_view) * vec4 (reflected, 0.0));

	vec4 envRGB = texture(u_envReflection, reflected);

	//reflected = abs(reflected) * 100.0;


	// Output to Diffuse Texture :: Can the gl_Position.w be used here to show depth?? (in the alpha channel)
	gl_FragData[0]		= diffuseRGB * vec4(u_diffuseMaterial, 1.0);
	//gl_FragData[0]		= diffuseRGB * vec4(u_diffuseMaterial, 1.0)  * 0.5 + envRGB * 0.5;
	//gl_FragData[0]		= envRGB;
	//gl_FragData[0]		= vec4(v_eyeNormal, 1.0);
	

	// Output to Position Texture
	gl_FragData[1]		= vec4(v_position, 1.0);

	// Output to Normal Texture
	gl_FragData[2]		= vec4(normalize(v_normal), 1.0);

	// Output to Specular Texture
	//gl_fragData[x]	= vec4(g_specular, shininess);
}
