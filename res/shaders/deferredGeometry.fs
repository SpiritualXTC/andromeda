// Deferred Shader
// Renders Geometry to a Series of RenderBuffers

uniform mat4 u_view;		// View Matrix




// Material
uniform vec3 u_ambientMaterial;
uniform vec3 u_diffuseMaterial;
uniform vec3 u_specularMaterial;
uniform float u_shininessMaterial;
uniform float u_reflectivityMaterial; 

uniform float u_opacityMaterial;



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
//in vec3 v_eyePosition;
//in vec3 v_eyeNormal;




vec4 diffuseComponent()
{
	vec4 texel = texture(g_diffuseTexture, v_diffuseTextureCoord);

	return texel * vec4(u_diffuseMaterial, 1.0);
}

vec4 environmentComponent(in vec3 position, in vec3 normal)
{
	vec3 camPos = u_view[2].xyz;
	
	vec4 P = u_view * vec4(position, 1.0);
	
	//vec3 I = normalize(position - camPos);
	vec3 I = normalize(-P.xyz);
	vec3 R = reflect(I, normal);
	
	return texture(u_envReflection, R);
}



// TODO: Add a binary input image mask that can be used to discard pixels
// TODO: Add a specular output image that contains the specular color (rgb) and specular power (alpha)
// TOOD: Add a second input diffuse Texture Channel

void main( void )
{
	// Sample Alpha Mask

	// Alpha Discard from the Mask


	// Sample Diffuse Texture :: Currently using this texture for the AlphaMask as well
	vec4 diffuseRGB = diffuseComponent();//texture(g_diffuseTexture, v_diffuseTextureCoord);

	// Alpha Discard :: The Alpha Mask should be used for this, rather than the diffuse texture
	if (diffuseRGB.a == 0.0) discard;



	
	// Environment Mapping :: TODO this should probably be done during the light pass
	vec4 envRGB = environmentComponent(v_position, v_normal);
	
	
	



	// Output to Diffuse Texture :: Can the gl_Position.w be used here to show depth?? (in the alpha channel)
	//gl_FragData[0] = mix(diffuseRGB, envRGB, u_reflectivityMaterial);
	gl_FragData[0] = diffuseRGB * vec4(u_diffuseMaterial, 1.0);
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
