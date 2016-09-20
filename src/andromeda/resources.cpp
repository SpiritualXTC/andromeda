#include <andromeda/resources.h>

#include <andromeda/andromeda.h>

#include <andromeda/Resources/resource_factory.h>

using namespace andromeda;






// Loads a Texture
std::shared_ptr<Texture> andromeda::LoadTexture(const std::string & name)
{
	return andromeda::resourceFactory()->getResource<Texture>(name);
}


// Loads a Cube Texture
std::shared_ptr<CubeTexture> andromeda::LoadCubeTexture(const std::string & name)
{
	return andromeda::resourceFactory()->getResource<CubeTexture>(name);
}


// Loads a Volume Texture
std::shared_ptr<VolumeTexture> andromeda::LoadVolumeTexture(const std::string & name)
{
	return nullptr;
}



// Loads an Effect
std::shared_ptr<Effect> andromeda::LoadEffect(const std::string & name)
{
	return andromeda::resourceFactory()->getResource<Effect>(name);
}


// Loads a Font
std::shared_ptr<Font> andromeda::LoadFont(const std::string & name)
{
	return andromeda::resourceFactory()->getResource<Font>(name);
}