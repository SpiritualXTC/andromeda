#include <andromeda/Resources/resource_manager.h>

#include <cassert>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

using namespace andromeda;




/*
	Initialiser for ResourceType
*/
Int32 ResourceTypeCounter::RESOURCE_TYPE_COUNTER = 0;















/*

*/
ResourceManager::ResourceManager()
{

}


/*

*/
ResourceManager::~ResourceManager()
{

}




/*

*/
std::shared_ptr<File> ResourceManager::loadFile(const std::string & filepath, Boolean binary, const std::string & locationName)
{

	std::shared_ptr<File> buffer = nullptr;

	// Empty locationName == Use First Instance
	if (locationName == "")
	{
		// TODO: Implement & Search a master cache of files + where to load them

		// Loop through all locations until it is loaded
		for (const auto it : _location2)
		{
			// Attempt to load File
			buffer = it.second->load(filepath, binary);

			if (buffer != nullptr)
				break;
		}
	}
	else
	{
		// Search for the specific location
		const auto it = _location2.find(locationName);

		if (it == _location2.end())
		{
			// No Location Found
		}
		else
		{
			// Load File
			buffer = it->second->load(filepath, binary);
		}
	}

	return buffer;
}


