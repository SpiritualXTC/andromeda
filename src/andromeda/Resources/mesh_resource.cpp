#include <andromeda/Graphics/mesh.h>
#include <andromeda/Resources/mesh_resource.h>
#include <andromeda/Resources/resource_manager.h>

#include <cassert>


/* assimp include files. These three are usually needed -- the other currently included in the header file */
#include <assimp/cimport.h>
#include <assimp/postprocess.h>



#include <andromeda/andromeda.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/material.h>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


using namespace andromeda;





/*
	loadMesh():

	Loads a mesh using AssImp [Asset Importer], and returns the Mesh
*/
std::shared_ptr<Mesh> andromeda::LoadMesh(const std::string & filename)
{
	MeshLoader loader(filename);

	return loader.getMesh();
}




/*
	Template Specialisation for Loading a Mesh

	TODO: 
	 - The Mesh needs to be created and returned, irrespective of when/where the mesh gets loaded
	 - Add threading support somewhere ...
*/
template<>
std::shared_ptr<Mesh> ResourceLoader::build<Mesh>(std::shared_ptr<File> file)
{
	log_warnp("Loading Mesh");

	MeshLoader loader(file);

	return loader.getMesh();
}













/*

*/
MeshLoader::MeshLoader(const std::string & filename)
	: _scene(aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality))
{
	log_debugp("Loading Scene: %1%", filename);

	

	// Create the Mesh
	_mesh = std::make_shared<Mesh>();

#if 0
	log_debugp("- Mesh Count = %1%", _scene->mNumMeshes);
	log_debugp("- Material Count = %1%", _scene->mNumMaterials);
	log_debugp("- Texture Count = %1%", _scene->mNumTextures);
#endif


	// Load the Scene
	loadScene();
	
}



/*

*/
MeshLoader::MeshLoader(const std::shared_ptr<File> & file)
	: _scene(aiImportFileFromMemory(file->data(), file->length(), aiProcessPreset_TargetRealtime_MaxQuality, file->extension().c_str()))
{
	assert(_scene);
	
	// Create the Mesh
	_mesh = std::make_shared<Mesh>();


	// Load the Scene
	loadScene();
}






/*

*/
MeshLoader::~MeshLoader()
{
	if (_scene != nullptr)
		aiReleaseImport(_scene);
	_scene = nullptr;
}


/*

*/
void MeshLoader::loadScene()
{
	log_debugp("MeshLoader :: loadScene()");

	log_debugp("Materials = %1%", _scene->mNumMaterials);
	log_debugp("Meshes = %1%", _scene->mNumMeshes);


	// Load Materials
	// Need more complex mesh to find out whether it works or not...
	for (UInt32 ma = 0; ma < _scene->mNumMaterials; ++ma)
	{
		loadMaterial(_scene->mMaterials[ma]);
	}


	// Load Meshes
	for (UInt32 me = 0; me < _scene->mNumMeshes; ++me)
	{
		loadMesh(_scene->mMeshes[me]);
	}
}



/*

*/
aiColor3D MeshLoader::getColor(const aiMaterial * pmaterial, const char * pKey, unsigned int type, unsigned int index)
{
	assert(pmaterial);

	aiColor3D color;

	if (pmaterial->Get(pKey, type, index, color) != AI_SUCCESS)
		color = aiColor3D(1, 1, 1);

	return color;
}

/*

*/
aiString MeshLoader::getTextureFilename(const aiMaterial * pmaterial, aiTextureType type, UInt32 index)
{
	assert(pmaterial);

	aiString filename;

	if (pmaterial->GetTexture(type, index, &filename, nullptr, nullptr, nullptr, nullptr, nullptr) != AI_SUCCESS)
	{
		log_warnp("-- Error retrieving texture information");
	}

	return filename;
}


/*

*/
std::shared_ptr<Texture> MeshLoader::loadTexture(const aiMaterial * pmaterial, aiTextureType type, UInt32 index)
{
	// No Texture
	if (pmaterial->GetTextureCount(type) == 0)
		return nullptr;

	// Get Filename
	aiString filename = getTextureFilename(pmaterial, type, 0);

	std::string fn = GetFilename(std::string(filename.C_Str()));

	// Load Texture :: This can't be loaded via a separate thread
	std::shared_ptr<Texture> texture = andromeda::LoadResource<Texture>(fn.c_str());

	return texture;
}


