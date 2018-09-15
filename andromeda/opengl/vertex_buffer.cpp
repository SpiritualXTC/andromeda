#include "vertex_buffer.h"

using namespace andromeda;
using namespace andromeda::opengl;


/*

*/
VertexBufferGL::VertexBufferGL()
{
	glGenBuffers(1, &_handle);
}


/*

*/
VertexBufferGL::~VertexBufferGL()
{
	if (_handle)
		glDeleteBuffers(1, &_handle);
}



/*

*/
void VertexBufferGL::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _handle);
}


/*

*/
void VertexBufferGL::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*

*/
void VertexBufferGL::data(const void * ptr, UInt32 length)
{
	assert(ptr);
	

	// Set Length
	_length = length;

	// Bind
	bind();

	// Allocate & Copy
	glBufferData(GL_ARRAY_BUFFER, _length, ptr, GL_STATIC_DRAW);

	// Unbind
	unbind();
}

/*

*/
void VertexBufferGL::subdata(const void * ptr, UInt32 offset, UInt32 length)
{
	assert(ptr);
	assert(offset + length <= _length);

	// Bind
	bind();

	// Copy
	glBufferSubData(GL_ARRAY_BUFFER, offset, length, ptr);

	// Unbind
	unbind();
}

