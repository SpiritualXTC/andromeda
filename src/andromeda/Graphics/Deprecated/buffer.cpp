#include <andromeda/Graphics/buffer.h>

#include <cassert>

using namespace andromeda;

#if 0
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

	_length = length;

	bind();

	glBufferData(_type, _length, ptr, GL_STATIC_DRAW);
	
	unbind();
}

/*

*/
void Buffer::subdata(const GLvoid * ptr, GLintptr offset, GLsizeiptr length)
{
	assert(ptr);
	assert(offset + length <= _length);

	bind();

	glBufferSubData(_type, offset, length, ptr);

	unbind();
}

#endif


