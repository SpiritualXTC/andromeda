


// G Buffer
uniform sampler2D u_gBufferDiffuse;
uniform sampler2D u_gBufferPosition;
uniform sampler2D u_gBufferNormal;

// Camera
uniform vec3 u_cameraPosition = vec3(0.0, 0.0, 0.0);

// Light
uniform vec3 g_lightDirection = vec3(-0.5, -0.7, -0.5);
uniform vec3 g_lightDiffuse = vec3(1.0, 1.0, 1.0);

// Varying
in vec2		v_textureCoordinate;

// Output
out vec4 o_color;




vec3 diffuseComponent(in vec3 normal, in vec3 lightDir, in vec3 diffuseColor)
{
	float diffuse = clamp(dot(normal, -lightDir), 0, 1);

	return diffuseColor * g_lightDiffuse * diffuse;
}

// specularComponent()
// normal			: Normal vector
// toLight			: LightPosition - Position
// toCamera			: CameraPosition - Position
// specularColor	: Specular Color
// shininess		: Specular Shininess
vec3 specularComponent(in vec3 normal, in vec3 toLight, in vec3 toCamera, in vec3 specularColor, in float shininess)
{
	// Light Specular Color :: Should be a Uniform
	vec3 lightSpecColor = vec3(1.0, 1.0, 1.0);


	float specular = 0.0;

	if (dot(normal, toLight) > 0)
	{
		vec3 half = normalize(toLight + toCamera);
		specular = pow(dot(normal, half), shininess);
	}

	return specularColor * lightSpecColor * specular;
}



void main(void)
{
	// Read G-Buffer
	vec4 diffuse = texture2D(u_gBufferDiffuse, v_textureCoordinate);
	vec4 position = texture2D(u_gBufferPosition, v_textureCoordinate);
	vec4 normal = texture2D(u_gBufferNormal, v_textureCoordinate);


	// Lighting Vectors [Directional Light]
	vec3 toLight = (-g_lightDirection * 10000.0) - position.rgb;
	vec3 toCamera = u_cameraPosition - position.rgb;


	// Culling Phase 
	// Do not continue unless geometry has been rendered to this pixel :)
	// TODO: This phase can be culled out by the stencil buffer.
	// That will however, require copying the stencil buffer from the GBuffer, so it's the active stencil buffer when rendering the lights
	if (position.w == 0.0) discard;



	// Calculate Lighting
//	float lightIntensity = max(dot(normal.xyz, -g_lightDirection), 0.0);
//	vec3 lightDiffuse = lightIntensity * g_lightDiffuse;


	// Calculate Ambient
	vec3 i_ambient = diffuse.rgb * 0.15;

	// Calculate Diffuse
	vec3 i_diffuse = diffuseComponent(normal.rgb, g_lightDirection, diffuse.rgb);//diffuse.rgb * lightDiffuse;

	// Calculate Specular
	vec3 i_specular = specularComponent(normal.rgb, toLight, toCamera, vec3(1.0, 1.0 , 1.0), 64.0);

	// Set Output Color
	o_color.rgb = i_ambient + i_diffuse + i_specular;
	o_color.a = 1.0;
}

