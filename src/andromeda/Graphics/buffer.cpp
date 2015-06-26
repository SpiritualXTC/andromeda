#include <andromeda/Graphics/buffer.h>

#include <cassert>

using namespace andromeda;


/*

*/
Buffer::Buffer(GLenum type) : _type(type)
{
	glGenBuffers(1, &_handle);
}


/*

*/
Buffer::~Buffer()
{
	if (_handle)
		glDeleteBuffers(1, &_handle);

}


/*

*/
void Buffer::bind()
{
	glBindBuffer(_type, _handle);
}


/*

*/
void Buffer::unbind()
{
	glBindBuffer(_type, 0);
}

/*

*/
void Buffer::data(const GLvoid * ptr, const GLsizeiptr length)
{
	assert(ptr);

	bind();

	glBufferData(_type, length, ptr, GL_STATIC_DRAW);

	unbind();
}






