#include "resource_stream_common.h"

#include <andromeda/Utilities/log.h>

#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

using namespace andromeda;
using namespace boost;

/*

*/
CommonResourceStream::CommonResourceStream(std::string & fullPath, Boolean binary)
{


}

/*

*/
CommonResourceStream::~CommonResourceStream()
{
	close();
}

/*

*/
void CommonResourceStream::open(const std::string & fullPath, const Boolean binary)
{
	// Length of File [Required for Binary]
	_length = filesystem::file_size(fullPath);
	
	// Select Open Mode
	UInt mode = 0;

	_binary = binary;
	if (_binary)
		mode |= std::ios::binary;

	// Open File
	_file.open(fullPath, mode);
	if (!_file.is_open())
	{
		log_err("Unable to Open File");
		return;
	}
}


/*

*/
void CommonResourceStream::close()
{
	if (_file.is_open())
		_file.close();
}


/*

*/
void CommonResourceStream::begin()
{
	// Virtual Files require an offset
	// Virtual Files require bounds checking
	_file.seekg(std::ios::beg);
}

/*

*/
void CommonResourceStream::end()
{
	// Virtual Files require an offset
	// Virtual Files require bounds checking
	_file.seekg(std::ios::end);
}

/*

*/
void CommonResourceStream::seek(UInt64 pos)
{
	// Virtual Files require an offset
	// Virtual Files require bounds checking
	_file.seekg(pos, std::ios::beg);
}

/*

*/
UInt64 CommonResourceStream::tell()
{
	// Virtual Files will require an offset
	return _file.tellg();
}