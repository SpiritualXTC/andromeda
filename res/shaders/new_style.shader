
// There is a one-liner declaration that can exist in the first line(s) for defining min version and extensions

// Built in Functions that need to be handled by the loader
include(...)






// Uniforms [Shared across all shaders even though half of the time they aren't needed]	- Throw an error when the shader attribute isn't present. The attribute needs to be either stripped before compilation or preceded by a ;// to end the line and start a comment
// This can be detected with simple regex
uniform mat4 u_proj : PROJECTION;
uniform mat4 u_view : VIEW;
uniform mat4 u_model : MODEL;


uniform vec4 u_materialDiffuse : MATERIAL_DIFFUSE;
uniform vec4 u_materialAmbient : MATERIAL_AMBIENT;
uniform vec4 u_materialSpecular : MATERIAL_SPECULAR;

uniform vec2 u_random : CUSTOM; // These lines could include comments!

/*
uniform vec2 u_ignore : DUNINCLUDEMEH;
Lines could also be included in multiline comments
*/



// GOOD practise may be to prepend ALL in/out parameters with the shader abbreviation
// IE: vertex shader inputs have vs_ preceded, it's outputs have ps_ preceded. 
// FINAL output could be o_ or sh_ or something
// ADDITIONAL check to confirm that all the OUTPUT parameters exist in the NEXT sub-shaders INPUT parameters [Optional, shader compilation will detect this anyway]

vec3 fn_random()
{

}

// Attributes [In Parameters] -- could use layout syntax instead, rather than attribute specification. However that makes assumptions. Maybe optional attribute to override any layout indexing
void vs_main(in vec3 vs_position : POSITION, in vec3 vs_normal : NORMAL, out vec3 ps_position, out vec3 ps_normal, out vec2 ps_texture) : VERTEX_SHADER
{

}



// The OUTPUT of the GeometryShader is the INPUT to the VertexShader
// The OUTPUT of the VertexShader is the INPUT to the FragmentShader
 


// Varying [In Parameters]
void ps_main(in vec3 ps_position, in vec3 ps_normal, in vec2 ps_texture, out vec4 o_color) : FRAGMENT_SHADER
{
	// OUTPUT constant colour as this is just a dummy shader :)
	o_color = vec4(0,0,0,0)
}



void pass_name() : PASS
{
	polygon = wireframe;
	vertex_shader = vs_main
	fragment_shader = ps_main
}

void pass_name2() : PASS
{

}

void debug_pass() :PASS
{

}


technique t1 (pass_name, pass_name2, debug_pass)






/*
	Automatic Defaults
	NO technique defined : Auto create one
	NO pass defined : AUTO create one
*/

/*
	COMPILATION:
	STEP 1:
		Strip all multiline comments from the script [this is to make things easier to deal with later ... essentially, regex.replaceall('\/\*[.*]\*\/', '')
	
	STEP 2:
		Include any additional files declared by include(..)	[The included file starts at STEP 1 as well]
	
	STEP 3:
		Extract ALL Functions as a single STRING
		Extract ALL Uniforms as STRING
		
		Specialised Functions, (IE those with a : TYPE] after the declaration are divided into respective shaders
		There is a requirement that a shader has BOTH a VERTEX_SHADER and a FRAGMENT_SHADER defined
		
*/

