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
//	class IShader;

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

		/*
		void render(const std::shared_ptr<IShader> & effect);
		void render(const std::shared_ptr<IShader> & effect, UInt32 geomIndex);
		*/


		const Int32 getGeometryCount() const { return _geometry.size(); }
		const Int32 getMaterialCount() const { return _materials.size(); }

		const Material & getGeometryMaterial(UInt32 geomIndex) const { return _materials[_geometry[geomIndex].materialIndex]; }



		const std::vector<Material> & getMaterials() const { return _materials; }
		const Material & getMaterial(Int32 materialIndex) const { return _materials[materialIndex]; }

		void drawGeometry(UInt32 geomIndex) const;

	private:
		std::vector<_MeshData> _geometry;
		std::vector<Material> _materials;
	};


	std::shared_ptr<Mesh> LoadMesh(const std::string & filename);
}

#endif
