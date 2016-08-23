#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <andromeda/exception.h>
#include <andromeda/stddef.h>

#include <andromeda/Utilities/log.h>
#include <andromeda/Utilities/template.h>

#include "resource_builder.h"
#include "resource_map.h"

namespace andromeda
{
	class File;

	class IFileLocation;









	// Yep Something went wrong!
	class ResourceExceptionEx : Exception
	{
	public:
		ResourceExceptionEx() : Exception("Error in Resource Management"){}
		ResourceExceptionEx(const std::string & what) : Exception(what) {}
	};







	// Central point for loading all resources
	class ResourceFactory : public TemplateContainer<IResourceMap>
	{
	public:
		ResourceFactory();
		virtual ~ResourceFactory();

		/*
			Registers a Builder :: This is what allows a resource to be loaded via XML
		*/
		template <typename RESOURCE, typename ARGS>
		void registerBuilder(const std::string & name, std::unique_ptr<ResourceBuilderEx<RESOURCE, ARGS>> && builder)
		{
			std::unique_ptr<IResourceMap> rc = std::make_unique<ResourceMap<RESOURCE, ARGS>>(std::move(builder));

			TemplateID tempId = getTemplateId<RESOURCE>();

			log_debugp("ResourceFactory :: Register Builder :: Name = %1%, ResourceID = %2%", name, tempId);

			_map.insert({ name, tempId });
			_resources.insert({ tempId, std::move(rc) });
		}

	
		/*
			Make this return a raw pointer...
		*/
		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> getResource(const std::string & name)
		{
			TemplateID tempId = getTemplateId<RESOURCE>();

			log_debugp("ResourceFactory :: Get Resource :: Name = %1%", name);
			log_tree();
			log_verbosep("Resource Type = %1%", tempId);


			// Find the Resource Map
			const auto & it = _resources.find(tempId);

			
			if (it == _resources.end())
				throw ResourceExceptionEx("Unknown Resource Type");

			// Get The Resource Container
			AResourceMap<RESOURCE> * rc = static_cast<AResourceMap<RESOURCE>*>(it->second.get());

			if (! rc)
				throw ResourceExceptionEx("Invalid Resource Type");

			// Get the Actual Resource
			std::shared_ptr<RESOURCE> r = rc->getResource(name);


			// Temp Validation
			if (! r)
				log_verbosep("Unable to Acquire Resource");
			else
				log_verbosep("Resource Aquired");

			return r; 
		}








		// Load the Resourcec XML File [Located on the FileSystem]
		void loadResources(const std::string & location, const std::string & filename); // 'loadMethod' :: This abstracts the method required to load the XML file. Such as from Disk, or from a Compressed Package. Null assumes FileSystem (?)

		// Load the Resource XML File [Located in a Package File, such as .zip/.pak]
		void loadResources(const std::string & filename, std::unique_ptr<IFileLocation> && locator);


	protected:
		void loadResources(const File * file, const IFileLocation * location);



	private:


		
		//std::unordered_map<std::string, std::unique_ptr<IResourceContainer>> _resources;
		std::unordered_map<std::string, TemplateID> _map;
		
		std::unordered_map<TemplateID, std::unique_ptr<IResourceMap>> _resources;



		// Maintains the list of FileLocation references
		std::vector<std::unique_ptr<IFileLocation>> _locations;	
	};

	







	/*
		TODO:
		Pimple the ResourceFactory behind another class aka ResourceManager :)

		This will hide the additional classes from even being forward declared...
	*/
	namespace TEMP
	{
		class ResourceManager
		{
		public:

		private:

			class Factory;	// This is the Resource Factory Above
			std::unique_ptr<Factory> _factory;
		};

	}
}