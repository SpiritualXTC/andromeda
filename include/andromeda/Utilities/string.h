#pragma once

/*
	Complete listing of all toString() functions

	TODO: 
	- Should support std::string & std::wstring (return std::basic_string<C>)
	- An Interface that a class could implement (Java Style)
		- Will require a template function all its own

	- Primitives (Maybe)
	- Common GLM types

	Required By:
	- Logger
	- Text Conversions
*/

namespace andromeda
{
	template <typename T>
	std::wstring toString(const T & t)
	{
		return "";
	}

	template <typename T>
	inline std::wstring toString(const T * const t)
	{
		return toString(*t);
	}
}
