#ifndef _ANDROMEDA_UTILITIES_TEMPLATE_H_
#define _ANDROMEDA_UTILITIES_TEMPLATE_H_

/*
	Special class for indexing template classes :)

	This makes it easy to access different implementations of an interface, in a map (for example)
*/


#include <andromeda/stddef.h>

namespace andromeda
{
	/*
		Increments a counter of all matching interfaces.

		For some reason... some arsehole as Macro Defined INTERFACE to something else. Stopping potential confusion and/or error before it becomes possible :)
	*/
	template <typename _INTERFACE_>
	class TemplateIdentifier
	{
	private:
		TemplateIdentifier() {}
		virtual ~TemplateIdentifier(){}

	public:
		// Generate the Index
		static Int32 generateTemplateID() { return ++_id; }


		// This should work now!
		template <typename _CONCRETE_>
		static inline Int32 getTemplateID() { return TemplateID<_CONCRETE_, _INTERFACE_>::getTemplateID(); }

	private:
		static Int32 _id;
	};
	template <typename _INTERFACE_>
	Int32 TemplateIdentifier<_INTERFACE_>::_id = 0;



	/*
		Handles the Automagically Identification of template classes that need to be accessed by ID (eg: in a map)
	*/
	template <typename _CLASS_, typename _INTERFACE_>
	class TemplateID
	{
	public:
		static inline const Int32 getTemplateID() { return _id; }

	private:
		static const Int32 _id;

	protected:
		// Should only be instantiated by derived classes.
		TemplateID() {}
		virtual ~TemplateID(){}
	};

	template <typename _CLASS_, typename _INTERFACE_>
	const Int32 TemplateID<_CLASS_, _INTERFACE_>::_id = TemplateIdentifier<_INTERFACE_>::generateTemplateID();
}



#endif