#pragma once

#include <andromeda/glm.h>

#include <andromeda/Utilities/image.h>

#include "font.h"




namespace andromeda
{
	class VertexBuffer;
	class IndexBuffer;

	class Geometry;
	class GeometryDescription;


	/*
		Precached FontAtlas
	*/
	class FontAtlasHandle
	{
	public:


	};

	/*
	Texture based Font Rendering
	*/
	class FontAtlas : public virtual IFont
	{
	private:
		const static Int32 IMAGE_WIDTH = 2048;
		const static Int32 IMAGE_HEIGHT = 2048;

		
		
		struct _Metrics
		{
			Float advance;

			Float bearingX;
			Float bearingY;

			Float width;
			Float height;
		};


		// Definately needs to be called something else :)
		struct _Geometry
		{
			glm::ivec2 textureOffset;
			

		};

		struct _Character
		{
			_Metrics metrics;

			//_Geometry geometry;
			glm::ivec2 dimensions;
			glm::ivec2 offset;

			UInt32 vertexOffset;
		};

	public:
		FontAtlas(const std::shared_ptr<FontFace> & ft, UInt32 fontSize);


		const std::shared_ptr<Texture> getTexture() const override { return _texture; }
		
		// Generate Geometry
		std::shared_ptr<Geometry> generateText(const std::wstring & string) override;



	protected:
		Boolean begin() override;
		Boolean end() override;

		UInt32 loadChar(const GlyphMetric & metric) override;

		

		
		// Draw the Character
		Float drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode) override;

		// Create Vertex Buffers & Textures
		void createBuffers();

		// Update Vertex Buffers & Textures
		void updateBuffers();



		void addGeometry(const _Character & ch);
		void addGeometry(const _Character & ch, std::vector<Float> & verts, Float offX, Float offY);


		Boolean getNextTextureCoordinate(const glm::ivec2 & dimensions, glm::ivec2 & texCoord);



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