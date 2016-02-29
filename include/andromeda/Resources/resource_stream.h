#ifndef _ANDROMEDA_RESOURCES_RESOURCE_STREAM_H_
#define _ANDROMEDA_RESOURCES_RESOURCE_STREAM_H_

#include <string>

#include <andromeda/stddef.h>


namespace andromeda
{
	/*	
		FileStream: [Abstract]
	
		Platform-Independant File Stream.
		Most Implementations of FileStream will be common, and will only provide a wrapper for ifstream.
		Then there is Android.................
	*/
	class ResourceStream
	{
	public:
		ResourceStream() {}
		virtual ~ResourceStream(){}

		/*
			Is the stream textual or binary?
		*/
		const virtual Boolean isBinary() const = 0;

		/*
			Is the File Open
		*/
		virtual const Boolean isOpen() const = 0;

		/*
			Virtual Files are files that exist "inside" a packaged file, such as ".zip"
			A Virtual FileStream may allocate its own memory (such as a compressed file)
			OR it may artificially lock the position range between it's own begin & end positions

			Virtual Files are currently not supported :)
		*/
//		const virtual Boolean isVirtual() = 0;


		/*
			Open the File
		*/
		virtual void open(const std::string & filename, const Boolean binary) = 0;

		/*
			Close the File
		*/
		virtual void close() = 0;

		/*
			Seek to Beginning of Stream
		*/
		virtual void begin() = 0;

		/*
			Seek to End of Stream
		*/
		virtual void end() = 0;

		/*
			Get Current Position in Stream
		*/
		virtual UInt64 tell() = 0;

		/*
			Set Current Position in Stream
		*/
		virtual void seek(UInt64 pos) = 0;

		/*
			Get Length of Stream
		*/
		virtual const UInt64 length() const = 0;

	private:
		
	};
}

#endif
