#include "test_fs.h"

#include <fstream>

#include <algorithm>

#include <Windows.h>

#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/log.h>



#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

using namespace boost;


#if 0
class FileSearch : public andromeda::IFileSearch
{
public:

	/*
		search():

		Search a windows directory
	*/
	virtual aBoolean search(const std::string & location,
		const std::string & filterPath,
		const std::string & extension,
		std::vector<std::string> & files)
		override
	{
		WIN32_FIND_DATAA data;

		std::string filter = location + "/" + filterPath + "/*." + extension;

		log_info("Path:", filter.c_str());


		// Open Handle
		HANDLE h = FindFirstFileA(filter.c_str(), &data);


		// Validation
		if (h != INVALID_HANDLE_VALUE)
		{
			do
			{
				// Validate Extension (Ignore for now)
				//std::string fn = data.cFileName;

				files.push_back(data.cFileName);

				// Next
			} while (FindNextFileA(h, &data));

			// Close Handle
			FindClose(h);
		}
		else
		{
			log_err("Invalid Handle");
			return false;
		}

		return true;
	}


	/*
		load():

		Loads a File in Windows
	*/
	std::shared_ptr<andromeda::FileStream> load(const std::string & location,
		const std::string & path,
		const std::string & filename) override
	{
		// Build Filename
		std::string fullPath = location + "/" + path + "/" + filename;

		log_info("Loading File:", fullPath.c_str());


		// Get Stats for File
		struct stat fileInfo;
		int rc = stat(fullPath.c_str(), &fileInfo);

		if (rc != 0)
		{
			log_err("Invalid file");
			return false;
		}
		else
			log_debug(fileInfo.st_size);

		// Length of File
		long length = fileInfo.st_size;

		// Open File [Required for Binary and Text]
		std::ifstream file(fullPath, std::ios::binary);
		if (!file.is_open())
		{
			log_err("Unable to open file");
			return false;
		}


#if 0
		// Read Entire File
		aChar * buffer = new aChar[length];

		//std::stream



		// OLD SCHOOL METHOD

		// Open File
		FILE * file = nullptr;
		aError err = fopen_s(&file, fullPath.c_str(), "rb");
		
		if (err != 0 || file == nullptr)
			return false;

		// Test Length of File
		fseek(file, 0, SEEK_END);
		aLong length = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		log_debug("File: Length =", length);


		// Allocate Data
		aChar * buffer = new aChar[length];
		aSize read = fread((void*)buffer, 1, length, file);

		

		// Copy
		data.reserve(length);

		log_debug("File: Length =", length, "Read =", read, "Capacity =", data.capacity());


		for (aUInt32 i = 0; i < data.capacity(); ++i)
			data.emplace(data.begin() + i, buffer[i]);
			//data[i] = buffer[i];
		

		// Deallocate
		delete[] buffer;
		
		if (read != length)
		{
			log_warn("Warning: Unexpected number of characters read");
		}


		// Close File
		fclose(file);
#endif
		return nullptr;
	}

};






class BoostFileSearch : public andromeda::IFileSearch
{
public:
	virtual aBoolean search(const std::string & location,
		const std::string & localPath,
		const std::string & extension,
		std::vector<std::string> & files)
		override
	{
		// Path of Directory
		filesystem::path path(location + "/" + localPath);

		try
		{
			// Validate Path
			if (!filesystem::exists(path))
			{
				log_warn("Path doesn't exist");
				return false;
			}

			// Validate Directory
			if (!filesystem::is_directory(path))
			{
				log_warn("Not a Directory");
				return false;
			}


			// Setup Regex
			std::string s = ".*\\." + extension;
			const boost::regex filter(s);

			// Iterate over directory
			filesystem::directory_iterator dir_end;
			for (boost::filesystem::directory_iterator it(path); it != dir_end; ++it)
			{
				// Skip Directories
				if (!filesystem::is_regular_file(it->status()))
					continue;

				// Filename Only
				std::string s = it->path().filename().string();

				// Extension match?
				boost::smatch what;
				if (!boost::regex_match(s, what, filter))
					continue;
	
				// Add matching File
				files.push_back(s);
			}
		}
		catch (const filesystem::filesystem_error& ex)
		{
			log_err(ex.what());
			return false;
		}
		catch (const boost::regex_error &ex)
		{
			log_err(ex.what());
			return false;
		}

		return true;
	}


	std::shared_ptr<andromeda::FileStream> load(const std::string & location,
		const std::string & path,
		const std::string & filename) override
	{
		// Build Filename
		std::string fullPath = location + "/" + path + "/" + filename;

		// Length of File [Required for Binary]
		aInt64 length = filesystem::file_size(fullPath);

		// Open File [Required for Binary and Text]
		std::ifstream file(fullPath, std::ios::binary);
		if (!file.is_open())
		{
			log_err("Unable to open file");
			return nullptr;
		}
		
		




		/*
			Remove everything except the close
		*/

		
		aUInt len = (aUInt)length;

		// Allocate Memory
		aChar * buffer = new aChar[len];
		file.read(buffer, length);

		log_debug(buffer);

		delete[] buffer;

		file.close();


		return nullptr;
	}
};


#endif




void testFS()
{
	log_info("Test File System");


	andromeda::ResourceManager * fs = andromeda::ResourceManager::instance();


	//std::shared_ptr<FileSearch> search = std::make_shared<FileSearch>();
	// This needs to be added during the platform specific load
	



	fs->addFilter("shader", "fs");
	fs->addFilter("shader", "vs");
	fs->addFilter("shader", "gs");

	fs->addFilter("textures", "png");

	// Windows : This needs to be added without knowledge of the search method
	fs->addLocation("../res");
	fs->addLocation("../res/test");

	std::shared_ptr<andromeda::ResourceStream> stream = fs->load("particle_draw.gs");

	//log_debug("Length:", data.capacity());
}