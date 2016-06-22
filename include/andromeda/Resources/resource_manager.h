#ifndef _ANDROMEDA_RESOURCES_RESOURCE_MANAGER_H_
#define _ANDROMEDA_RESOURCES_RESOURCE_MANAGER_H_

/*
	Resource Management classes for maintaining a virtual file system 
	stored in various locations accessible by the engine.

	Resources can be stored on physical storage. (Win/*Nix/Mac)
	Stored in an APK (Android Only)
	Stored in a package file [.zip/.pak/etc] (Win/*Nix/Mac)

	iOS. No Idea how/where it stores resources/assets



	Information:
	
	Format:
	<Location>/[<Resource>/]<filename>

	<Location>	: [Required]
				: Location where the resource can be loaded from : This is defined by the application
				: It can be a FileSystem, Packaged File, Network

	<Resource>	: [Optional]
				: Defined by the Resource Type
	
	<Filename>	: [Required]
				: Known Filetype



	Location:
	Multiple Locations can be specified.

	Files where [<Resource>/]filename match, the LATEST is used by default




	TODO:
	The current implementation is NOT very friendly when it concerns numerous locations.
	
	Some ResourceLocators, specifically ones that involve opening a packaged file should cache the files in the package

	A "master" cache of files would speed up access times
*/

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


#include <andromeda/exception.h>
#include <andromeda/stddef.h>

#include <andromeda/Platform/file.h>

#include <andromeda/Utilities/log.h>
#include <andromeda/Utilities/singleton.h>


#include "resource_loader.h"
#include "resource_stream.h"
#include "resource_type.h"

//#include "mesh_resource.h"

namespace andromeda
{

	/*
		DEPRECATED

		IResourceScan:

		Technique to use to navigate a virtual or physical file system to locate resources.

		TODO: Remove Meh, and anything that still uses it.
	*/
	class IResourceScan
	{
	public:
		IResourceScan() {}
		virtual ~IResourceScan() {}

		/*
			Load a resource
		*/
		virtual std::shared_ptr<ResourceStream> load(const std::string & location,
			const std::string & localPath,
			const std::string & filename) = 0;


		/*
			Search for resources in the specified location
		*/
		virtual Boolean search(const std::string & location,
			const std::string & localPath,
			const std::string & extension,
			std::vector<std::string> & files) = 0;
	};








	/*
		Resource Exception
	*/
	class ResourceException : public Exception
	{
	public:
		ResourceException(const std::string & message)
			: Exception(message)
		{
		}
	};





	/*
		ResourceLocation
	*/
	class ResourceLocation
	{
	public:
		ResourceLocation(const std::string & location)
			: _location(location)
		{

		}
		virtual ~ResourceLocation() {}

		const std::string & getLocation() const { return _location; }


		/*
			Loads the File
		*/
		virtual std::shared_ptr<File> load(const std::string & filename, Boolean binary) = 0;

	private:
		std::string _location;
	};



	/*
		ResourceManager:

		Caches a reference of all resources recognised by the engine, and a method to load
		the resource from numerous location

		This is NOT going to be a singleton!
	*/
	class ResourceManager
	{
	public:
		enum _ResourceFlags
		{
			None = 0x00,
			Binary = 0x01,
		};

	private:
		struct _Resource
		{
			std::string directory;
			UInt32 flags;
		};


	public:
		ResourceManager();
		virtual ~ResourceManager();


		/*
			Adds a resource type
		*/
		template <typename RESOURCE>
		Boolean addResourceType(const std::string & directory, UInt32 flags = ResourceManager::None)
		{
			// TODO: Make less "templatey"

			// This is currently NOT required, as their as:
			// a) No Base Resource Type
			// b) No Requirement for a Base Resource Type :)
		//	static_assert(std::is_base_of<andromeda::Resource, RESOURCE>::value, "Resource is not a valid resource");

			// Get Resource ID
			ResourceType type = Resource<RESOURCE>::getResourceId();

			// Add Resource
			_Resource res;
			res.directory = directory;
			res.flags = flags;

			_resourceType[type] = res;

			log_infop("ResourceManager :: addResourceType() :: Type = %1%, Directory = %2%", type, directory);

			return false;
		}



