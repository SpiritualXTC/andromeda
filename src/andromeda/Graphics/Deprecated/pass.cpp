#include <andromeda/Graphics/Deprecated/pass.h>

#include <cassert>

#include <andromeda/Graphics/Deprecated/shader.h>


using namespace andromeda;

/*

*/
//Pass::Pass(std::shared_ptr<Shader> shader) : _shader(shader)
Pass::Pass(const std::string & name, std::shared_ptr<Shader> shader) 
	: _name(name)
	, _shader(shader)
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
Boolean Pass::begin()
{
	assert(_shader);
	
	if (! _enabled)
		return _enabled;

	// Bind the Shader
	_shader->bind();

	return _enabled;
}



/*
	end():

	Set OpenGL Configuration Settings
*/
Boolean Pass::end()
{
	assert(_shader);

	// Disabled
	//if (!_enabled)
	//	return _enabled;

	// Unbind the Shader
	_shader->unbind();

	return _enabled;
}