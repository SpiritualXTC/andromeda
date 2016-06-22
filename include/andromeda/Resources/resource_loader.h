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
		Unknown Resource
	*/
	class ResourceLoader
	{
	public:
		ResourceLoader()
		{
		}


		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> build(std::shared_ptr<File> file)
		{
			log_errp("No Resource Loading Implemented. Unable to load Resource");

			return nullptr;
		}
		
	};
}
