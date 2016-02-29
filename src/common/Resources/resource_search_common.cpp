#include "resource_search_common.h"

#include <fstream>
#include <algorithm>

#include <andromeda/Utilities/log.h>


#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "resource_stream_common.h"

using namespace andromeda;
using namespace boost;




/*

*/
CommonResourceScan::CommonResourceScan()
{

}


/*

*/
CommonResourceScan::~CommonResourceScan()
{

}


/*

*/
Boolean CommonResourceScan::search(const std::string & location,
	const std::string & localPath,
	const std::string & extension,
	std::vector<std::string> & files)
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




/*

*/
std::shared_ptr<ResourceStream> CommonResourceScan::load(const std::string & location,
	const std::string & localPath,
	const std::string & filename)
{
	// Build Filename
	std::string fullPath = location + "/" + localPath + "/" + filename;

	// Make a Resource Stream
	return std::make_shared<CommonResourceStream>(fullPath, true);
}