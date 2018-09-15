#pragma once
/*
	Special class for indexing template classes :)

	This makes it easy to access different implementations of an interface, in a hashmap (for example)
*/


/*
	TODO:
	It appears as though some of the "special" class inheritance early classes went through to use the system wasn't even required ..... :S HAHAHAHAHAHAHAHAHAHAHAHA

	Clean it up :)

	2018:
	I don't even remember what the special class inheritance is.... 
*/

#include <cassert>

#include "types.h"

namespace andromeda
{
	typedef Int32 TemplateID;


	/*
		Increments a counter for all matching interfaces.

		For some reason... some arsehole has Macro Defined INTERFACE to something else. Stopping potential confusion and/or error before it becomes possible :)

		Indexes template classes by incrementing a counter, for the given interface.
		Classes that share an association with a common class/interface share a counter.
	*/
	template <typename _INTERFACE_>
	class TemplateIndexer
	{
	private:
		TemplateIndexer() {}
		virtual ~TemplateIndexer(){}

	public:
		// Generate a new Index
		static TemplateID generateTemplateId() { return ++_id; }

		/*
			Gets the Template ID for the association between the passed class and this counters interface.
		*/
		template <typename _CLASS_>
		static inline const TemplateID getTemplateId() { return TemplateIndex<_CLASS_, _INTERFACE_>::getTemplateId(); }

	private:
		static TemplateID _id;
	};
	template <typename _INTERFACE_>
	TemplateID TemplateIndexer<_INTERFACE_>::_id = 0;



	/*
		Handles the Automagically Identification of template classes that need to be accessed by ID
	*/
	template <typename _CLASS_, typename _INTERFACE_>
	class TemplateIndex
	{
	public:
		static inline const TemplateID getTemplateId() { return _templateId; }

	private:
		static const TemplateID _templateId;

	protected:
		// Should only be instantiated by derived classes :: Except that isn't even true :O
		TemplateIndex() { }
		virtual ~TemplateIndex(){}
	};

	template <typename _CLASS_, typename _INTERFACE_>
	const TemplateID TemplateIndex<_CLASS_, _INTERFACE_>::_templateId = TemplateIndexer<_INTERFACE_>::generateTemplateId();


	/*
		Gives a slightly less "human" error prone method for obtaining the Template ID


	*/
	template <typename _INTERFACE_>
	class TemplateContainer
	{
	public:
		template <typename _CLASS_>
		inline const TemplateID getTemplateId() const { return TemplateIndex<_CLASS_, _INTERFACE_>::getTemplateId(); }
	};
}

