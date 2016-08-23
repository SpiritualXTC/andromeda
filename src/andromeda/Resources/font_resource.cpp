#include <andromeda/Resources/font_resource.h>
#include <andromeda/Resources/resource_manager.h>



// Freetype Library
#include <freetype/ftoutln.h>

// Cimage
#include <cimg/CImg.h>

// Andromeda
#include <andromeda/Geometry/shape.h>
#include <andromeda/IO/file.h>
#include <andromeda/Utilities/image.h>

#include <andromeda/Utilities/log.h>


using namespace andromeda;
using namespace andromeda::geometry;


template<>
std::shared_ptr<FontFace> ResourceLoader::build<FontFace>(std::shared_ptr<File> file)
{
	log_warnp("ResourceLoader :: build<Font>() :: Loading Font");

	std::shared_ptr<FontFace> ff = std::make_shared<FontFace>(file);

	return ff;
}







std::weak_ptr<FontLibrary> FontLibrary::_instance;


/*

*/
std::shared_ptr<FontLibrary> FontLibrary::loadLibrary()
{
	// The library is still loaded.
	if (!_instance.expired())
	{
		log_debug("Font Library already initialised");
		return _instance.lock();
	}

	// Load Library
	std::shared_ptr<FontLibrary> lib = std::make_shared<FontLibrary>();

	// Assign Reference
	_instance = lib;

	return lib;
}




/*

*/
FontLibrary::FontLibrary()
{
	log_debug("Initialising Font Library");

	// Init Library
	FT_Error libError = FT_Init_FreeType(&_lib);

	if (libError)
	{
		log_err("Error Initialising FreeType Library");
		throw FontLibraryException();
	}
}

/*

*/
FontLibrary::~FontLibrary()
{
	log_debug("UnInitialising Font Library");

	// Kill Library
	if (_lib)
		FT_Done_FreeType(_lib);

	_lib = nullptr;
}
















/*

*/
Int32 FontFace::moveTo(const FT_Vector* to, void* user)
{
	assert(user);

	Shape * shape = (Shape*)user;

	log_infop("MOVE: (%1%, %2%)", to->x, to->y);

	glm::vec3 v = glm::vec3(to->x, to->y, 0.0f);
	shape->moveTo(v);


	return 0;
}


/*

*/
Int32 FontFace::lineTo(const FT_Vector*  to, void* user)
{
	assert(user);

	Shape * shape = (Shape*)user;

	log_infop("LINE: To = (%1%, %2%)", to->x, to->y);

	// Add a Line
	glm::vec3 v = glm::vec3(to->x, to->y, 0.0f);
	shape->lineTo(v);

	return 0;
}

/*

*/
Int32 FontFace::conicTo(const FT_Vector * control, const FT_Vector * to, void * user)
{
	assert(user);

	Shape * shape = (Shape*)user;

	log_infop("CONIC: To = (%1%, %2%), Control = (%3%, %4%)", to->x, to->y, control->x, control->y);

	// Add Bezier, with single control point
	// For now just add a line
	glm::vec3 v = glm::vec3(to->x, to->y, 0.0f);
	glm::vec3 c = glm::vec3(control->x, control->y, 0.0f);
	shape->bezierTo(c, v);

	return 0;
}

/*

*/
Int32 FontFace::cubicTo(const FT_Vector * control1, const FT_Vector * control2, const FT_Vector * to, void * user)
{
	assert(user);

	Shape * shape = (Shape*)user;

	log_infop("CUBIC: To = (%1%, %2%), Control1 = (%3%, %4%), Control2 = (%5%, %6%)", to->x, to->y, control1->x, control1->y, control2->x, control2->y);

	// Add Bezier, with multiple control points
	// For now just add a line

	// The Polygon / Contour Classes currently do not support mutli-control point beziers.
	// However when they do... it will be to split cubic curves into quadratic curves.
	glm::vec3 v = glm::vec3(to->x, to->y, 0.0f);
	glm::vec3 c1 = glm::vec3(control1->x, control1->y, 0.0f);
	glm::vec3 c2 = glm::vec3(control2->x, control2->y, 0.0f);
	shape->lineTo(v);

	return 0;
}













/*

*/
FontFace::FontFace(const std::string & filename)
{
	loadFace(filename);
}

/*

*/
FontFace::FontFace(const std::shared_ptr<File> & file)
{
	loadFace(file);
}


/*

*/
FontFace::~FontFace()
{
	unloadFace();
	_library = nullptr;
}





/*
	Loads the Font from disk
*/
void FontFace::loadFace(const std::string & filename)
{
	// Load Font Library
	_library = FontLibrary::loadLibrary();

	// Unloads teh Current Face
	unloadFace();

	// Load Font 
	FT_Error fntError = FT_New_Face(_library->getLibrary(), filename.c_str(), 0, &_face);
	if (fntError)
	{
		log_err("Error Loading Font");
		throw FontException("Unable to load Font");
	}
}


/*
	Loads the Font from Memory Pointer
*/
void FontFace::loadFace(const std::shared_ptr<File> & file)
{
	// Load Font Library
	_library = FontLibrary::loadLibrary();

	// Unloads the Current Face
	unloadFace();

	// Load Font 
	FT_Error fntError = FT_New_Memory_Face(_library->getLibrary(), (FT_Byte*)file->data(), file->length(), 0, &_face);
	if (fntError)
	{
		log_err("Error Loading Font from memory");
		throw FontException("Unable to load Font from memory");
	}
}



