#include <andromeda/resources.h>

#include <andromeda/andromeda.h>
#include <andromeda/Resources/resource_manager.h>

using namespace andromeda;






// Loads a Texture
std::shared_ptr<Texture> andromeda::LoadTexture(const std::string & filename, const std::string & locationName)
{
	return andromeda::resources()->loadResource<Texture>(filename);
}


// Loads a Cube Texture
std::shared_ptr<CubeTexture> andromeda::LoadCubeTexture(const std::string & alias, const CubeTextureLoadArgs * args, const std::string & locationName)
{

	return nullptr;
}


// Loads a Volume Texture
std::shared_ptr<VolumeTexture> andromeda::LoadVolumeTexture(const std::string & alias, const VolumeTextureLoadArgs * args, const std::string & locationName)
{

	return nullptr;
}


// Loads an Effect
std::shared_ptr<Effect> andromeda::LoadEffect(const std::string & filename, const std::string & locationName)
{
	return andromeda::resources()->loadResource<Effect>(filename);
}