#include <andromeda/Utilities/io.h>

#include <fstream>
#include <sstream>
#include <assert.h>

/*
	LoadFile();

	Loads a Text File.

	Temporary!
*/
std::string andromeda::LoadFile(const std::string & filename)
{
	std::stringstream contents;
	
	// Open File
	std::ifstream file(filename);

	// Validate
	if (!file.is_open())
	{
		// Should be throwing an exception here!
		assert(false);
		return "";
	}

	

	// Load all of the file
	std::string line;
	while (std::getline(file, line))
	{
		contents << line << std::endl;
	}

	file.close();

	return contents.str();
}