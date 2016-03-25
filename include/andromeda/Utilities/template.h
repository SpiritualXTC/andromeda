#ifndef _ANDROMEDA_UTILITIES_TEMPLATE_H_
#define _ANDROMEDA_UTILITIES_TEMPLATE_H_

/*
	Special class for indexing template classes :)

	This makes it easy to access different implementations of an interface, in a hashmap (for example)
*/
#include <cassert>

#include <andromeda/stddef.h>

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
		Handles the Automagically Identification of template classes that need to be accessed by ID (eg: in a map)
	*/
	template <typename _CLASS_, typename _INTERFACE_>
	class TemplateIndex
	{
	public:
		static inline const TemplateID getTemplateId() { return _id; }

	private:
		static const TemplateID _id;

	protected:
		// Should only be instantiated by derived classes :: Except that isn't even true :O
		TemplateIndex() { }
		virtual ~TemplateIndex(){}
	};

	template <typename _CLASS_, typename _INTERFACE_>
	const TemplateID TemplateIndex<_CLASS_, _INTERFACE_>::_id = TemplateIndexer<_INTERFACE_>::generateTemplateId();




	/*
		Gives a slightly less "human" error prone method for obtaining the Template ID

		Might not need this class, if the generic template containers work :)
	*/
	template <typename _INTERFACE_>
	class TemplateContainer
	{
	public:
		template <typename _CLASS_>
		inline const TemplateID getTemplateId() const { return TemplateIndex<_CLASS_, _INTERFACE_>::getTemplateId(); }
	};
}



#endif