#include "x_uniform_builder.h"

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include <andromeda/glm.h>

#include "x_node.h"
#include "x_uniform.h"


using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XUniformBuilder::XUniformBuilder(const XNode & node)
	: _node(node)
{
	// Get Uniform Name
	boost::optional<std::string> name = _node.getAttribute("name");
	if (name.is_initialized())
		_name = name.get();


	// Get Data Type
	boost::optional<std::string> type = _node.getAttribute("type");

	if (type.is_initialized())
		_type = determineType(type.get());


	// Specific Values
	_node.getAttributeArray("value", _values);

	


}



/*

*/
XUniformBuilder::~XUniformBuilder()
{

}


/*

*/
XUniformBuilder::_UniformDataType XUniformBuilder::determineType(const std::string & type)
{
	XUniformBuilder::_UniformDataType t = _UniformDataType::Auto;

	if (boost::iequals(type, "float"))
		t = _UniformDataType::Float;
	else if (boost::iequals(type, "int"))
		t = _UniformDataType::Int;
	else
	{
		// Maybe display an error/warning
		t = _UniformDataType::Auto;
	}

	return t;
}





/*

*/
std::shared_ptr<XUniform> XUniformBuilder::build()
{
	std::shared_ptr<XUniform> uniform;

	// Determine Type
	if (_type == _UniformDataType::Auto)
	{
		// TODO: Smart Check to determine if all values match an int or float profile
		_type = _UniformDataType::Float;
	}

	// Create Instance
	// Naive Implementation
	switch (_type)
	{
	case _UniformDataType::Float:
		uniform = buildFloat();
		break;
	case _UniformDataType::Int:
		uniform = buildInt();
		break;
	}


	return uniform;
}


/*

*/
std::shared_ptr<XUniform> XUniformBuilder::buildFloat()
{
	std::shared_ptr<XUniform> uniform;

	std::vector<Float> v;

	for (const auto & s : _values)
		v.push_back(std::stof(s));

	const Size size = v.size();

	switch (size)
	{
	case 1:
		uniform = std::make_shared<XUniformType<Float>>(_name, v[0]);
		break;
	case 2:
		uniform = std::make_shared<XUniformType<glm::fvec2>>(_name, glm::fvec2(v[0], v[1]));
		break;
	case 3:
		uniform = std::make_shared<XUniformType<glm::fvec3>>(_name, glm::fvec3(v[0], v[1], v[2]));
		break;
	case 4:
		uniform = std::make_shared<XUniformType<glm::fvec4>>(_name, glm::fvec4(v[0], v[1], v[2], v[3]));
		break;
	default:
		// Display Warning
		break;
	}

	return uniform;
}


/*

*/
std::shared_ptr<XUniform> XUniformBuilder::buildInt()
{
	std::shared_ptr<XUniform> uniform;

	std::vector<Int32> v;

	for (const auto & s : _values)
		v.push_back(std::stoi(s));

	const Size size = v.size();

	switch (size)
	{
	case 1:
		uniform = std::make_shared<XUniformType<Int32>>(_name, v[0]);
		break;
	case 2:
		uniform = std::make_shared<XUniformType<glm::ivec2>>(_name, glm::ivec2(v[0], v[1]));
		break;
	case 3:
		uniform = std::make_shared<XUniformType<glm::ivec3>>(_name, glm::ivec3(v[0], v[1], v[2]));
		break;
	case 4:
		uniform = std::make_shared<XUniformType<glm::ivec4>>(_name, glm::ivec4(v[0], v[1], v[2], v[3]));
		break;
	default:
		// Display Warning
		break;
	}

	return uniform;
}