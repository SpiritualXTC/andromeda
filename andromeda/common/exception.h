#pragma once
#include <exception>
#include <string>

#include "types.h"


/*
	Base Exception Class for all of Andromeda!
*/
namespace andromeda
{
	class Exception : std::exception
	{
	public:

		/*
		
		*/
		Exception(const std::string & message) 
			: _message(message)
		{

		}


		/*
		
		*/
		const Char * what() const
		{
			return _message.c_str();
		}

	private:
		std::string _message;
	};

}
