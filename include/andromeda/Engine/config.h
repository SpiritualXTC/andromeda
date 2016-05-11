#ifndef _ANDROMEDA_ENGINE_CONFIG_H_
#define _ANDROMEDA_ENGINE_CONFIG_H_

/*
	Configuration:
	
	Configuration Information Loaded from a file located somewhere on the users HDD!
*/


#include "module.h"

#include <string>

#include <boost/property_tree/ptree.hpp>




namespace andromeda
{
	class Config
	{
	public:
		Config();
		virtual ~Config();


		Boolean load(const std::string & filename);
		Boolean save();

	private:

		std::string _filename;

		
	};
}

typedef andromeda::Config aConfig;

#endif