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

/*
	Make the Font Class purely to load freetype fonts.

	Allow it to load the fonts, and export:
	a) Font Atlas
	b) Font Vectors
*/




namespace andromeda
{
	class IShader;
	class ITexture;


	class Geometry;
	class MatrixStack;
	class Texture;
	class TextEx;

	class Font;

	struct GlyphMetric;



	/*
		Interface for text drawing

		There will be 3 main methods for drawing text.

		Static and Dynamic.

		Static can done by:
		- Bezier Curves	(Static or Dynamic)
			Static: The entire string is prebuilt into a single Geometry object, and then its just drawn with a single call.
			Dynamic: Each character is prebuilt with it's own geometry object. Each character is drawn individually.

		- Texture Atlas (Static or Dynamic) :: The Result is a FontVector, or a FontVectorHandle
			Static: The entire string is prebuilt into a single Geometry object, referencing the Texture atlas and its just drawn with a single call
			Dynamic: Each character is drawn individually
			Semi-Dynamic: Sections of the string are static, others are not. String is divided up into static sections, by a dynamic portion.

		- Prebuilt 3D extruded Geometry (Static) :: This Result is Geometry
			The entire string is converted to geometry and rendered with a single draw call

		Rename to Font once the rest of the changes are made
	*/









	/*
		An instance of a font

		Remove this.
	*/
	class FontGraphics
	{
	private:



	protected:
		static const UInt32 FONT_INVALID_CHARACTER = 0xFFFFFFFF;



	public:
		FontGraphics(const std::shared_ptr<Font> & ft, UInt32 fontSize);

		

		// Getters :: Don't do things :)
		const std::shared_ptr<Font> & getFont() const { return _font; }

		inline UInt32 getFontSize() const { return _fontSize; }
		
		inline Int32 getLineSpacing() const { return _lineSpacing; }

		
		

		// Maps the CharCode to Glyph/Character Information
		// Does things
		UInt32 mapIndex(UInt32 charCode);



		/*
			Generates a precached version of the text for faster rendering of text

			Does Things :: Move to FontFace
		*/
		virtual std::shared_ptr<Geometry> generateText(const std::wstring & string) = 0;
		virtual const std::shared_ptr<Texture> getTexture() const = 0;




		// Draws Text
	//	void drawText(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms);


		// Loads a Character
		// Does things :: But not much
		Boolean loadCharacter(UInt32 charCode);
		
		// Loads a Range of Character
		Boolean loadCharacter(UInt32 charCode_begin, UInt32 charCode_end);


		


	protected:



		// Loads a Character
		virtual UInt32 loadChar(const GlyphMetric & metric) = 0;

		// Prepare the Font for Rendering
		virtual Boolean begin() = 0;

		// End the Font Rendering
		virtual Boolean end() = 0;


		// Draws the String
		//	void drawString(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms);

		// Draws an Individual Character
	//	virtual Float drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode) = 0;

	private:
		// Reference to the Font
		std::shared_ptr<Font> _font;

		// Size of the Font
		UInt32 _fontSize = 12;


		Int32 _lineSpacing = 0;
	//	Int32 _fontWidth = 0;
	//	Int32 _fontHeight = 0;

		// CharCode <-> Array Index
		std::unordered_map<UInt32, UInt32> _map;
	};

	


	











}