/*

*/
void MeshLoader::loadMaterial(const aiMaterial * pmaterial)
{
	log_debugp("MeshLoader :: loadMaterial()");

	aiString name;
	pmaterial->Get(AI_MATKEY_NAME, name);

	

	aiColor3D ambient = getColor(pmaterial, AI_MATKEY_COLOR_AMBIENT);
	aiColor3D diffuse = getColor(pmaterial, AI_MATKEY_COLOR_DIFFUSE);
	aiColor3D specular = getColor(pmaterial, AI_MATKEY_COLOR_SPECULAR);

	Float opacity = 1.0f;
	pmaterial->Get(AI_MATKEY_OPACITY, opacity);


	// Texture Types
	//aiTextureType_DIFFUSE			:: The Everyday Texture!
	//aiTextureType_NORMALS			:: Normal Map (?)
	//aiTextureType_HEIGHT			:: Bump Map (?)
	//aiTextureType_OPACITY			:: Opacity :: Per Pixel Opacity Variation
	//aiTextureType_DISPLACEMENT	:: Displacement Mapping (?)


	log_debugp("- Material: %1%", name.C_Str());
	log_debugp("-- Ambient: (%1%, %2%, %3%)", ambient.r, ambient.g, ambient.b);
	log_debugp("-- Diffuse: (%1%, %2%, %3%)", diffuse.r, diffuse.g, diffuse.b);
	log_debugp("-- Specular: (%1%, %2%, %3%)", specular.r, specular.g, specular.b);
	log_debugp("-- Opacity: %1%", opacity);
	log_debugp("-- Diffuse Texture Count: %1%", pmaterial->GetTextureCount(aiTextureType_DIFFUSE));



	// Load only the First Texture
	std::shared_ptr<Texture> difTex = loadTexture(pmaterial, aiTextureType_DIFFUSE, 0);
	std::shared_ptr<Texture> normTex = loadTexture(pmaterial, aiTextureType_NORMALS, 0);


	// Texture Debug
	for (UInt32 tex = 0; tex < pmaterial->GetTextureCount(aiTextureType_DIFFUSE); ++tex)
	{
		aiString filename;

		aiReturn err = pmaterial->GetTexture(aiTextureType_DIFFUSE, 0, &filename, nullptr, nullptr, nullptr, nullptr, nullptr);
		if (err != AI_SUCCESS)
		{
			log_warnp("-- Error retrieving texture information");
			continue;
		}

		log_debugp("-- Texture Filename: %1%", filename.C_Str());
	}

	






	
	// Create the Material
	Material material(name.C_Str());

	// Set Material Properties
	material.setAmbient(ambient.r, ambient.g, ambient.b);
	material.setDiffuse(diffuse.r, diffuse.g, diffuse.b);
	material.setSpecular(specular.r, specular.g, specular.b);
	material.setOpacity(opacity);

	// Set Textures
	if (difTex)
		material.setDiffuseTexture(difTex);

	if (normTex)
		material.setNormalTexture(normTex);

	// Add Material
	_mesh->addMaterial(material);
}


/*

*/
void MeshLoader::loadMesh(const aiMesh * pmesh)
{
	log_debugp("MeshLoader :: loadMesh()");

#if 0
	log_debugp("-- Mesh '%1%'", pmesh->mName.C_Str());
	log_debugp("-- Vertices = %1%", pmesh->mNumVertices);
	log_debugp("-- Faces = %1%", pmesh->mNumFaces);
	log_debugp("-- Material index = %1%", pmesh->mMaterialIndex);
	log_debugp("-- Texture Channels %1%", pmesh->GetNumUVChannels());
	for (UInt32 t = 0; t < pmesh->GetNumUVChannels(); ++t)
		log_debugp("--- Texture Coordinates[%1%] = %2%", t, pmesh->mNumUVComponents[t]);
#endif


	GeometryBuilder gb;

	// Add Information to the Geometry Builder


	// Position Data
	if (pmesh->HasPositions())
		gb.addVertexData<aiVector3D>("pos", pmesh->mVertices, (Size)pmesh->mNumVertices, 3, GL_FLOAT, GeometryLocation::Position);

	// Normal Data
	if (pmesh->HasNormals())
		gb.addVertexData<aiVector3D>("norm", pmesh->mNormals, (Size)pmesh->mNumVertices, 3, GL_FLOAT, GeometryLocation::Normal);

	// Texture Data
	for (UInt32 tex = 0; tex < pmesh->GetNumUVChannels(); ++tex)
	{
		if (pmesh->HasTextureCoords(tex))
		{
			// Need a mesh with numerous texture channels to test this out...
			// Assimp ONLY uses 3D Vectors for storing texture coordinates, irrespective of how many coordinates the texture needs...
			// Therefore texture coordinates need to be interpreted for 1D or 2D systems, it won't be possible to just pass through. (Currently)

			// Reintrepretting the coordinates could be done here --- or add something into the GeometryBuilder that can cull out the stride 
			//  - this will need to be done upon ADDING (IE: addVertexData(...)), and not upon building

			// It MAY be possible to allow the coordinates to be passed through, with the appropriate stride as-is
			// however this will add additional data that is never used to the GPU streams

			// The other aspect is.... the stride offsets have never been tested for the case where the stride is greater than the size of the data
		}
	}



	// Index Data :: Simplistic Version :: Assumes all faces have 3 vertices :: This is wrong :)
	// TODO: Implement a parser to build the faces so they are always made up of 3 indices
	if (pmesh->HasFaces() && pmesh->mNumFaces >= 1)
	{
		// Create Buffer
		UInt32 * indices = new UInt32[pmesh->mNumFaces * 3];
		UInt32 * pindices = indices;
		for (UInt32 f = 0; f < pmesh->mNumFaces; ++f)
		{
			const aiFace & face = pmesh->mFaces[f];

			*pindices++ = face.mIndices[0];
			*pindices++ = face.mIndices[1];
			*pindices++ = face.mIndices[2];
		}

		// Set Index Data
		gb.setIndexData(indices, pmesh->mNumFaces * 3);

		// Delete Buffer
		if (indices)
			delete[] indices;
	}

	// Add Geometry
	_mesh->addGeometry(gb, pmesh->mMaterialIndex);
}




