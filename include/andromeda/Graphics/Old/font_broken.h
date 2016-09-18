#pragma once

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
	class Geometry;
	class MatrixStack;

	class IShader;
	class ITexture;

	/*
	This class is kinda broken :)

	TODO:
	- Replace it with FontType & FontVector and an interface

	- Rename to FontBroken :)
	- Move to deprecated folder -- however do not exclude the class ...
	*/
	class FontBroken
	{
	private:
		const static Int32 BMP_WIDTH = 2048;
		const static Int32 BMP_HEIGHT = 2048;




		// Information about a single Glyph
		struct _Glyph
		{
			_Glyph(UInt32 c)
				: code(c) {}

			const UInt32 code;

			Float advance;
			glm::fvec2 bearing;

			glm::fvec2 dimension;



			//	UInt32 offset;				// Offset of this character into the buffers
			//	glm::fvec2 position[4];		// Position Coordinates
			//	glm::fvec2 texture[4];		// Texture Coordinates
		};

		struct _Character
		{
			_Character(UInt32 c)
				: glyph(c) {}


			_Glyph glyph;
			std::shared_ptr<Geometry> geometry;
		};


	public:
		FontBroken(const std::string & font, Int32 size);
		virtual ~FontBroken();


		Float calcWidth(const std::string & string);

		/*
		Renders the Text
		*/
		void drawText(const std::shared_ptr<andromeda::IShader> shader, const std::string & string, andromeda::MatrixStack & ms);



		// TEMP
		//std::shared_ptr<Geometry> getGeometry(ULong character);





		// Rendering Specific :: Justify = 0.0 ???
		inline void setCharacterSpacing(Float spacing) { _spacing = spacing; }


	protected:
		Float drawCharacter(ULong character);

	private:
		Boolean loadFont(const std::string & font, Int32 size);
		Boolean loadChar(const FT_Face & fontFace, ULong charCode);

		std::unordered_map<ULong, _Character> _characters;

		std::shared_ptr<ITexture> _texture;



		Float _spacing = 0.0f;

		Float _lineGap = 0.0f;


		//	std::unordered_map<UInt32, _Glyph> _characterMap;

		//	std::unique_ptr<Texture> _texture;



		//	UInt32 _bitmap[BMP_HEIGHT][BMP_WIDTH];	//TEMPORARY
	};
}