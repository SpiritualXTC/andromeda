#include <andromeda/Engine/config.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/exception.hpp>


#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Config::Config() : Module(Module::Idle, Module::Lowest, true)
{
	log_verbose("Config: Created");

	load("andromeda.conf");
}



/*

*/
Config::~Config()
{
	log_verbose("Config: Destroyed");
}


/*

*/
Boolean Config::load(const std::string & filename)
{
	_filename = filename;

	
	try
	{
	//s	boost::property_tree::ptree props;

	//	boost::property_tree::read_json(filename, props, std::locale());
	}
	catch (boost::exception & e)
	{
		//log_err("failed: ", e.)
	}
	return true;
}


/*

*/
Boolean Config::save()
{
	return true;
}