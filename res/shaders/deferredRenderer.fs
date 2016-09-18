// Deferred Shader : Light Shader
//


// G Buffer
uniform sampler2D u_gBufferDiffuse;
uniform sampler2D u_gBufferPosition;
uniform sampler2D u_gBufferNormal;

// Camera
uniform vec3 u_cameraPosition;// = vec3(0.0, 0.0, 0.0);

// Light
uniform vec3 u_lightDirection = vec3(-0.5, -0.7, -0.5);


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
vec3 ambientComponent(in vec3 diffuseColor)
{
	return diffuseColor * u_lightAmbient;
}

// diffuseComponent
vec3 diffuseComponent(in vec3 normal, in vec3 diffuseColor)
{
	float diffuse = clamp(dot(normal, u_lightPosition), 0, 1);

	return diffuseColor * (u_lightDiffuse - u_lightAmbient) * diffuse;
}

// specularComponent()
// normal			: Normal vector
// toLight			: LightPosition - Position
// toCamera			: CameraPosition - Position
// specularColor	: Specular Color
// shininess		: Specular Shininess
vec3 specularComponent(in vec3 normal, in vec3 toLight, in vec3 toCamera, in vec3 color, in float shininess)
{
	// Light Specular Color :: Should be a Uniform
	float spec = 0.0;
	
	return clamp(color * u_lightSpecular * spec, 0, 1);
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



void main(void)
{
	// Read G-Buffer
	vec4 position = texture2D(u_gBufferPosition, v_textureCoordinate);		// modelviewMatrix * position
	vec4 normal = texture2D(u_gBufferNormal, v_textureCoordinate);			// normalMatrix * normal
	vec4 diffuseRGB = texture2D(u_gBufferDiffuse, v_textureCoordinate);		// diffuseMaterial * diffuseTexture

	// Lighting Vectors [Directional Light]
//	vec3 toLight = normalize(-u_lightDirection - position.rgb);
//	vec3 toCamera = normalize(u_cameraPosition - position.rgb);


	// Culling Phase 
	// Do not continue unless geometry has been rendered to this pixel :)
	// TODO: This phase can be culled out by the stencil buffer.
	// That will however, require copying the stencil buffer from the GBuffer, so it's the active stencil buffer when rendering the lights
	if (position.w == 0.0) discard;

	// Calculate Ambient
	vec3 i_ambient = ambientComponent(diffuseRGB.rgb);	// diffuse.rgb * lightAmbient

	// Calculate Diffuse
	vec3 i_diffuse = vec3(0.0, 0.0, 0.0);
	if (! inShadow(position))
		i_diffuse = diffuseComponent(normal.rgb, diffuseRGB.rgb);//diffuse.rgb * lightDiffuse * lightIntensity;

	// Calculate Specular
	//vec3 i_specular = specularComponent(normal.rgb, toLight, toCamera);

	vec3 i_specular = vec3(0.0, 0.0, 0.0);
	

	// TODO: Move to specular function.
	vec3 n = normalize(normal.rgb);
	vec3 e = normalize(u_cameraPosition - position.rgb);
	
	float intensity = max(dot(n, u_lightPosition), 0.0);
	
	if (intensity > 0.0)
	{
		vec3 h = normalize(u_lightPosition + e);
		float intSpec = max(dot(h, n), 0.0);
		
		i_specular = vec3(1.0, 1.0, 1.0) * pow(intSpec, 64.0);
	}

	
	
	// Set Output Color
	//o_color.rgb = (i_ambient + i_diffuse + i_specular) * i_shadow;
	o_color.rgb = i_ambient + i_diffuse + i_specular;
	//o_color.rgb = i_specular;
	//o_color.g = specCoef;
	
	//.rgb = surface;
	
	o_color.a = 1.0;
}











































