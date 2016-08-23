#include <andromeda/IO/file.h>

#include <fstream>
#include <sstream>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
FileText::FileText(std::istream & stream)
	: FileText(stream, "")
{

}


/*

*/
FileText::FileText(std::istream & stream, const std::string & filename)
	: File(filename)
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
