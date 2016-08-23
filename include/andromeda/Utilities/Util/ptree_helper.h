#pragma once

/*
	Static Class with helper functionality for accessing boost/ptree
*/
#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

namespace andromeda
{
	namespace util
	{
		boost::optional<std::string> getChildValueOptional(const boost::property_tree::ptree & propTree, const std::string & child);
	};

}