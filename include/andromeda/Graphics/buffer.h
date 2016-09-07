#pragma once
#include <andromeda/opengl.h>


#include <andromeda/stddef.h>

namespace andromeda
{

	/*
		Buffer Interface

		Should this be used?
	*/
	class IBuffer
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual UInt32 length() const = 0;
	};


	/*
		Vertex Buffer Interface
	*/
	class VertexBuffer : public IBuffer
	{
	public:
		VertexBuffer() {}
		virtual ~VertexBuffer() {}

	//	virtual void bind() = 0;
	//	virtual void unbind() = 0;
		
		/*
			TODO:
			Add some fixed-type passthru functions
		*/


		virtual void data(const void * ptr, UInt32 length) = 0;
		virtual void subdata(const void * ptr, UInt32 offset, UInt32 length) = 0;
	};

	/*
		Index Buffer Interface
	*/
	class IndexBuffer : public IBuffer
	{
	public:
		IndexBuffer() {}
		virtual ~IndexBuffer() {}

	//	virtual void bind() = 0;
	//	virtual void unbind() = 0;

		virtual void data(const UInt32 * ptr, UInt32 length) = 0;
		virtual void subdata(const UInt32 * ptr, UInt32 offset, UInt32 length) = 0;
	};
}

//typedef andromeda::VertexBuffer aVertexBuffer;
//typedef andromeda::IndexBuffer aIndexBuffer;
