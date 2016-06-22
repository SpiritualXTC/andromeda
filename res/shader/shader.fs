// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!


// Material
uniform vec3 g_ambient;	
uniform vec3 g_diffuse;
uniform vec3 g_specular;
uniform float g_opacity;

// Texture
uniform sampler2D g_diffuseTexture;



// Passed Along the Pipe
in vec2 v_diffuseTextureCoord;
in vec3 v_normal;

// Output
out vec4 o_color;


// Entry Point
void main()
{
	// Get Diffuse Color from Texture 
	vec4 texDif = texture2D(g_diffuseTexture, v_diffuseTextureCoord);
	vec4 dif = vec4(g_diffuse, 1);

	// Set Output Color
	o_color = dif * texDif;
}