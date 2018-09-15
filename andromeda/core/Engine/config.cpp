#include "config.h"

using namespace andromeda;

Config::Config()
{

}

Config::~Config()
{

}



Boolean Config::load(const std::string& type, const std::string& filename, Boolean readOnly)
{
	// TODO: Check if File exists

	// TODO: Load File using Boost JSON parser

	// TODO: Append the JSON onto the config _config[type] = {filename: filename, contents: loaded_json, readOnly=readOnly}

	return true;
}


Boolean Config::save(const std::string& data)
{
	// TODO: Save the specific config

	return true;
}