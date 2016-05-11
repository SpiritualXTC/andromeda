#include <andromeda/Platform/file.h>

using namespace andromeda;



FileBinary::FileBinary(std::istream & stream)
	: FileBinary(stream, "")
{

}


/*

*/
FileBinary::FileBinary(std::istream & stream, const std::string & extension)
	: File(extension)
	, _data(std::istreambuf_iterator<Char>(stream), std::istreambuf_iterator<Char>())
{

	
}