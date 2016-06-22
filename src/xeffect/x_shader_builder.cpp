#include "x_shader_builder.h"

#include <unordered_map>

#include <andromeda/graphics.h>

#include "x_extension.h"
#include "x_shader.h"
#include "x_shader_source.h"

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XShaderBuilder::XShaderBuilder(XShaderType shaderType)
	: _shaderType(shaderType)
{

}

/*

*/
XShaderBuilder::~XShaderBuilder()
{
	
}

/*

*/
Boolean XShaderBuilder::attachHeader(XExtension & extensions)
{
	_source << extensions.getHeader() << std::endl;

	return true;
}


/*

*/
Boolean XShaderBuilder::attachCode(std::shared_ptr<XShaderSource> & source)
{
	assert(source);

	_source << source->source();
	_source << std::endl << std::endl;

	return true;
}


/*

*/
std::shared_ptr<XShader> XShaderBuilder::compile()
{
	/*
		TODO:

		Preprocessing of code should be done here!
	*/

	std::shared_ptr<XShader> shader = std::make_shared<XShader>(_shaderType);
	shader->compile(_source.str());
	return shader;
}







/*

*/
XShaderProgramBuilder::XShaderProgramBuilder()
{

}


/*

*/
XShaderProgramBuilder::~XShaderProgramBuilder()
{

}


/*

*/
void XShaderProgramBuilder::attachShader(const std::shared_ptr<XShaderBuilder> & shader)
{
	if (shader)
		_shaders.push_back(shader);
	return;
}


/*

*/
std::shared_ptr<XShaderProgram> XShaderProgramBuilder::link()
{
	std::shared_ptr<XShaderProgram> program = std::make_shared<XShaderProgram>();

	// Create Program
	if (!program->create())
		return nullptr;

	// Attach Shaders
	for (const auto & shader : _shaders)
	{
		// Compile Shader
		std::shared_ptr<XShader> s = shader->compile();

		// Invalid Shader
		if (!s || ! s->isValid())
			return nullptr;

		// Attach Compiled Shader
		if (! program->attach(s))
			return nullptr;
	}

	// Link Program
	if (!program->link())
		return nullptr;

	return program;
}