/*
	Unloads the Face
*/
void FontFace::unloadFace()
{
	// Kill Font
	if (_face)
		FT_Done_Face(_face);
	_face = nullptr;
}



/*

*/
Boolean FontFace::setFontSize(UInt32 fontSize)
{
	assert(_face);

	if (fontSize == _lastFontSizeSet)
		return true;

	// Changes the Pixel Size for the Font
	FT_Error fntError = FT_Set_Pixel_Sizes(_face, fontSize, fontSize);

	// Reset the Last Character Loaded :: Some of this information may change under a different size Font
	_lastCharacterLoaded = VALUE_UNASSIGNED;

	// Set the Last Font Size Used
	_lastFontSizeSet = fontSize;

	return fntError ? false : true;
}





/*

*/
Int32 FontFace::getFontWidth()
{
	return _face->bbox.xMax - _face->bbox.xMin;
}

/*

*/
Int32 FontFace::getFontHeight()
{
	return _face->bbox.yMax - _face->bbox.yMin;
}

/*

*/
Int32 FontFace::getLineSpacing()
{
	return _face->size->metrics.height >> 6;
}



/*

*/
Boolean FontFace::getCharacterMetrics(UInt32 charCode, GlyphMetric & metrics)
{
	// Get the Character
	if (!loadCharacter(charCode))
		return false;

	// Determine if the Font has vertical metrics
	//FT_Long hasVerticalMetrics = FT_HAS_VERTICAL(fontFace);

	// Copy Glyph Characters to the Class

	metrics.charCode = charCode;
	
	metrics.hori.advance = _face->glyph->metrics.horiAdvance >> 6;
	metrics.hori.bearingX = _face->glyph->metrics.horiBearingX >> 6;
	metrics.hori.bearingY = _face->glyph->metrics.horiBearingY >> 6;
	
	metrics.vert.advance = _face->glyph->metrics.vertAdvance >> 6;
	metrics.vert.bearingX = _face->glyph->metrics.vertBearingX >> 6;
	metrics.vert.bearingY = _face->glyph->metrics.vertBearingY >> 6;

	metrics.width = _face->glyph->metrics.width >> 6;
	metrics.height = _face->glyph->metrics.height >> 6;

	return true;
}


/*

*/
Boolean FontFace::getCharacterOutline(UInt32 charCode)
{
	// Get the Character
	if (!loadCharacter(charCode))
		return false;

	// Set Outline
	FT_Outline * outline = &_face->glyph->outline;

	// Setup Outline Decomposer
	FT_Outline_Funcs funcs;
	funcs.delta = 0;
	funcs.shift = 0;
	funcs.conic_to = &FontFace::conicTo;
	funcs.cubic_to = &FontFace::cubicTo;
	funcs.move_to = &FontFace::moveTo;
	funcs.line_to = &FontFace::lineTo;


	Shape shape;	// pass me in :)

	// Decompose Font
	FT_Error fntError = FT_Outline_Decompose(outline, &funcs, &shape);

	return fntError ? false : true;;
}


/*
	
*/
Boolean FontFace::getCharacterBitmap(UInt32 charCode, ImageData<UInt8> & image)
{
	// Get the Character
	if (!loadCharacter(charCode))
		return false;


	// Render the Glyph as a bitmap
	FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);

	// Pointer to the Bitmap
	FT_Bitmap* pBitmap = &_face->glyph->bitmap;


	//glyph.dimension = glm::ivec2(fontFace->glyph->metrics.width >> 6, fontFace->glyph->metrics.height >> 6);

	Int32 width = _face->glyph->metrics.width >> 6;
	Int32 height = _face->glyph->metrics.height >> 6;
	Int32 channels = 1;




#if 0
	log_errp("Exporting Test");

	

	cimg_library::CImg<UInt32> img(512, 512, 1, channels, 64);

	Int32 xOff = 20;
	Int32 yOff = 20;
	UInt32 * data = img.data();


	for (Int32 h = 0; h < height; ++h)
	{
		Int32 y = h + yOff;
		for (Int32 w = 0; w < width; ++w)
		{
			Int32 x = w + xOff;



			Int32 index = h * width + w;
			UInt8 value = pBitmap->buffer[index];

			Int32 pixel = y * 512 + x;

			UInt32 argb = 0xFF << 24 | value << 16 | value << 8 | value << 0;

			data[pixel] = argb;
		}
	}

	img.save_bmp("png_test.bmp");
#endif


	// Asssign the Image
	image.width = width;
	image.height = height;
	image.channels = channels;
	image.image = pBitmap->buffer;


//	std::shared_ptr<ImagePtr<UInt8>> image = std::make_shared<ImagePtr<UInt8>>(width, height, channels, pBitmap->buffer);

	return true;
}






/*

*/
Boolean FontFace::loadCharacter(UInt32 charCode)
{
	// This Character is already loaded
	if (charCode == _lastCharacterLoaded)
		return true;

	// Convert Character Code to Glyph Index
	FT_UInt glyphIndex = FT_Get_Char_Index(_face, charCode);

	// Validate Character :: glyphIndex returns 0, for a character that has no mapping
	if (glyphIndex == VALUE_UNASSIGNED)
	{
		_lastCharacterLoaded = VALUE_UNASSIGNED;
		return false;
	}

	// Load the Glyph
	FT_Error fntError = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_DEFAULT);

	if (fntError)
	{
		_lastCharacterLoaded = VALUE_UNASSIGNED;
	}
	else
	{
		_lastCharacterLoaded = charCode;
	}


	return fntError ? false : true;
}