#pragma once

/*
	Bunch of basic conversion functions...

	TODO:
	Work out boost:lexical_cast<T> properly :/

	This is a temporary implementation until that works.... lolololol
*/

#include <string>

#include <andromeda/stddef.h>

#include <andromeda/exception.h>

namespace andromeda
{
	class BadConversionException : public virtual Exception
	{
	public:
		BadConversionException()
			: Exception("Bad Conversion")
		{

		}

		BadConversionException(const std::string & s)
			: Exception(s)
		{

		}

	};


	template <typename T>
	inline T convert(const std::string & s)
	{
		T t;
		
		throw BadConversionException("Unknown Type");

		return t;
	}

	template <>
	inline std::string convert<std::string>(const std::string & s)
	{
		return s;
	}


	template<>
	inline Float convert<Float>(const std::string & s)
	{
		return std::stof(s);
	}

	template<>
	inline Int32 convert<Int32>(const std::string & s)
	{
		return std::stoi(s, 0, 0);
	}

	template<>
	inline UInt32 convert<UInt32>(const std::string & s)
	{
		return  std::stoul(s, 0, 0);
	}
	
}
