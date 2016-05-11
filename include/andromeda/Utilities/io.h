#ifndef _ANDROMEDA_UTILITIES_IO_H_
#define _ANDROMEDA_UTILITIES_IO_H_

#include <string>

#include <andromeda/stddef.h>

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

#endif