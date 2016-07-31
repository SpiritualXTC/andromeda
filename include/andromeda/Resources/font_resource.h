#pragma once

/*
	TODO:
	This is technically NOT graphics, so should probably appear in the Resources area
*/
#include <memory>
#include <string>
#include <unordered_map>


#include <andromeda/stddef.h>
#include <andromeda/exception.h>

// Not Sure which is better .... 
// Really dont wont FreeType poluting the global namespace :(
// Maybe place b/w a wrapper? (Deal with later) :)
#include <ft2build.h>
#include FT_FREETYPE_H


/*
	Handles loading of TrueType fonts, via the freetype Library
*/

namespace andromeda
{
	class File;

	template<typename T>
	struct ImageData;


	class FontException : Exception
	{
	public:
		FontException() : Exception("Exception in Font") {}
		FontException(const std::string & e) : Exception(e){}
	};

	class FontLibraryException : Exception
	{
	public:
		FontLibraryException() : Exception("Exception in Font Library"){}
		FontLibraryException(const std::string & e) : Exception(e) {}
	};








	/*
		This class handles loading and unloading the library :: 
		
		TODO: It shouldn't be exposed to to the API

		TODO: This static implementation could be templated as a design pattern... but fuck knows whats it called.
	*/
	class FontLibrary
	{
	public:
		// STATIC FUNCTIONS
		static std::shared_ptr<FontLibrary> loadLibrary();




	private:
		// STATIC MEMBERS

		// This allows the library to immediately clean itself up as soon as it moves beyond scope without manual intervention.
		// While also allowing shared reference of the library while in scope
		static std::weak_ptr<FontLibrary> _instance;	


	public:
		FontLibrary();
		virtual ~FontLibrary();

		const inline FT_Library getLibrary() const { return _lib; }

	private:
		FT_Library _lib;
	};





	/*
		The glyph information that makes up a character

		This uses the RAW information from freetype, without modification.... well without scaling :P
	*/
	class CharacterGlyphMetric
	{
	public:
	};


	struct GlyphMetricDirection
	{
		Int32 advance;

		Int32 bearingX;
		Int32 bearingY;
	};

	struct GlyphMetric
	{
		UInt32 charCode;

		GlyphMetricDirection hori;
		GlyphMetricDirection vert;

//		Int32 advanceX;
//		Int32 advanceY;

//		Int32 bearingX;
//		Int32 bearingY;

		Int32 width;
		Int32 height;
	};




	/*
		TODO: Loading fonts via resource seems to be really slow...

		TODO:
		Determine if change the fontsize does anything internally (freetype)
		Otherwise just add the current fontSize to the class, and check whether it matches when calling setFontSize(...)
	*/
	class FontFace
	{
	private:
		static const UInt32 VALUE_UNASSIGNED = 0;

		static Int32 moveTo(const FT_Vector* to, void* user);
		static Int32 lineTo(const FT_Vector*  to, void* user);
		static Int32 conicTo(const FT_Vector * control, const FT_Vector * to, void * user);
		static Int32 cubicTo(const FT_Vector * control1, const FT_Vector * control2, const FT_Vector * to, void * user);

	public:
		FontFace(const std::string & ttfFile);
		FontFace(const std::shared_ptr<File> & file);
		
		virtual ~FontFace();
		
		// Sets the Font Size
		Boolean setFontSize(UInt32 size);

		// Gets the characters metrics
		Boolean getCharacterMetrics(UInt32 charCode, GlyphMetric & metrics);
		Boolean getCharacterOutline(UInt32 charCode);
		Boolean getCharacterBitmap(UInt32 charCode, ImageData<UInt8> & image);


		Int32 getFontWidth();
		Int32 getFontHeight();
		Int32 getLineSpacing();


	private:

		Boolean loadCharacter(UInt32 charCode);


		void loadFace(const std::string & filename);
		void loadFace(const std::shared_ptr<File> & file);
		void unloadFace();
		
		FT_Face _face = nullptr;;			// Pointer to the Face
		std::shared_ptr<FontLibrary> _library;


		UInt32 _lastCharacterLoaded = VALUE_UNASSIGNED;
		UInt32 _lastFontSizeSet = VALUE_UNASSIGNED;
		// Internal Location of Character Data thats been loaded already
	};
}