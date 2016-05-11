#pragma once

#include <andromeda/stddef.h>

namespace andromeda
{
	typedef Int32 ResourceType;



	/*
		Counts the Resources
	*/
	class ResourceTypeCounter
	{
	public:
		static const inline ResourceType getResourceId()
		{
			return ++RESOURCE_TYPE_COUNTER;
		}

	private:
		static ResourceType RESOURCE_TYPE_COUNTER;

		ResourceTypeCounter() {}
		virtual ~ResourceTypeCounter() {}
	};




	/*
		Identifies the Resource
	*/
	template <typename RESOURCE_TYPE>
	class Resource
	{
	private:
		static const ResourceType RESOURCE_ID;

	public:
		static const inline ResourceType getResourceId() { return RESOURCE_ID; }




	/* Resource Interface - not sure if needed or not */
	public:
		Resource() {}
		virtual ~Resource() {}


	private:


	};

	template <typename RESOURCE_TYPE>
	const ResourceType Resource<RESOURCE_TYPE>::RESOURCE_ID = ResourceTypeCounter::getResourceId();
}