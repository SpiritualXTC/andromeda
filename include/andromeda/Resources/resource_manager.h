#ifndef _ANDROMEDA_RESOURCES_RESOURCE_MANAGER_H_
#define _ANDROMEDA_RESOURCES_RESOURCE_MANAGER_H_

/*
	Resource Management classes for maintaining a virtual file system 
	stored in various locations accessible by the engine.

	Resources can be stored on physical storage. (Win/*Nix/Mac)
	Stored in an APK (Android Only)
	Stored in a package file [.zip/.pak/etc] (Win/*Nix/Mac)

	iOS. No Idea how/where it stores resources/assets
*/

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <andromeda/stddef.h>

#include <andromeda/Utilities/singleton.h>

#include "resource_stream.h"

namespace andromeda
{

#if 0
	/*
		IResourceHandler:

		Event handler loading resources
		I DONT THINK THIS IS NEEDED AS THE RESOURCE MANAGER ONLY DEALS WITH POINTERS / REFERENCES!
		(Except in some scenerios....... Android)

		What this actually does, should be "elsewhere"

		This should probably also NOT be a ResourceStream, but a copy of the contents of hte file
	*/
	class IResourceHandler
	{
	public:
		IResourceHandler(){}
		virtual ~IResourceHandler() {}

		virtual void onStart(const Size bytes) = 0;
		virtual void onComplete(std::shared_ptr<ResourceStream> stream) = 0;
	};
#endif


	/*
		IResourceScan:

		Technique to use to navigate a virtual or physical file system to locate resources.
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
		ResourceManager:

		Caches a reference of all resources recognised by the engine, and a method to load
		the resource from numerous location
	*/
	class ResourceManager : public Singleton<ResourceManager>
	{
	private:
		struct _Scan
		{
			std::shared_ptr<IResourceScan> search;
		};

		struct _Location
		{
			std::string location;					// Root Location
			std::weak_ptr<_Scan> search;			// Method to search the location
		};

		struct _Filter
		{
			std::string path;						// Local Path
			std::string extension;					// Extension to load
		};

		struct _File
		{
			std::string filename;					// Filename only
			
			std::weak_ptr<_Location> location;		// Root Location
			std::weak_ptr<_Filter> filter;			// Local Path
		};



	public:
		ResourceManager();
		virtual ~ResourceManager();

		/*
			Resource Search Method
		*/
		void addSearch(std::shared_ptr<IResourceScan> search);

		/*
			Filter for supported filetypes
		*/
		void addFilter(const std::string & path, const std::string & extension);

		/*
			Add a location to search
		*/
		void addLocation(const std::string & location);

		/*
			Loads a File
		*/
		std::shared_ptr<ResourceStream> load(const std::string & filename);

	private:

		std::vector<std::shared_ptr<_Filter>> _filters;						// List of Supported Extensions
		std::vector<std::shared_ptr<_Location>> _location;					// List of Searched Locations

		std::unordered_map<std::string, std::shared_ptr<_Scan>> _search;


		std::unordered_map<std::string, std::shared_ptr<_File>> _files;	// Map of Filename <-> File Access

	};
}

#endif
