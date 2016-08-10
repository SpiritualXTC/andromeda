#pragma once

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
#include "resource_type.h"

namespace andromeda
{




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
#if 1
		struct _Resource
		{
			std::string directory;
			UInt32 flags;
		};
#endif


	public:
		ResourceManager();
		virtual ~ResourceManager();

		/*
			Adds a resource type
		*/
		template <typename RESOURCE>
		Boolean addResourceType(const std::string & directory, UInt32 flags = ResourceManager::None);


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
		std::shared_ptr<RESOURCE> loadResourceAsync(const std::string & filename);



		/*
			Loads the Resource in-line.

			Loads a resource from the given filepath
			Loads from the FIRST Location found in the map
		*/
		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> loadResource(const std::string & filename, const std::string & locationName = "");

		/*
			Loads a Resource
		*/
		template <typename RESOURCE, typename ARGS>
		std::shared_ptr<RESOURCE> loadResource(const std::string & name, const ARGS * args, const std::string & locationName);

		/*
		
		*/
		template <typename RESOURCE>
		std::shared_ptr<File> loadResourceSupport(const std::string & filename, const std::string & locationName = "");

		/*
			Gets the Resource Directory
		*/
		template <typename RESOURCE>
		std::shared_ptr<ResourceType<RESOURCE>> getResourceType();


		



	private:

		/*
			Loads a File from the given path
			Loads from the FIRST Location found in the map or the LocationName
		*/
		std::shared_ptr<File> loadFile(const std::string & filepath, Boolean binary, const std::string & locationName = "");


		template <typename RESOURCE>
		inline ResourceTypeId getResourceTypeId() const
		{
			return Resource<RESOURCE>::getResourceId();
		}

		// Mapping :: ResourceType :: IResourceLoader :: All Built in Resources will have their loaded 
		// added by the engine during initialisation
		std::unordered_map<ResourceTypeId, std::shared_ptr<IResourceLoader>> _resourceLoader;


		// Mapping :: ResourceType :: ResourceDirectory
		std::unordered_map<ResourceTypeId, std::shared_ptr<IResourceType>> _resourceType;

		// Mapping :: locationName <-> ResourceLocation
		std::unordered_map<std::string, std::shared_ptr<ResourceLocation>> _location;


		// Mapping :: [<Resource>/]<filename> <-> FILEEX_STRUCTURE
		//std::unordered_multimap<std::string, std::shared_ptr<_FileEx>> _files;	// Map of Filename <-> File Access
	};






	/*
		Resource Loading ...

		TODO:
		This setup may lead to issues when it comes to loading custom types with the resource manager

		ands its highly unclean with a little too much coupling between the resource manager and the individual resources that needs to be loaded.
	*/
	class Effect;
	class Mesh;
	class Texture;
	class CubeTexture;
	class VolumeTexture;

	class FontFace;


	template<>
	std::shared_ptr<Effect> ResourceLoader::build<Effect>(std::shared_ptr<File> file);

	template<>
	std::shared_ptr<Mesh> ResourceLoader::build<Mesh>(std::shared_ptr<File> file);

	template<>
	std::shared_ptr<Texture> ResourceLoader::build<Texture>(std::shared_ptr<File> file);


	template<>
	std::shared_ptr<CubeTexture> ResourceBuilder::build<CubeTexture, CubeTextureLoadArgs>(const CubeTextureLoadArgs * args);


	/*
		TODO: Rename to Font when the class is done...ish
	*/
	template<>
	std::shared_ptr<FontFace> ResourceLoader::build<FontFace>(std::shared_ptr<File> file);
}

#include "resource_manager.hpp"



