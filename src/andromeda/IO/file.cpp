#include <andromeda/IO/file.h>
#include <andromeda/IO/file_location.h>

#include <cassert>


#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace boost;


/*

*/
std::shared_ptr<File> File::OpenFile(const std::string & filepath, Boolean binary)
{
	log_infop("File :: Load File() :: Filename = %1%, Binary = %2%", filepath, binary);


	// Validate if File Exists
	if (!filesystem::exists(filepath))
		return nullptr;

	// Select Open Mode
	UInt mode = 0;	// Read Mode ???
	
	if (binary)
		mode |= std::ios::binary;

	// Open File
	std::ifstream file(filepath, mode);

	// Is the File Open ?
	if (!file.is_open())
		return nullptr;

	// Read File
	std::shared_ptr<File> f = nullptr;

	if (binary)
	{
		// Binary File
		f = std::make_shared<FileBinary>(file, filepath);
	}
	else
	{
		// Text File
		f = std::make_shared<FileText>(file, filepath);
	}

	// Close File
	file.close();

	return f;
}









/*

*/
File::File(const std::string & filename)
	: _filename(filename)
{
	// Get File Extension
	_extension = GetFileExtension(_filename);
}

/*

*/
File::~File()
{


}