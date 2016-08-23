#include <andromeda/Resources2/resource_factory.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


#include <andromeda/IO/file.h>
#include <andromeda/IO/file_location.h>

#include <andromeda/Utilities/log.h>

#include "resource_texture.h"
#include "resource_cube_texture.h"
#include "resource_volumetexture.h"

using namespace andromeda;


/*

*/
ResourceFactory::ResourceFactory()
{
	// Built in Resource Types
	registerBuilder<Texture, TextureResourceArgs>("texture", std::move(std::make_unique<TextureResourceBuilder>()));
	registerBuilder<CubeTexture, CubeTextureResourceArgs>("cubetexture", std::move(std::make_unique<CubeTextureResourceBuilder>()));
//	registerBuilder<VolumeTexture>("volumetexture", std::move(std::make_unique<VolumeTextureResourceBuilder>()));
}



/*

*/
ResourceFactory::~ResourceFactory()
{

}




/*
	Loads Resource File
*/
void ResourceFactory::loadResources(const std::string & location, const std::string & filename)
{
	log_debugp("ResourceFactory :: loadResources() :: Loading Resource XML. Location = %1%, File = %2%", location, filename);


	loadResources(filename, std::make_unique<FileLocationFileSystem>(location));
}


/*
	Loads Resource File
*/
void ResourceFactory::loadResources(const std::string & filename, std::unique_ptr<IFileLocation> && location)
{
	assert(location);

	// Load the Resource XML File
	std::shared_ptr<File> file = location->loadFile(filename, false);

	// Load the Resources XML
	loadResources(file.get(), location.get());

	// Add to List
	_locations.push_back(std::move(location));
}









/*
	Loads the Resource XML File
*/
void ResourceFactory::loadResources(const File * file, const IFileLocation * location)
{
	if (!file || !location)
		throw ResourceExceptionEx("File Error");



	log_debugp("ResourceFactory :: loadResources() :: Loading Resource XML");
	log_tree();

	std::stringstream stream(file->data());



	boost::property_tree::ptree pt;

	// TODO: Choose between XML or JSON parsers
	// Parse XML
	boost::property_tree::read_xml(stream, pt);

	// Get Root Node
	boost::property_tree::ptree & root = pt.get_child("resources");

	// Parse
	for (const auto & n : root)
	{
		const std::string & element = n.first;

		
		const auto & it = _map.find(element);

		log_debugp("ResourceFactory :: loadResources() :: Found Resource Type = %1%", element);

		// Add Resource
		if (it != _map.end())
		{
			TemplateID key = it->second;

			// Search for the Container with this element name
			const auto & res = _resources.find(key);
			
			if (res != _resources.end())
				res->second->addResource(n.second, location);
		}
	}
}



