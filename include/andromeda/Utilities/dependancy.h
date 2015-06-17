#ifndef _ANDROMEDA_UTILITIES_DEPENDANCY_H_
#define _ANDROMEDA_UTILITIES_DEPENDANCY_H_

#include <unordered_map>
#include <memory>

#include "../stddef.h"

#include "template.h"
#include "log.h"

namespace andromeda
{
	/*
		
	*/
	template <class _CONCRETE_, class _INTERFACE_>
	class Dependancy : public TemplateID<_CONCRETE_, _INTERFACE_>
	{
	public:
		Dependancy() {}
		virtual ~Dependancy(){}

		/*
			Get Dependancy ID
		*/
		template <class T>
		inline Int32 getDependancyID() { return TemplateID<T, _INTERFACE_>::getTemplateID(); }
								
		
		/*
			Is it Dependant ?
		*/
		template <class T>
		inline Boolean isDependant() { return !_dependancies[getDependancyID<T>()].expired(); }

		/*
			Get Depandant RAW Pointer
		*/
		template <class T>
		T * getDependancy()
		{
			// Check for Expiration, and remove dependancy
			std::shared_ptr<_INTERFACE_> dependancy = getDependancyPtr<T>();
			
			// Return Pointer
			return ! dependancy ? nullptr : dependancy.get();
		}


		/*
			Get Dependant Pointer
		*/
		template <class T>
		std::shared_ptr<T> getDependancyPtr()
		{
			// Is it Dependant
			if (!isDependant<T>())
				return false;

			// Get Dependancy ID
			Int32 depId = getDependancyID<T>();

			// Check for Expiration, and remove dependancy
			std::weak_ptr<_INTERFACE_> dependancy = _dependancies[depId];

			// Return Shared Pointer
			return std::static_pointer_cast<T>(dependancy.lock());
		}

		/*

		*/
		template <class T>
		Boolean addDependancy(std::weak_ptr<_INTERFACE_> ptr)
		{
		//	assert(ptr);

			// No Pointer!
			if (ptr.expired()) return false;

			// Already Dependant ?
			if (isDependant<T>()) return false;

			// Get ID
			Int32 depId = getDependancyID<T>();

			// Assign
			_dependancies[depId] = ptr;

			return true;
		}


		/*

		*/
		template <class T>
		Boolean removeDependancy()
		{
			// Already Dependant ?
			if (!isDependant<T>())
				return false;

			// Erase
			_dependancies.erase(getDependancyID<T>());

			return true;
		}

	private:
		std::unordered_map<Int32, std::weak_ptr<_INTERFACE_>> _dependancies;
	};
}


#endif