// Deferred Shader : Light Shader
//


// G Buffer
uniform sampler2D u_gBufferDiffuse;
uniform sampler2D u_gBufferPosition;
uniform sampler2D u_gBufferNormal;

// Camera
uniform vec3 u_cameraPosition;// = vec3(0.0, 0.0, 0.0);

// Light
uniform vec3 u_lightAmbient = vec3(0.0, 0.0, 0.0);
uniform vec3 u_lightDiffuse = vec3(1.0, 1.0, 1.0);
uniform vec3 u_lightSpecular = vec3(1.0, 1.0, 1.0);

uniform vec3 u_lightPosition = vec3(0.0, 1.0, 0.0);	// Directly Overhead

// Shadow
uniform bool u_lightShadow = true;
uniform mat4 u_lightShadowMatrix;			// Light Projection View Model Matrix
uniform sampler2D u_lightShadowMap;			// Shadow Map Texture





// Varying
in vec2		v_textureCoordinate;

// Output
out vec4 o_color;



// ambientComponent
vec3 ambientComponent(in vec3 color)
{
	return color * u_lightAmbient;
}

// diffuseComponent
vec3 diffuseComponent(in vec3 normal, in vec3 color)
{
	float diffuse = clamp(dot(normal, u_lightPosition), 0, 1);

	return color * (u_lightDiffuse - u_lightAmbient) * diffuse;
}

// specularComponent
vec3 specularComponent(in vec3 normal, in vec3 position, in vec3 color, in float shininess)
{
	vec3 specular = vec3(0.0, 0.0, 0.0);

	vec3 eye = normalize(u_cameraPosition - position);
	
	// Light Position here is ambiguous, directional lights and point/spot lights will treat this differently
	float intensity = max(dot(normal, u_lightPosition), 0.0);
	
	if (intensity > 0.0)
	{
		vec3 h = normalize(u_lightPosition + eye);
		float specTerm = max(dot(h, normal), 0.0);
		
		specular = clamp(color * pow(specTerm, shininess), 0, 1);
	}
	
	// TODO: Setup Specular Lighting
	return specular * u_lightSpecular;
}


// inShadow()
// Calculates whether the position is in shadow
bool inShadow(in vec4 worldPosition)
{
	float bias = 0.01;
	
	// Project World Position into Light Space
	vec4 posLight = u_lightShadowMatrix * worldPosition;
		
	// Sample Shadow Map
	vec4 shadow = texture(u_lightShadowMap, posLight.xy);
		
	// Projected World Space Depth Component closer than the 
	// value stored in the texture, with some bias to prevent artifacting.
	return shadow.z < min(1.0, posLight.z) - bias;
}



// main()
// Main
void main(void)
{
	// Read G-Buffer
	vec4 position = texture2D(u_gBufferPosition, v_textureCoordinate);		// modelMatrix * position :: Alternative = modelViewMatrix * position
	vec4 normal = texture2D(u_gBufferNormal, v_textureCoordinate);			// normalMatrix * normal
	vec4 diffuseRGB = texture2D(u_gBufferDiffuse, v_textureCoordinate);		// diffuseMaterial * diffuseTexture

	// Normalize ... Normal
	normal.rgb = normalize(normal.rgb);

	// TODO:
	// It could be more beneficial to store the geometry position, in view space, rather than world space.
	// However this may require as few extra calculations for some other areas.
	
	// TODO:
	// Depth value could be stored in the alpha channel of the Position
	
	// Culling Phase 
	// Do not continue unless geometry has been rendered to this pixel :)
	// TODO: This phase can be culled out by the stencil buffer.
	// That will however, require copying the stencil buffer from the GBuffer, so it's the active stencil buffer when rendering the lights
	if (position.w == 0.0) discard;

	// Calculate Ambient :: diffuse.rgb * lightAmbient
	vec3 i_ambient = ambientComponent(diffuseRGB.rgb);

	// Calculate Diffuse :: diffuse.rgb * lightDiffuse * lightIntensity
	vec3 i_diffuse = vec3(0.0, 0.0, 0.0);
	if (! (u_lightShadow && inShadow(position)) )
	{
		i_diffuse = diffuseComponent(normal.rgb, diffuseRGB.rgb);
	}

	// Calculate Specular

	// TODO: Specular Color and Shininess need to be pulled from the GBuffer
	// TODO: Specular probably also shouldn't be visible if in shadow...
	vec3 specularRGB = vec3(1.0, 1.0, 1.0);
	float specularShininess = 64.0;

	vec3 i_specular = specularComponent(normal.rgb, position.rgb, specularRGB, specularShininess);

	
	// TODO: Environment Mapping Should probably be handled here instead of as part of the Deferred Stage
	// TODO: Reflectivity should also be pulled from the GBuffer -- However GBUffer channels are available.
	
	// Set Output Color
	o_color.rgb = i_ambient + i_diffuse + i_specular;
	//o_color.rgb = i_specular;
	
	// Set Alpha
	o_color.a = 1.0;
}











