		/*
			Adds a Keyed Location
		*/
		Boolean addLocation(const std::string & name, std::shared_ptr<ResourceLocation> location);




		/*
			TODO: Setup an ASync Method for loading textures

			Gets a reference to the resource

			Returns a pointer to either:
			a) A pointer to a valid resource
			b) A pointer to a resource that hasn't been loaded yet
		*/
		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> loadResourceAsync(const std::string & filename)
		{
			// First of all... SEARCH THE CACHE for the resource... it may have already been loaded!

			// If it isn't in the cache, then Load the Resource

			// Add to Loader :: This loads the resource in the background

			// Add to Cache ??

			return nullptr;
		}



		/*
			Loads the Resource in-line.

			Loads a resource from the given filepath
			Loads from the FIRST Location found in the map
		*/
		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> loadResource(const std::string & filename, const std::string & locationName = "")
		{
			// TODO: Make less "templatey"

			// Should it attempt to retrieve from the cache?

			// Search for FIRST reference that matches filename in the map
			// Search for ALL references that matches the filename in the map.
			// Search for the file that matches the location in the map

			// Load the File
			std::shared_ptr<File> file = loadResourceSupport<RESOURCE>(filename, locationName);


			if (file == nullptr)
				return nullptr;

			// Process the File using the Resources Loading Mechanism
			ResourceLoader loader;
			std::shared_ptr<RESOURCE> resource = loader.build<RESOURCE>(file);


			return resource;
		}


		/*
		
		*/
		template <typename RESOURCE>
		std::shared_ptr<File> loadResourceSupport(const std::string & filename, const std::string & locationName = "")
		{
			// Get Resource ID
			const _Resource & res = getResourceType<RESOURCE>();

			std::string filepath = res.directory + "/" + filename;

			log_debugp("ResourceManager :: loadResource() :: %1%", filepath);


			// Binary or Text?
			Boolean binary = false;

			if (res.flags & ResourceManager::Binary)
				binary = true;

			// Load the File
			return loadFile(filepath, binary, locationName);
		}




		/*
			Loads a File from the given path
			Loads from the FIRST Location found in the map or the LocationName
		*/
		std::shared_ptr<File> loadFile(const std::string & filepath, Boolean binary, const std::string & locationName = "");


		/*
			Gets the Resource Directory
		*/
		template <typename RESOURCE>
		const _Resource & getResourceType();




	private:

		// Mapping :: ResourceType :: ResourceDirectory
		std::unordered_map<ResourceType, _Resource> _resourceType;

		// Mapping :: locationName <-> ILocator
		std::unordered_map<std::string, std::shared_ptr<ResourceLocation>> _location;


		// Mapping :: [<Resource>/]<filename> <-> FILEEX_STRUCTURE
		//std::unordered_multimap<std::string, std::shared_ptr<_FileEx>> _files;	// Map of Filename <-> File Access
	};




	/*
	
	*/
	template <typename RESOURCE>
	const ResourceManager::_Resource & ResourceManager::getResourceType()
	{
		// Get Resource Type
		ResourceType type = Resource<RESOURCE>::getResourceId();

		// Find Resource Type
		const auto it = _resourceType.find(type);

		if (it == _resourceType.end())
		{
			log_errp("ResourceManager :: getResourceDirectory() :: Invalid Resource Type [%1%]", type);
			throw ResourceException("Invalid Resource Type");
		}

		return it->second;
	}







	class Effect;
	class Mesh;
	class Texture;



	template<>
	std::shared_ptr<Effect> ResourceLoader::build<Effect>(std::shared_ptr<File> file);

	template<>
	std::shared_ptr<Mesh> ResourceLoader::build<Mesh>(std::shared_ptr<File> file);

	template<>
	std::shared_ptr<Texture> ResourceLoader::build<Texture>(std::shared_ptr<File> file);

}




#endif
