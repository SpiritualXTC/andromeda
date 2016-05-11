#include <andromeda/Platform/file.h>

#include <fstream>
#include <sstream>

using namespace andromeda;


/*

*/
FileText::FileText(std::istream & stream)
	: FileText(stream, "")
{

}


/*

*/
FileText::FileText(std::istream & stream, const std::string & extension)
	: File(extension)
{
	std::stringstream contents;

	// Load all of the file
	std::string line;
	while (std::getline(stream, line))
	{
		contents << line << std::endl;
	}

	// Set Contents
	_contents = contents.str();
}
