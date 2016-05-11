#include <andromeda/Platform/file.h>

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
std::shared_ptr<File> andromeda::OpenFile(const std::string & filepath, Boolean binary)
{
	log_infop("Common FS :: Load File: %1%", filepath);


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

	// Get Extension
	std::string extension = GetFileExtension(filepath);

	// Read File
	std::shared_ptr<File> f = nullptr;

	if (binary)
	{
		// Binary File
		f = std::make_shared<FileBinary>(file, extension);
	}
	else
	{
		// Text File
		f = std::make_shared<FileText>(file, extension);
	}

	
	// Close File
	file.close();

	return f;
}


#if 0

/*

*/
FileBuffer::FileBuffer()
{

}

FileBuffer::FileBuffer(Size len)
{
	// Allocate
	allocate(len);
}

FileBuffer::FileBuffer(UChar * source, Size len)
{
	// Allocate
	allocate(len);

	// Copy
	copy(source, len);
}



/*

*/
FileBuffer::~FileBuffer()
{
	deallocate();
}




void FileBuffer::allocate(Size len)
{
	deallocate();

	// Allocate
	_length = len;
	_bytes = new UChar[_length];
}

/*

*/
void FileBuffer::release()
{
	deallocate();
}

/*

*/
void FileBuffer::deallocate()
{
	if (_bytes != nullptr)
		delete[] _bytes;

	_bytes = nullptr;
	_length = 0;
}


/*
	TODO: Untested
*/
void FileBuffer::copy(UChar * source, Size len)
{
	assert(len == length());

	UChar * copy = lock();

	for (Int32 i = 0; i < len; ++i)
		*copy++ = *source++;
}



/*

*/
UChar * FileBuffer::lock(Size size, UInt32 flags)
{
	if (size != 0)
	{
		// Release Existing
		allocate(size);
	}

	// Validate
	assert(_bytes);

	// Return Buffer
	return _bytes;
}



#include <vector>
void FileBuffer::stream()
{
	
}


#endif