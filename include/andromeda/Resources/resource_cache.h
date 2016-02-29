#ifndef _ANDROMEDA_RESOURCE_CACHE_H_
#define _ANDROMEDA_RESOURCE_CACHE_H_


#include <andromeda/Engine/module.h>


namespace andromeda
{

	/*
		ResourceCache:

		Manages resources that have been loaded into memory or video memory
	*/
	class ResourceCache : public Module<ResourceCache>
	{
	public:
		ResourceCache();
		virtual ~ResourceCache();
	};

}


#endif
