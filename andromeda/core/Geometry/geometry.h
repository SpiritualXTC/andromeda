#pragma once

#if 0
#include <memory>

#include <Common/types.h>

namespace andromeda
{
	// Forward Declarations
	class VertexBuffer;
	class IndexBuffer;
	class GeometryDescription;



	/*
		Class containing geometry!
	*/
	class Geometry
	{
	public:
		Geometry();
	//	Geometry(GeometryBuilder & gb);
		Geometry(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc, std::shared_ptr<IndexBuffer> ib);
		virtual ~Geometry();


		/*
			Render all the geometry at once!
		*/
		void render();

	//	inline std::shared_ptr<VertexBuffer> getVertexBuffer() { return _vertexBuffer; }
	//	inline std::shared_ptr<GeometryDescription> getDescription() { return _description; }

	private:
		std::shared_ptr<VertexBuffer> _vertexBuffer;
		std::shared_ptr<IndexBuffer> _indexBuffer;

		std::shared_ptr<GeometryDescription> _description;
	};
}


typedef andromeda::Geometry aGeometry;
#endif
