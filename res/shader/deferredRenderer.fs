


// G Buffer
uniform sampler2D g_gBufferDiffuse;
uniform sampler2D g_gBufferPosition;
uniform sampler2D g_gBufferNormal;

// Light
uniform vec3 g_lightDirection = vec3(-0.5, -0.7, -0.7);
uniform vec3 g_lightDiffuse = vec3(1.0, 1.0, 1.0);

// Varying
varying vec2		v_textureCoordinate;

// Output
out vec4 o_color;

void main(void)
{

	// Read G-Buffer
	vec4 diffuse = texture2D(g_gBufferDiffuse, v_textureCoordinate);
	vec4 position = texture2D(g_gBufferPosition, v_textureCoordinate);
	vec4 normal = texture2D(g_gBufferNormal, v_textureCoordinate);

	// Calculate Ambient
	vec4 ambient = diffuse * 0.15;

	// Calculate Lighting
	float lightIntensity = max(dot(normal.xyz, -g_lightDirection), 0.0);
	vec4 lightDiffuse = vec4(lightIntensity * g_lightDiffuse, 1.0);

	// TODO: Calculate Specular



	// Set Output Color
	o_color = ambient + diffuse * lightDiffuse;
}

