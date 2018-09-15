#pragma once

#include <common/types.h>

namespace andromeda
{

	/*
		Buffer Interface
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
	class IVertexBuffer : public IBuffer
	{
	public:
		IVertexBuffer() {}
		virtual ~IVertexBuffer() {}

		virtual void data(const void* ptr, UInt32 length) = 0;
		virtual void subdata(const void* ptr, UInt32 offset, UInt32 length) = 0;
	};

	/*
		Index Buffer Interface
	*/
	class IIndexBuffer : public IBuffer
	{
	public:
		IIndexBuffer() {}
		virtual ~IIndexBuffer() {}
		
		virtual void data(const UInt32* ptr, UInt32 length) = 0;
		virtual void subdata(const UInt32* ptr, UInt32 offset, UInt32 length) = 0;
	};
}

//typedef andromeda::VertexBuffer aVertexBuffer;
//typedef andromeda::IndexBuffer aIndexBuffer;
