#include <andromeda/Resources/resource_manager.h>

#include <cassert>

#include <andromeda/Utilities/log.h>



// TEMP
#include "../../common/Resources/resource_search_common.h"

using namespace andromeda;


/*

*/
ResourceManager::ResourceManager()
{
	// Create File System Search
	log_warn("Temporary Creation of search method for VFS");
	
	addSearch(std::make_shared<CommonResourceScan>());
}


/*

*/
ResourceManager::~ResourceManager()
{

}


/*

*/
void ResourceManager::addSearch(std::shared_ptr<IResourceScan> search)
{
	std::string key = "";

	std::shared_ptr<_Scan> s = std::make_shared<_Scan>();
	s->search = search;

	_search[key] = s;

	log_debug("Added Search Method");

}


/*

*/
void ResourceManager::addFilter(const std::string & path, const std::string & extension)
{
	std::shared_ptr<_Filter> filter = std::make_shared<_Filter>();

	filter->extension = extension;
	filter->path = path;

	_filters.push_back(filter);
}


/*

*/
void ResourceManager::addLocation(const std::string & location)
{
	// Determine Search Method...... [Pull Extension from location? No Extension = Default ???]
	std::string key = "";

	std::weak_ptr<_Scan> search = _search[key];

	if (search.expired())
	{
		log_err("No Search Method Found");
		return;
	}


	// Add Location
	std::shared_ptr<_Location> loc = std::make_shared<_Location>();
	loc->search = search;
	loc->location = location;
	_location.push_back(loc);


	log_debug("Search Location:", location.c_str());

	// More Focused Search
	for (const std::shared_ptr<_Filter> filter : _filters)
	{
		std::vector<std::string> files;

		std::shared_ptr<IResourceScan> scan = loc->search.lock()->search;

		// Search the location
		if (! scan->search(location, filter->path, filter->extension, files))
			continue;

		log_debug("Local Path:", filter->path.c_str());

		// Insert Files into Map
		for (const std::string & filename : files)
		{
			if (_files.find(filename) != _files.end())
			{
				log_warn("Override File");
			}

			// Create File Reference
			std::shared_ptr<_File> file = std::make_shared<_File>();
			file->filename = filename;
			file->filter = filter;
			file->location = loc;

			// Insert File into Map
			_files[filename] = file;

			log_debug("File:", filename.c_str());
		}
	}





}


/*

*/
std::shared_ptr<ResourceStream> ResourceManager::load(const std::string & filename)
{
	// Look for Hashmap Entry
	if (_files.find(filename) == _files.end())
	{
		log_warn("File: ", filename.c_str(), "Not found in map");
		return nullptr;
	}

	std::shared_ptr<_File> file = _files[filename];

	// Validate Pointer
	if (file->location.expired() || file->filter.expired())
	{
		log_warn("File: ", filename.c_str(), ". Unable to load File, location doesn't exist");
		return nullptr;
	}

	// Get Pointer
	std::shared_ptr<_Location> location = file->location.lock();
	std::shared_ptr<_Filter> filter = file->filter.lock();
	std::shared_ptr<_Scan> scan= location->search.lock();

	// Load the File
	std::shared_ptr<ResourceStream> resource = scan->search->load(location->location, filter->path, filename);
	if (! resource)
	{
		log_warn("File: ", filename.c_str(), ". Unable to load file, file doesn't exist");
		return nullptr;
	}

	return resource;
}