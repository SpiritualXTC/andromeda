#ifndef _ANDROMEDA_GRAPHICS_BUFFER_H_
#define _ANDROMEDA_GRAPHICS_BUFFER_H_

#include <andromeda/opengl.h>

namespace andromeda
{
	/*
	
	*/
	class Buffer
	{
	public:
		Buffer(GLenum buf_type);
		virtual ~Buffer();

		/*

		*/
		const inline GLuint handle() const { return _handle; }

		/*
		
		*/
		void bind();

		/*
		
		*/
		void unbind();

		/*
			
		*/
		void data(const GLvoid * ptr, const GLsizeiptr length);


		/*
		
		*/
		void subdata(const GLvoid * ptr, GLintptr offset, GLsizeiptr length);

	private:
		GLenum _type = GLU_UNKNOWN;
		GLuint _handle = 0;

		GLsizeiptr _length = 0;
	};





	/*
	
	*/
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer() : Buffer(GL_ARRAY_BUFFER){}
		virtual ~VertexBuffer(){}		
	};


	/*
	
	*/
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER){}
		virtual ~IndexBuffer() {}
	};
}

typedef andromeda::VertexBuffer aVertexBuffer;
typedef andromeda::IndexBuffer aIndexBuffer;

#endif