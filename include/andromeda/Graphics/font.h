#ifndef _ANDROMEDA_GRAPHICS_FONT_H_
#define _ANDROMEDA_GRAPHICS_FONT_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>


// Not Sure which is better .... 
// Really dont wont FreeType poluting the global namespace :(
// Maybe place b/w a wrapper? (Deal with later) :)
#include <ft2build.h>
#include FT_FREETYPE_H



namespace andromeda
{
	class Texture;

	class Font
	{
	private:
		const static Int32 BMP_WIDTH = 2048;
		const static Int32 BMP_HEIGHT = 2048;

		class _FontLibrary
		{
		// Singleton Class that Handles loading the FreeType Library

		};

		// Information about a single Glyph
		struct _Glyph
		{
			_Glyph(UInt32 c)
				: code(c){}

			const UInt32 code;

			Int32 advance;
			glm::ivec2 bearing;
			
			glm::ivec2 dimension;



			UInt32 offset;				// Offset of this character into the buffers
			glm::fvec2 position[4];		// Position Coordinates
			glm::fvec2 texture[4];		// Texture Coordinates
		};


	public:
		Font(const std::string & font, Int32 size);
		virtual ~Font();


		Float calcWidth(const std::string & string);

		/*
			Renders the Text
		*/
		void render(const std::string & string);

	private:
		Boolean loadFont(const std::string & font, Int32 size);
		Boolean loadChar(const FT_Face & fontFace, ULong charCode);


		std::unordered_map<UInt32, _Glyph> _characterMap;

		std::unique_ptr<Texture> _texture;



		UInt32 _bitmap[BMP_HEIGHT][BMP_WIDTH];	//TEMPORARY

	};
}


#endif
