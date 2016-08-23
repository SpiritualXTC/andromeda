#pragma once

// Std Lib
#include <memory>

// Boost
#include <boost/property_tree/ptree.hpp>

// Andromeda
#include <andromeda/stddef.h>



#include "resource.h"

namespace andromeda
{

	class IFileLocation;



	// Resource Builder
	template <typename RESOURCE, typename ARGS>
	class ResourceBuilderEx
	{
	public:

		// Builds the Resource Container Object
		virtual std::shared_ptr<ResourceEx<RESOURCE, ARGS>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) = 0;

		// Loads the Resource in the Container via the location
		virtual std::shared_ptr<RESOURCE> load(const ARGS & args, const IFileLocation * location) = 0;

		


	private:
	};
}
