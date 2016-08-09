#pragma once

namespace andromeda
{
	/*
	
	*/
	template <typename RESOURCE>
	Boolean ResourceManager::addResourceType(const std::string & directory, UInt32 flags)
	{
		// TODO: Make less "templatey"

		// Type Check is currently NOT required, as their as:
		// a) No Base Resource Type
		// b) No Requirement for a Base Resource Type :)
		//	static_assert(std::is_base_of<andromeda::Resource, RESOURCE>::value, "Resource is not a valid resource");

		// Get Resource ID
		//ResourceTypeId type = Resource<RESOURCE>::getResourceId();
		ResourceTypeId type = getResourceTypeId<RESOURCE>();

		// Add Resource
	//	_Resource res;
	//	res.directory = directory;
	//	res.flags = flags;

		std::shared_ptr<ResourceType<RESOURCE>> res = std::make_shared<ResourceType<RESOURCE>>(directory, flags);

		_resourceType[type] = std::static_pointer_cast<IResourceType>(res);

		log_infop("ResourceManager :: addResourceType() :: Type = %1%, Directory = %2%", type, directory);

		return false;
	}




	/*
	
	*/
	template <typename RESOURCE>
	std::shared_ptr<RESOURCE> ResourceManager::loadResourceAsync(const std::string & filename)
	{
		// First of all... SEARCH THE CACHE for the resource... it may have already been loaded!

		// If it isn't in the cache, then Load the Resource

		// Add to Loader :: This loads the resource in the background

		// Add to Cache ??

		return nullptr;
	}


	/*
	
	*/
	template <typename RESOURCE>
	std::shared_ptr<RESOURCE> ResourceManager::loadResource(const std::string & filename, const std::string & locationName)
	{
		// TODO: Make less "templatey"

		// Should it attempt to retrieve from the cache?

		// Search for FIRST reference that matches filename in the map
		// Search for ALL references that matches the filename in the map.
		// Search for the file that matches the location in the map

		// Get Resource Type
		std::shared_ptr<ResourceType<RESOURCE>> type = getResourceType<RESOURCE>();

		if (! type) return nullptr;

		// Look for the Resource in the Cache
		 std::shared_ptr<RESOURCE> resource = type->getResource(filename, locationName);

		if (resource) return resource;

		// Load the File
		std::shared_ptr<File> file = loadResourceSupport<RESOURCE>(filename, locationName);


		if (file == nullptr) return nullptr;

		// Process the File using the Resources Loading Mechanism
		ResourceLoader loader;
		resource = loader.build<RESOURCE>(file);

		// Add to Cache
		type->addResource(filename, locationName, resource);

		return resource;
	}



	/*
	
	*/
	template <typename RESOURCE, typename ARGS>
	std::shared_ptr<RESOURCE> ResourceManager::loadResource(const std::string & name, const ARGS * args, const std::string & locationName)
	{
		// Get Resource Type
		std::shared_ptr<ResourceType<RESOURCE>> type = getResourceType<RESOURCE>();

		if (!type) return nullptr;

		// Look for the Resource in the Cache
		std::shared_ptr<RESOURCE> resource = type->getResource(name, locationName);

		if (resource) return resource;

		// If we got this far, the resource doesn't exist and we don't have any information on how to load it.
		assert(args);

		// Build the Resource
		ResourceBuilder loader;
		resource = loader.build<RESOURCE, ARGS>(args);

		// Add to Cache
		type->addResource(name, locationName, resource);

		return resource;
	}



	/*
	
	*/
	template <typename RESOURCE>
	std::shared_ptr<File> ResourceManager::loadResourceSupport(const std::string & filename, const std::string & locationName)
	{
		/*
			Support Files would be loaded before or during the construction of a 
			resource (this includes the resource file as well, as external files)

			Therefore support files don't need to worry about being cached -- as the 
			resource they build is cached
		*/


		// Get ResourceType
		std::shared_ptr<ResourceType<RESOURCE>> type = getResourceType<RESOURCE>();

		

		std::string filepath = type->getDirectory() + "/" + filename;

		log_debugp("ResourceManager :: loadResourceSupport() :: %1%", filepath);


		// Binary or Text?
		Boolean binary = false;

		if (type->getFlags() & ResourceManager::Binary)
			binary = true;

		// Load the File
		return loadFile(filepath, binary, locationName);
	}





	/*

	*/
	template <typename RESOURCE>
	std::shared_ptr<ResourceType<RESOURCE>> ResourceManager::getResourceType()
	{
		// Get Resource Type
		ResourceTypeId type = getResourceTypeId<RESOURCE>();

		// Find Resource Type
		const auto it = _resourceType.find(type);

		if (it == _resourceType.end())
		{
			log_errp("ResourceManager :: getResourceDirectory() :: Invalid Resource Type [%1%]", type);
			throw ResourceException("Invalid Resource Type");
		}

	//	return it->second;
		return std::static_pointer_cast<ResourceType<RESOURCE>>(it->second);
	}



}
