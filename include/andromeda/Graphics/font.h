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

	class FontFace;

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

		- Prebuilt into a Texture (Static Only) :: This Result is a Texture (Possibly a Sprite)
			The entire string is drawn to a texture which is then rendered as 2 primitives
			This can only be done with very small strings -- will depend on the size of the texture, could be extremely wasteful of texture space, even if it allows multiple strings per texture

		- Prebuilt 3D extruded Geometry :: This Result is Geometry
			The entire string is converted to geometry and rendered with a single draw call

		Rename to Font once the rest of the changes are made
	*/









	/*
		Text
	*/
	class IFont
	{
	private:



	protected:
		static const UInt32 FONT_INVALID_CHARACTER = 0xFFFFFFFF;



	public:
		IFont(const std::shared_ptr<FontFace> & ft, UInt32 fontSize);

		// Gets the Font Index
		const std::shared_ptr<FontFace> & getFontFace() const { return _font; }

		inline UInt32 getFontSize() const { return _fontSize; }
		
		
		inline Int32 getFontWidth() const { return _fontWidth; }
		inline Int32 getFontHeight() const { return _fontHeight; }
		
		inline Int32 getLineSpacing() const { return _lineSpacing; }



		// Maps the CharCode to Glyph/Character Information
		UInt32 mapIndex(UInt32 charCode);



		/*
			Generates a precached version of the text for faster rendering of static text
		*/
		virtual std::shared_ptr<Geometry> generateText(const std::wstring & string) = 0;




		// Draws Text
		void drawText(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms);


		// Loads a Character
		Boolean loadCharacter(UInt32 charCode);
		
		// Loads a Range of Character
		Boolean loadCharacter(UInt32 charCode_begin, UInt32 charCode_end);


		Boolean splitText(const std::wstring & text, std::vector<std::wstring> & lines);


	protected:
		// Draws the String
		void drawString(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms);

		// Loads a Character
		virtual UInt32 loadChar(const GlyphMetric & metric) = 0;

		// Prepare the Font for Rendering
		virtual Boolean begin() = 0;

		// End the Font Rendering
		virtual Boolean end() = 0;

		// Draws an Individual Character
		virtual Float drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode) = 0;

	private:
		// Reference to the Font
		std::shared_ptr<FontFace> _font;

		// Size of the Font
		UInt32 _fontSize = 12;


		Int32 _lineSpacing = 0;
		Int32 _fontWidth = 0;
		Int32 _fontHeight = 0;

		// CharCode <-> Array Index
		std::unordered_map<UInt32, UInt32> _map;
	};

	
#if 0
	/*
		May Need a templated support class...
	*/
	class FontSupport : public virtual IFont
	{
	private:
		struct _Character
		{

		};

	public:

	};
#endif





#if 0
	/*
		Precached FontVector
	*/
	class FontVectorHandle
	{

	};

	/*
		Bezier curve based font rendering
	*/
	class FontVector : public virtual IFont
	{
	public:

	};
#endif

	












	/*
		This class is kinda broken :)

		TODO:
		Replace it with FontType & FontVector and an interface
	*/
	class Font
	{
	private:
		const static Int32 BMP_WIDTH = 2048;
		const static Int32 BMP_HEIGHT = 2048;

		


		// Information about a single Glyph
		struct _Glyph
		{
			_Glyph(UInt32 c)
				: code(c){}

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
				: glyph(c){}


			_Glyph glyph;
			std::shared_ptr<Geometry> geometry;
		};


	public:
		Font(const std::string & font, Int32 size);
		virtual ~Font();


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

