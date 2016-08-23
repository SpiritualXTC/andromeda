#pragma once

#include <memory>
#include <string>

// Andromeda
#include "stddef.h"

namespace andromeda
{
	// Forward Declarations
	class Texture;
	class CubeTexture;
	class VolumeTexture;

	class Effect;


	struct CubeTextureLoadArgs;
	struct VolumeTextureLoadArgs;

	/*
		Loaders
	*/

	// Loads a Texture
	std::shared_ptr<Texture> LoadTexture(const std::string & filename, const std::string & locationName = "");

	// Loads a Cube Texture
	std::shared_ptr<CubeTexture> LoadCubeTexture(const std::string & name);

	// Loads a Volme Texture
	std::shared_ptr<VolumeTexture> LoadVolumeTexture(const std::string & alias, const VolumeTextureLoadArgs * args, const std::string & locationName = "");

	// Loads an Effect
	std::shared_ptr<Effect> LoadEffect(const std::string & filename, const std::string & locationName = "");
}