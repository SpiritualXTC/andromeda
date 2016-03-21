#ifndef _ANDROMEDA_RESOURCE_CACHE_H_
#define _ANDROMEDA_RESOURCE_CACHE_H_

#include <unordered_map>
#include <andromeda/Engine/module.h>


namespace andromeda
{

	/*
		TEMPORARY
	*/
	class IResource
	{

	};


	/*
		ResourceCache:

		Manages resources that have been loaded into memory or video memory
	*/
	class ResourceCache : public Module<ResourceCache>
	{
	private:
		struct _Resource
		{
			std::shared_ptr<IResource> resource;
		};

	public:
		ResourceCache();
		virtual ~ResourceCache();


		template<class T>
		std::shared_ptr<T> getResource(const std::string & id)
		{
			if (_cache.find(id) != _cache.end())
			{
				// Resource Does Not Exist In Cache. Load it
			}


			// Get Resource
			_Resource & res = _cache[id];
		}


	private:
		std::unordered_map<std::string, _Resource> _cache;
	};

}


#endif
