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
	class Font;


	struct CubeTextureLoadArgs;
	struct VolumeTextureLoadArgs;

	/*
		Loaders
	*/

	// Loads a Texture
	std::shared_ptr<Texture> LoadTexture(const std::string & name);

	// Loads a Cube Texture
	std::shared_ptr<CubeTexture> LoadCubeTexture(const std::string & name);

	// Loads a Volme Texture
	std::shared_ptr<VolumeTexture> LoadVolumeTexture(const std::string & name);

	// Loads an Effect
	std::shared_ptr<Effect> LoadEffect(const std::string & name);

	// Loads a Font
	std::shared_ptr<Font> LoadFont(const std::string & name);
}