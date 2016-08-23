#pragma once

/*
	Currently just a typedef for a vector, rather than a class of it's own.

	TODO: Make it a wrapper for a vector

	TODO: Move to Utilities
*/

#include <memory>
#include <string>
#include <vector>

#include <istream>

#include <andromeda/stddef.h>

namespace andromeda
{
	class IFileLocation;

	/*
	
	*/
	class File
	{
	public:
		static std::shared_ptr<File> OpenFile(const std::string & filename, Boolean binary);
		
	public:
		File(const std::string & filename);
		virtual ~File();

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

		/*
			
		*/
		const inline std::string & filename() const { return _filename; }

	private:
		std::string _extension;
		std::string _filename;
	};


	/*
	
	*/
	class FileBinary : public File
	{
	public:
		FileBinary(std::istream & stream);
		FileBinary(std::istream & stream, const std::string & filename);


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
		FileText(std::istream & stream, const std::string & filename);

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
}