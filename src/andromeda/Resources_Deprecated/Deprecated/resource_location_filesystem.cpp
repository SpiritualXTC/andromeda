#include <andromeda/Resources/resource_location_filesystem.h>

#include <andromeda/IO/file.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace boost;

/*

*/
ResourceLocationFileSystem::ResourceLocationFileSystem(const std::string & location)
	: ResourceLocation(location)
{
	// TODO: Make sure location does NOT have trailing slash

}




/*

*/
std::shared_ptr<File> ResourceLocationFileSystem::load(const std::string & filename, Boolean binary)
{
	// Build Filepath
	std::string filepath = getLocation() + "/" + filename;

	return File::OpenFile(filepath, binary);
}