#include <andromeda/Platform/file.h>

using namespace andromeda;



FileBinary::FileBinary(std::istream & stream)
	: FileBinary(stream, "", "")
{

}


/*

*/
FileBinary::FileBinary(std::istream & stream, const std::string & filename, const std::string & location)
	: File(filename, location)
	, _data(std::istreambuf_iterator<Char>(stream), std::istreambuf_iterator<Char>())
{
	// TODO: Make the _data() initialiser in the actual constructor...
	
}