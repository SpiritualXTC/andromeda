#include "index_buffer.h"

using namespace andromeda;
using namespace andromeda::opengl;


/*

*/
IndexBufferGL::IndexBufferGL()
{
	glGenBuffers(1, &_handle);
}


/*

*/
IndexBufferGL::~IndexBufferGL()
{
	if (_handle)
		glDeleteBuffers(1, &_handle);
}



/*

*/
void IndexBufferGL::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
}


/*

*/
void IndexBufferGL::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*

*/
void IndexBufferGL::data(const UInt32 * ptr, UInt32 length)
{
	assert(ptr);
	
	// Set Length
	_length = length;

	// Bind
	bind();

	// Allocate & Copy
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _length, ptr, GL_STATIC_DRAW);

	// Unbind
	unbind();
}

/*

*/
void IndexBufferGL::subdata(const UInt32 * ptr, UInt32 offset, UInt32 length)
{
	assert(ptr);
	assert(offset + length <= _length);

	// Bind
	bind();

	// Copy
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, ptr);

	// Unbind
	unbind();
}

