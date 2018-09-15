#pragma once

#include "types.h"

#include <string>
#include <typeinfo>

namespace andromeda
{
	typedef UInt64 ClassId;

	// TODO: Generic ClassID containers
	// unordered_map
	// unordered_set
	// unordered_multiset


	template <typename T>
	ClassId gen_hash()
	{
		// TODO: Could use the typeid(T) to generate a hash of the class name
		// TODO: Investigate later :)
		ClassId _hash = 0;

		return _hash;
	}

	ClassId generate();


	template <typename T>
	class IClass
	{
	public:

		static ClassId id()
		{
			return _id;
		}

		static std::string name()
		{
			return std::string(typeid((T).name()));
		}

	private:
		static UInt64 _id;

	};

	template <typename T>
	UInt64 IClass<T>::_id = generate();	//Magic id generator
}