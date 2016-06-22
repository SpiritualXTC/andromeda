#include "x_pass.h"

#include "x_state.h"
#include "x_uniform.h"

using namespace andromeda;
using namespace andromeda::xeffect;

/*

*/
XPass::XPass(const std::string & name, const std::shared_ptr<XShaderProgram> & shader)
	: _name(name)
	, _shader(shader)
{

}


/*

*/
XPass::~XPass()
{

}




/*

*/
void XPass::addUniform(const std::string & name, const glm::fvec2 & v)
{
	addUniform(std::make_shared<XUniformType<glm::fvec2>>(name, v));
}

/*

*/
void XPass::addUniform(const std::string & name, const glm::fvec3 & v)
{
	addUniform(std::make_shared<XUniformType<glm::fvec3>>(name, v));
}

/*

*/
void XPass::addUniform(const std::string & name, const glm::fvec4 & v)
{
	addUniform(std::make_shared<XUniformType<glm::fvec4>>(name, v));
}

/*

*/
void XPass::addUniform(const std::string & name, const glm::ivec2 & v)
{
	addUniform(std::make_shared<XUniformType<glm::ivec2>>(name, v));
}

/*

*/
void XPass::addUniform(const std::string & name, const glm::ivec3 & v)
{
	addUniform(std::make_shared<XUniformType<glm::ivec3>>(name, v));
}

/*

*/
void XPass::addUniform(const std::string & name, const glm::ivec4 & v)
{
	addUniform(std::make_shared<XUniformType<glm::ivec4>>(name, v));
}








/*

*/
void XPass::addUniform(const std::shared_ptr<XUniform> & uniform)
{
	assert(uniform);

	_uniforms.push_back(uniform);
}


/*

*/
void XPass::addState(const std::shared_ptr<IState> & state)
{
	assert(state);

	_states.push_back(state);
}



/*

*/
Boolean XPass::apply()
{
	assert(_shader);

	// Activate all of the things!



	// Apply shader
	if (!_shader->apply())
		return false;


	// Set Uniform Defaults
	for (const auto & uniform : _uniforms)
		uniform->apply(_shader);


	// Activate rasterization states
	for (const auto & state : _states)
		state->apply();


	return true;
}