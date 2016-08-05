// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!


// Material
uniform vec3 g_ambient;
uniform vec3 g_diffuse;
uniform vec3 g_specular;
uniform float g_opacity;

// Light [Testing]
uniform vec3 g_lightDirection = vec3(-0.5, -0.7, -0.7);
uniform vec3 g_lightDiffuse = vec3(1.0, 1.0, 1.0);

// Texture
uniform sampler2D g_diffuseTexture;



// Passed Along the Pipe
in vec2 v_diffuseTextureCoord;
in vec3 v_position;
in vec3 v_normal;

// Output
out vec4 o_color;


// Entry Point
void main()
{
	// Get Diffuse Color from Texture 
	vec4 texDif = texture2D(g_diffuseTexture, v_diffuseTextureCoord);

	if (texDif.a == 0.0) discard;

	vec4 dif = vec4(g_diffuse, 1);


	// Calculate Lighting
	float lightIntensity = max(dot(v_normal, -g_lightDirection), 0.0);

	vec4 lightDiffuse = vec4(lightIntensity * g_lightDiffuse, 1.0);

	// Set Output Color
	o_color = dif * lightDiffuse * texDif;
}