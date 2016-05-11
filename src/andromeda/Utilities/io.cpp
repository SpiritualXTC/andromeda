#include <andromeda/Utilities/io.h>

#include <fstream>
#include <sstream>
#include <cassert>

using namespace andromeda;


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



/*

*/
std::string andromeda::GetDirectory(const std::string & filepath)
{
	// TODO: Allow both directions of slashes

	Size pos = filepath.find_last_of('/');

	if (pos != std::string::npos)
	{
		return filepath.substr(0, pos);
	}

	// No slashes? No Directory information
	return "";
}


/*

*/
std::string andromeda::GetFilename(const std::string & filepath)
{
	// TODO: Allow both directions of slashes

	Size pos = filepath.find_last_of('/');

	if (pos != std::string::npos)
	{
		return filepath.substr(pos + 1);
	}

	// No slashes? Assume it is only the filename
	return filepath;
}




/*

*/
std::string andromeda::GetFileExtension(const std::string & filepath)
{
	// Get Position of Dot
	Size pos = filepath.find_last_of('.');

	if (pos != std::string::npos)
	{
		return filepath.substr(pos + 1);
	}

	// No dot? No Extension
	return "";
}