#include <andromeda/IO/file_location.h>

#include <andromeda/IO/file.h>

using namespace andromeda;


/*

*/
std::shared_ptr<File> FileLocationFileSystem::loadFile(const std::string & filename, Bool binary) const
{
	std::string fn = _directory + "/" + filename;

	return File::OpenFile(fn, binary);
}