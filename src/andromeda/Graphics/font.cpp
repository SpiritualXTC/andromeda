#include <andromeda/Graphics/font.h>

#include <andromeda/Graphics/texture.h>

#include <andromeda/Utilities/log.h>

#include <SOIL/SOIL.h>

using namespace andromeda;

/*

*/
Font::Font(const std::string & font, Int32 size)
{
	// Create the Texture
	_texture = std::make_unique<Texture>(BMP_WIDTH, BMP_HEIGHT);

	// Initialise the Bitmap to Black
	for (Int32 h = 0; h < BMP_HEIGHT; ++h)
	{
		for (Int32 w = 0; w < BMP_WIDTH; ++w)
			_bitmap[h][w] = 0;
	}



	loadFont(font, size);
}


/*

*/
Font::~Font()
{


}


/*

*/
Boolean Font::loadFont(const std::string & font, Int32 size)
{
	FT_Library lib;

	log_infop("Loading Font %1%", font);

	// Init Library
	FT_Error libError = FT_Init_FreeType(&lib);

	if (libError)
		log_err("Error Initialising FreeType Library");


	// Load Font 
	FT_Face face;
	FT_Error fntError = FT_New_Face(lib, font.c_str(), 0, &face);
	if (fntError)
		log_err("Error Loading Font");

	// Set Pixel Size
	FT_Set_Pixel_Sizes(face, size, size);


	log_debugp("Fixed Sizes: %1%", face->num_fixed_sizes);
	for (Int32 i = 0; i < face->num_fixed_sizes; ++i)
	{
		log_debugp("%1% = %2%x%3%", i, face->available_sizes[i].width, face->available_sizes[i].height);
	}

	log_debugp("BBox: (%1%, %2%), (%3%, %4%)", face->bbox.xMin >> 6, face->bbox.yMin >> 6, face->bbox.xMax >> 6, face->bbox.yMax >> 6);

//	log_debugp("Max Advances: %1%x%2%", face->available_sizes >> 6, face->max_advance_height >> 6);
//	log_debugp("Height = %1%", face->height >> 6);


	// Load Initial Set of Characters
	for (Int32 i = 32; i < 128; ++i)
	{
		loadChar(face, i);
	}


	// Kill Font
	FT_Done_Face(face);

	// Kill Library
	FT_Done_FreeType(lib);


//	SOIL_save_image("test.bmp", SOIL_SAVE_TYPE_BMP, BMP_WIDTH, BMP_HEIGHT, 4, (const unsigned char*)&_bitmap[0][0]);

	return true;
}


/*

*/
Boolean Font::loadChar(const FT_Face & fontFace, ULong charCode)
{
	// Load the Glyph
	FT_Load_Glyph(fontFace, FT_Get_Char_Index(fontFace, charCode), FT_LOAD_DEFAULT);

	// Render the Glyph as a bitmap
	FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

	// Pointer to the Bitmap
	FT_Bitmap* pBitmap = &fontFace->glyph->bitmap;


//	log_infop("Glyph '%1%' Metrics", (Char)charCode);

	
	
	
	// Determine if the Font has vertical metrics
	FT_Long hasVerticalMetrics = FT_HAS_VERTICAL(fontFace);

	// >> 6 divides the values by 64

	_Glyph glyph(charCode);
	
	glyph.advance = fontFace->glyph->metrics.horiAdvance >> 6;
	
	glyph.bearing = glm::ivec2(fontFace->glyph->metrics.horiBearingX >> 6, fontFace->glyph->metrics.horiBearingY >> 6);

	glyph.dimension = glm::ivec2(fontFace->glyph->metrics.width >> 6, fontFace->glyph->metrics.height >> 6);

	// Dump Glyph Information
//	log_infop("- Dimension: %1%x%2%", glyph.dimension.x, glyph.dimension.y);
//	log_infop("- Bearing: %1%x%2%", glyph.dimension.x, glyph.dimension.y);
//	log_infop("- Advance: %1%", glyph.advance);

	// Dump Bitmap Information
//	log_infop("- Bitmap Dimensions: %1%x%2%", pBitmap->width, pBitmap->rows);






	// Copy the Bitmap to the Texture, with the appropriate offsets
	Int32 cols = 16;
	Int32 rows = 16;

	Int32 sprWidth = BMP_WIDTH / cols;
	Int32 sprHeight = BMP_HEIGHT / rows;

	Int32 xCell = (charCode % cols);
	Int32 yCell = (charCode / rows);

	Int32 xOff = xCell * sprWidth;
	Int32 yOff = yCell * sprHeight;


//	log_infop("- Grid Cell: %1%x%2%", xCell, yCell);
//	log_infop("- Bitmap Offset: %1%x%2%", xOff, yOff);


	for (Int32 h = 0; h < glyph.dimension.y; ++h)
	{
		Int32 y = h + yOff;
		for (Int32 w = 0; w < glyph.dimension.x; ++w)
		{
			Int32 x = w + xOff;

			Int32 index = h * glyph.dimension.x + w;
			UInt8 value = pBitmap->buffer[index];
			_bitmap[y][x] = 0xFF << 24 | value << 16 | value << 8 | value << 0;
		}
	}

	


	return true;
}




/*

*/
Float Font::calcWidth(const std::string & string)
{
	return -1.0f;
}


/*

*/
void Font::render(const std::string & string)
{

}