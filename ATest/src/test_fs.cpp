#include "test_fs.h"

#include <fstream>

#include <algorithm>

#include <Windows.h>

#include <andromeda/Resources/resource_manager.h>
#include <andromeda/Utilities/log.h>



void testFS()
{
#if 0
	log_info("Test File System");


	andromeda::ResourceManager * fs = andromeda::ResourceManager::instance();


	// Add Search Paths & Filters
	fs->addFilter("shader", "fs");
	fs->addFilter("shader", "vs");
	fs->addFilter("shader", "gs");
	fs->addFilter("shader", "glslfx");

	fs->addFilter("textures", "png");

	// Add Search Locations
	fs->addLocation("../res");

	std::shared_ptr<andromeda::ResourceStream> stream = fs->load("particle_draw.gs");
#endif

	// Text Works. Binary not Implemented Yet
	//std::string contents = stream->read();
	//log_debug("Length:", contents.c_str());
}