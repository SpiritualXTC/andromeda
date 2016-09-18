#pragma once

#include <cassert>
#include <functional>
#include <memory>

#include <boost/optional.hpp>

#include <andromeda/stddef.h>

namespace andromeda
{
	class IFileLocation;

	template <typename RESOURCE, typename ARGS>
	class ResourceBuilderEx;



	/*
		ResourceEx
		Container for a Resource

		TODO: 
			Remove the old resource management system
			Rename to Resource	
	*/
	template <typename RESOURCE, typename ARGS>
	class ResourceEx //: virtual public RESOURCE
	{
	public:
		ResourceEx(const std::string & name, const IFileLocation * location)
			: _name(name)
			, _location(location)
		{

		}

		// Gets the Name of the Resource
		inline const std::string & getName() const { return _name; }


		inline const Boolean isAvailable() const { return !!_resource; }


		/*
			Acquire the Resource
		*/
		std::shared_ptr<RESOURCE> acquire(ResourceBuilderEx<RESOURCE, ARGS> * builder)
		{
			assert(builder);

			// Is the resource loaded
			// This can allow for preloading
			if (! _resource)
			{
				//_resource = std::move(builder->load(_args, _location));
				_resource = builder->load(getArgs(), _location);
			}


			// Increase Reference Counter
			++_refCounter;

			return std::shared_ptr<RESOURCE>(_resource.get(), std::bind(&ResourceEx::release, this, std::placeholders::_1));
		}


		/*
			Release the Resource
		*/
		void release(RESOURCE * r)// override
		{
			// Decrease Reference Counter
			--_refCounter;

			// Resource is still referenced?
			// TODO: Add ability to preload. 
			// This however may not be needed , as preloading should be achievable without "acquiring"
			// Hence the reference counter will remain @ 0
			if (_refCounter == 0)
			{
				_resource = nullptr;
			}
		}







	protected:
		// Get RAW Pointer to the resource :: This shouldn't be needed now :)
		inline RESOURCE * getResource() { return _resource.get(); }
		const inline RESOURCE * getResource() const { return _resource.get(); }


		// Get Args
		virtual const inline ARGS & getArgs() const = 0;

	private:
		// Name of the resource
		std::string _name;

		// Number of times the resource has been acquired
		Int32 _refCounter = 0;

		// Location where the resource is stored
		const IFileLocation * _location;

		// Actual Resource
		std::shared_ptr<RESOURCE> _resource;
	};






}