#pragma once

#include <memory>
#include <vector>

#include <assimp/scene.h>

#include <andromeda/stddef.h>

namespace andromeda
{
	class Mesh;
	class File;
	class Texture;

	class MeshLoader
	{
	public:
		MeshLoader(const std::string & filename);
		MeshLoader(const std::shared_ptr<File> & file);
		virtual ~MeshLoader();



		/* Get Mesh */
		const std::shared_ptr<Mesh> & getMesh() const { return _mesh; }

	private:

		void loadScene();
		void loadMaterial(const aiMaterial * pmaterial);
		void loadMesh(const aiMesh * pmesh);


		aiColor3D getColor(const aiMaterial * pmaterial, const char * pKey, unsigned int type, unsigned int index);
		aiString getTextureFilename(const aiMaterial * pmaterial, aiTextureType type, UInt32 index);

		std::shared_ptr<Texture> loadTexture(const aiMaterial * pmaterial, aiTextureType type, UInt32 index);

		const aiScene * _scene;

		std::shared_ptr<Mesh> _mesh;
	};	




//	template<>
//	std::shared_ptr<Mesh> ResourceLoader::build<Mesh>(std::shared_ptr<File> file);
}



