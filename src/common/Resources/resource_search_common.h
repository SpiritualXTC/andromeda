#ifndef _ANDROMEDA_COMMON_FILE_SEARCH_COMMON_H_
#define _ANDROMEDA_COMMON_FILE_SEARCH_COMMON_H_

#include <andromeda/Resources/resource_manager.h>

namespace andromeda
{
	/*
	
	*/
	class CommonResourceScan : public andromeda::IResourceScan
	{
	public:
		CommonResourceScan();
		virtual ~CommonResourceScan();

		/*
		
		*/
		aBoolean search(const std::string & location,
			const std::string & filterPath,
			const std::string & extension,
			std::vector<std::string> & files) override;

		/*
		
		*/
		std::shared_ptr<ResourceStream> load(const std::string & location,
			const std::string & localPath,
			const std::string & filename) override;
	};
}

#endif
