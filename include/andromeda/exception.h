#ifndef _ANDROMEDA_EXCEPTION_H_
#define _ANDROMEDA_EXCEPTION_H_

#include <exception>
#include <string>

#include "stddef.h"


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
		Exception(const std::string & message) : _message(message)
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


#endif