#include <andromeda/Graphics/pass.h>

#include <cassert>

#include <andromeda/Graphics/shader.h>


using namespace andromeda;

/*

*/
Pass::Pass(std::shared_ptr<Shader> shader) : _shader(shader)
{
	assert(_shader);
}


/*

*/
Pass::~Pass()
{
	
}


/*
	begin():

	Set OpenGL Configuration Settings
*/
void Pass::begin()
{
	
	// Bind the Shader
	_shader->bind();
}



/*
	end():

	Set OpenGL Configuration Settings
*/
void Pass::end()
{

	// Unbind the Shader
	_shader->unbind();
}