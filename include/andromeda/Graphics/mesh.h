#ifndef _ANDROMEDA_GRAPHICS_MESH_H_
#define _ANDROMEDA_GRAPHICS_MESH_H_

#include <memory>
#include <string>
#include <vector>

#include <andromeda/stddef.h>

#include "material.h"

namespace andromeda
{
	class Geometry;
	class GeometryBuilder;
	class IEffect;

	/*
		Simplistic UNOPTIMISED Mesh Class
	*/
	class Mesh
	{
	private:
		struct _MeshData
		{
		public:
			_MeshData(std::shared_ptr<Geometry> & g, Int32 matIndex)
				: geometry(g)
				, materialIndex(matIndex)
			{

			}
			std::shared_ptr<Geometry> geometry;
			Int32 materialIndex;
		};

	public:
		Mesh();
		virtual ~Mesh();

		Boolean addGeometry(std::shared_ptr<Geometry> & geometry, Int32 matIndex);
		Boolean addGeometry(GeometryBuilder & geometryBuilder, Int32 matIndex);

		Boolean addMaterial(Material & material);

		void render(const std::shared_ptr<IEffect> & effect);
		void render(const std::shared_ptr<IEffect> & effect, UInt32 geomIndex);

	private:
		std::vector<_MeshData> _geometry;
		std::vector<Material> _materials;
	};


	std::shared_ptr<Mesh> LoadMesh(const std::string & filename);
}


#endif
