#pragma once


#include <memory>
#include <string>

#include <andromeda/stddef.h>

/*
	TODO: 
	Remove the 'ex's'
*/

namespace andromeda
{
	class File;

	// Interface for Resource Loading
	class IFileLocation
	{
	public:
		virtual std::shared_ptr<File> loadFile(const std::string & filename, Bool binary) const = 0;
	};


	/*
		Resource Location is on the FileSystem
	*/
	class FileLocationFileSystem : public IFileLocation
	{
	public:
		FileLocationFileSystem(const std::string & directory)
			: _directory(directory)
		{

		}

		// Loads the File
		std::shared_ptr<File> loadFile(const std::string & filename, Bool binary) const override;


	private:
		std::string _directory;	// Directory of the Resources
	};
}