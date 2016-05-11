#pragma once

#include <memory>
#include <string>

namespace andromeda
{
	class File;
	class Texture;

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
}