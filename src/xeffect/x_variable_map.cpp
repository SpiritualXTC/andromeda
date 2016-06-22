#include "x_variable_map.h"

#include <sstream>

#include <boost/regex.hpp>

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XVariableMap::XVariableMap()
{

}


/*

*/
XVariableMap::~XVariableMap()
{

}




/*
	Check whether a key exists
*/
const Boolean XVariableMap::exists(const std::string & key)
{
	return _map.find(key) != _map.end();
}

/*
	Add or Modify a Value
*/
const void XVariableMap::set(const std::string & key, const std::string & value)
{
	_map[key] = value;
}

/*
	Get a Value
*/
const std::string & XVariableMap::get(const std::string & key)
{
	// Throws Exception
	return _map.at(key);
}


/*
	Parse a string for variables, and replace with their value
*/
std::string XVariableMap::parse(const std::string & value)
{
	std::string str = value;

	for (const auto & p : _map)
	{
		std::stringstream strVar;
		strVar << "(\\$\\(" << p.first << "\\))";

		std::string fmt = p.second;

		boost::regex expr(strVar.str());

		str = boost::regex_replace(str, expr, fmt);
	}

	return str;
}