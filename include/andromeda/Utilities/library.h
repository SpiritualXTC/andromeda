#pragma once

/*
	library.h:

	Libary Singleton Instance.
	Unlike normal singletons, libraries will be destroyed when the last reference is destroyed.
*/


#include <memory>

#include <andromeda/stddef.h>

/*
	TODO:
	Freetype should extend this library...
*/

namespace andromeda
{


	template <typename T>
	class Library
	{
	public:
		// STATIC FUNCTIONS
		static std::shared_ptr<T> loadLibrary()
		{
			// The library is still loaded.
			if (!_instance.expired())
			{
				return _instance.lock();
			}

			// Load Library
			std::shared_ptr<T> lib = std::make_shared<T>();

			// Assign Reference
			_instance = lib;

			return lib;
		}

	private:
		// STATIC MEMBERS

		// This allows the library to immediately clean itself up as soon as it moves beyond scope without manual intervention.
		// While also allowing shared reference of the library while its still loaded
		static std::weak_ptr<T> _instance;


	protected:
		Library(){}
		virtual ~Library(){}
	};


	// Initialise
	template<typename T>
	std::weak_ptr<T> Library<T>::_instance;
}