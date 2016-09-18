#pragma once

#include <memory>
#include <string>
//#include <list>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/log.h>



/*
	TODO: REMOVE
*/


namespace andromeda
{
	// Forward Declarations
	class File;

	/*
		Base Class
	*/
	class IResourceLoader
	{
	public:

	};






	/*
		Loads a Resource
	*/
	class ResourceLoader
	{
	public:
		ResourceLoader() {}


		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> build(std::shared_ptr<File> file)
		{
			log_errp("No Resource Loading Implemented. Unable to load Resource");

			return nullptr;
		}
		


	};



	/*
		Builds a Resource
	*/
	class ResourceBuilder
	{
	public:
		ResourceBuilder() {}


		template <typename RESOURCE, typename ARGS>
		std::shared_ptr<RESOURCE> build(const ARGS * args)
		{
			log_errp("No Resource Loading Implemented. Unable to load Resource");

			return nullptr;
		}
	};

}
