#pragma once

#include <andromeda/stddef.h>

#include <andromeda/Utilities/log.h>

namespace andromeda
{
	typedef Int32 ResourceTypeId;



	/*
		Counts the Resources
	*/
	class ResourceTypeCounter
	{
	public:
		static const inline ResourceTypeId getResourceId()
		{
			return ++RESOURCE_TYPE_COUNTER;
		}

	private:
		static ResourceTypeId RESOURCE_TYPE_COUNTER;

		ResourceTypeCounter() {}
		virtual ~ResourceTypeCounter() {}
	};




	/*
		Sets up the ResourceType Identification
	*/
	template <typename RESOURCE_TYPE>
	class Resource
	{
	private:
		static const ResourceTypeId RESOURCE_ID;

	public:
		static const inline ResourceTypeId getResourceId() { return RESOURCE_ID; }




	/* Resource ! */
	private:
		Resource() {}
		virtual ~Resource() {}
	};

	template <typename RESOURCE_TYPE>
	const ResourceTypeId Resource<RESOURCE_TYPE>::RESOURCE_ID = ResourceTypeCounter::getResourceId();


	class IResourceType
	{
	public:
		IResourceType(const std::string & directory, UInt32 flags = 0)
			: _directory(directory)
			, _flags(flags)
		{

		}
		virtual ~IResourceType() {}

		/*
			getDirectory()
		*/
		const std::string & getDirectory() const { return _directory; }

		/*
			getFlags()
		*/
		UInt32 getFlags() const { return _flags; }

	private:
		UInt32 _flags = 0;
		std::string _directory;
	};







	/*
		TODO:
		Allow the cache to support multimap [multiple keys]
		When searching, grab the first, or the one specified by location

		Don't allow a resource to be cached
	*/


	/*
		ResourceCache:

		Manages resources that have been loaded into memory or video memory

		REPLACES ResourceManager::_resource;
	*/
	template <typename RESOURCE_TYPE>
	class ResourceType : public IResourceType
	{
	private:
		struct _Resource
		{
			std::string location;						// Location resource was loaded from
			std::shared_ptr<RESOURCE_TYPE> resource;	// Resource
		};

	public:
		ResourceType(const std::string & directory, UInt32 flags = 0)
			: IResourceType(directory, flags)
		{}

		virtual ~ResourceType() {}


		ResourceTypeId getResourceTypeId() const { return Resource<RESOURCE_TYPE>::getResourceId(); }



		/*
			Add Resource
		*/
		Boolean addResource(const std::string & id, const std::string & location, std::shared_ptr<RESOURCE_TYPE> & resource)
		{
			_Resource res;

			// Resource Exists
			if (hasResource(id))
				return false;

			res.location = location;
			res.resource = resource;

			_cache[id] = res;

			log_debugp("ResourceType :: Caching Resource :: Resource ID = %1%, Type = %2%", id, getResourceTypeId());

			return hasResource(id);
		}


		/*
			Has Resource
		*/
		Boolean hasResource(const std::string & id, const std::string & location = "")
		{
			const auto & it = _cache.find(id);

			/*
				Location is Empty ... any resource with that key

				Otherwise location & Key must match
			*/

			return it != _cache.end();
		}


		/*
			Get Resource
		*/
		std::shared_ptr<RESOURCE_TYPE> getResource(const std::string & id, const std::string & location = "")
		{
			// Find the Resource
			const auto & it = _cache.find(id);

			// No Results Found?
			if (it == _cache.end())
				return nullptr;

			/*
				TODO:
				Location Search:
				- First listed resource with matching key
				- The resource with matching key -- that also shares the location
			*/

			// Get Resource
			_Resource & res = it->second;

			log_debugp("ResourceType :: Resource in Cache :: Resource ID = %1%, Type = %2%", id, getResourceTypeId());

			return res.resource;
		}

	private:
		std::unordered_map<std::string, _Resource> _cache;
	};
}