#pragma once

#if 0
#include <memory>
#include <string>

#include <andromeda/stddef.h>

namespace andromeda
{
	class File;
	class Texture;

	/*
		Loads a Texture
	*/
	class TextureLoader
	{
	public:
		TextureLoader(const std::string & filename);
		TextureLoader(const std::shared_ptr<File> & file);
		virtual ~TextureLoader();



		/* Get Texture */
		const std::shared_ptr<Texture> & getTexture() const { return _texture; }

	private:



		std::shared_ptr<Texture> _texture;
	};
	

//	template<>
//	std::shared_ptr<Texture> ResourceLoader::build<Texture>(std::shared_ptr<File> file);
}
#endif