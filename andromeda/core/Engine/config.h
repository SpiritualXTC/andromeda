#pragma once

#include <boost/property_tree/ptree.hpp>

#include <common/types.h>

namespace andromeda
{
	class Config
	{
	public:
		Config();
		virtual ~Config();


		Boolean load(const std::string& type, const std::string& filename, Boolean readOnly=true);
		Boolean save(const std::string& type);

		Boolean restore(const std::string& type) {}
	private:

		boost::property_tree::ptree _config;

	};
}