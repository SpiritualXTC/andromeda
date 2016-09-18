#include "font_resource.h"

#include <andromeda/IO/file_location.h>

#include <andromeda/Utilities/font.h>
#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/Util/ptree_helper.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
std::shared_ptr<ResourceEx<Font, FontResourceArgs>> FontResourceBuilder::build(const boost::property_tree::ptree & propTree, const IFileLocation * location)
{
	// Get Args from Tree
	boost::optional<std::string> name = util::getChildValueOptional(propTree, "name");
	boost::optional<std::string> filename = util::getChildValueOptional(propTree, "filename");

	// Filename must be set
	if (!filename.is_initialized())
		return nullptr;

	log_debugp("FontResourceBuilder :: build() :: Creating Font Resource");
	log_tree();


	// Set the Name :: Strip the Filename for the name (Remove Slashes)
	if (!name.is_initialized())
		name = GetFilename(filename.get());


	// Create Resource
	auto resource = std::make_shared<FontResource>(name.get(), location);

	// Set Filename
	resource->setFilename(filename.get());

	return resource;
}


/*

*/
std::shared_ptr<Font> FontResourceBuilder::load(const FontResourceArgs & args, const IFileLocation * location)
{
	assert(location);

	/*
		TODO:
		Fonts cannot use the location system yet, as it's to slow loading the font into memory (for large fonts that contain all characters)
		Files will need to be restructured
	*/
	

	std::string fn = location->getLocation() + "/" + args.filename;

	log_debugp("Loading a Font : %1%", fn);

	// Currently the only way to create a font
	std::shared_ptr<Font> font = std::make_shared<Font>(fn);

	return font;
}
