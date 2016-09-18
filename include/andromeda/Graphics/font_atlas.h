#pragma once

#include <string>
#include <vector>

#include <andromeda/glm.h>

#include <andromeda/Utilities/image.h>
#include <andromeda/Utilities/font.h>

#include "font_graphics.h"




namespace andromeda
{
	class VertexBuffer;
	class IndexBuffer;

	class Geometry;
	class GeometryDescription;


	/*
		Texture based Font Rendering

		TODO: Add a single pixel outline around ALL fonts
	*/
	class FontAtlas : public virtual FontGraphics
	{
	private:
		const static Int32 IMAGE_WIDTH = 2048;
		const static Int32 IMAGE_HEIGHT = 2048;

		
		/*
			TODO: Improve Meh
		*/
#if 0
		struct _Metrics
		{
			Float advance;

			Float bearingX;
			Float bearingY;

			Float width;
			Float height;
		};
#endif


		struct _Character
		{
		//	_Metrics metrics;
			GlyphMetric metrics;

			//_Geometry geometry;
			glm::ivec2 dimensions;
			glm::ivec2 offset;

			Float advance;

			UInt32 vertexOffset;
		};

	public:
		FontAtlas(const std::shared_ptr<Font> & ft, UInt32 fontSize);


		const std::shared_ptr<Texture> getTexture() const override { return _texture; }
		
		// Generate Geometry
		std::shared_ptr<Geometry> generateText(const std::wstring & string) override;


	protected:
		Boolean begin() override;
		Boolean end() override;

		UInt32 loadChar(const GlyphMetric & metric) override;

		

		
		// Draw the Character
	//	Float drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode) override;

		// Create Vertex Buffers & Textures
		void createBuffers();

		// Update Vertex Buffers & Textures
		void updateBuffers();



		void addGeometry(const _Character & ch);
		void addGeometry(const _Character & ch, std::vector<Float> & verts, Float offX, Float offY);



		// Determine the next set of texture coordinates to place a character in the atlas
		Boolean getNextTextureCoordinate(const glm::ivec2 & dimensions, glm::ivec2 & texCoord);

		// Splits a block of text into lines
		Boolean splitText(const std::wstring & text, std::vector<std::wstring> & lines);

	private:



		Image _image;

		std::shared_ptr<Texture> _texture;

		std::vector<_Character> _characters;


		std::shared_ptr<VertexBuffer> _vb;
		std::shared_ptr<GeometryDescription> _desc;

		std::vector<Float> _vertices;



		Float FONT_SCALE = 64.0f;
	};
}