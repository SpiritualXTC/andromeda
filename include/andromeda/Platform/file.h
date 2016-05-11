#pragma once

/*
	Currently just a typedef for a vector, rather than a class of it's own.

	TODO: Make it a wrapper for a vector
*/

#include <memory>
#include <string>
#include <vector>

#include <istream>

#include <andromeda/stddef.h>

namespace andromeda
{
	//typedef std::vector<Char> FileBuffer;

#if 0
	/*
		Array of Bytes

		This could be done via a vector, but YOLO for now this will do :)
	*/
	class FileBuffer
	{
	public:
		FileBuffer();
		FileBuffer(Size len);
		FileBuffer(UChar * source, Size len);

		virtual ~FileBuffer();


		/*
			Get Size of Buffer
		*/
		const inline Size length() const { return _length; }


		/*
			Lock Existing Buffer
		*/
		UChar * lock() { return lock(0); }
		
		/*
			Lock New Buffer

			TODO: Their are no flags (yet)!
		*/
		UChar * lock(Size len, UInt32 flags = 0);



		void stream();

		/*
			Release Existing Data
		*/
		void release();

	private:
		void allocate(Size size);
		void deallocate();
		void copy(UChar * source, Size size);


		Size _length = 0;

		UChar * _bytes = nullptr;
	};
#endif


	/*
	
	*/
	class File
	{
	public:
		File(const std::string & extension)
			:_extension(extension)
		{

		}
		virtual ~File(){}

		/*
			Contents of the File
		*/
		virtual const inline Char * data() const = 0;

		/*
			Length of the File
		*/
		virtual const inline Size length() const = 0;

		/*
			Extension of the File :: Can be useful for loading resources 3rd party API's
		*/
		const inline std::string & extension() const { return _extension; }

	private:
		std::string _extension;
	};


	/*
	
	*/
	class FileBinary : public File
	{
	public:
		FileBinary(std::istream & stream);
		FileBinary(std::istream & stream, const std::string & extension);

		/*
			Get Data
		*/
		const inline Char * data() const override { return _data.data(); }

		/*
		
		*/
		const inline Size length() const override { return _data.size(); }

	private:
		std::vector<Char> _data;

	};


	/*
	
	*/
	class FileText : public File
	{
	public:

		FileText(std::istream & stream);
		FileText(std::istream & stream, const std::string & extension);

		/*
			Get Data
		*/
		const inline Char * data() const override { return _contents.c_str(); }


		/*
		
		*/
		const inline Size length() const override { return _contents.length(); }

	private:
		std::string _contents;
	};








	// These functions are defined in platform specific areas....
	std::shared_ptr<File> OpenFile(const std::string & filepath, Boolean binary);
}