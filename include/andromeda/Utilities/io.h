#pragma once 

#include <string>

#include <andromeda/stddef.h>

/*
	TODO:
	Move to Utilities/Util

	Place in the ::util namespace

	Lowercase the first letter
*/

namespace andromeda
{
	// Global Namespace I/O Functions
	// Mostly temporary :)

	// TODO: Remove Me [Maybe] :)
	std::string LoadFile(const std::string & filename);


	/*
	
	*/
	std::string GetDirectory(const std::string & filepath);

	/*
		Gets the Filename from a filepath
	*/
	std::string GetFilename(const std::string & filepath);

	/*
		Gets the Extension from a file
	*/
	std::string GetFileExtension(const std::string & filepath);
}
