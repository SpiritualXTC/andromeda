#ifndef _ANDROMEDA_GRAPHICS_MATERIAL_H_
#define _ANDROMEDA_GRAPHICS_MATERIAL_H_

#include <memory>
#include <string>

#include <andromeda/stddef.h>

#include <andromeda/glm.h>



namespace andromeda
{
	class ITexture;

	/*
		Depending on how the material/mesh/geometry is all integrated this interface may be completely uneeded
	*/
	class IMaterial
	{
	public:
		IMaterial() {}
		virtual ~IMaterial() {}
	};


	/*
		This class (and the shader) is built around how Asset Importer treats materials...
		without all the complexities ... hopefully 
	*/
	class Material : virtual public IMaterial
	{
	public:
		typedef glm::vec3 MatColor;

		//
		Material()
		{

		}

		//
		Material(const std::string & name) 
			: _name(name)
		{
		}
		
		virtual ~Material() {}

		// Get Material Name
		const inline std::string & getName() const { return _name; }

		// Get Material Opacity
		const inline Float getOpacity() const { return _opacity; }

		// Set Material Name
		inline Material & setName(const std::string & name)
		{
			_name = name;
			return *this;
		}

		// Set Opacity
		inline Material & setOpacity(Float opacity)
		{
			_opacity = opacity;
			return *this;
		}


		const inline MatColor & getAmbient() const { return _ambient; }
		const inline MatColor & getDiffuse() const { return _diffuse; }
		const inline MatColor & getSpecular() const { return _specular; }
		const inline MatColor & getEmissive() const { return _emissive; }
		const inline Float getShininess() const { return _shininess; }
		const inline Float getReflectivity() const { return _reflectivity; }

		// Set Ambient Color
		inline Material & setAmbient(const MatColor & ambient)
		{
			_ambient = ambient;
			return *this;
		}

		// Set Ambient Color
		inline Material & setAmbient(Float r, Float g, Float b)
		{
			_ambient = glm::vec3(r, g, b);
			return *this;
		}

		// Set Diffuse Color
		inline Material & setDiffuse(const MatColor & diffuse)
		{
			_diffuse = diffuse;
			return *this;
		}

		// Set Diffuse Color
		inline Material & setDiffuse(Float r, Float g, Float b)
		{
			_diffuse = glm::vec3(r, g, b);
			return *this;
		}

		// Set Specular Color
		inline Material & setSpecular(const MatColor & specular)
		{
			_specular = specular;
			return *this;
		}

		// Set Specular Color
		inline Material & setSpecular(Float r, Float g, Float b)
		{
			_specular = glm::vec3(r, g, b);
			return *this;
		}

		// Set Emissive Color
		inline Material & setEmissive(const MatColor & emissive)
		{
			_emissive = emissive;
			return *this;
		}

		// Set Emissive Color
		inline Material & setEmissive(Float r, Float g, Float b)
		{
			_emissive = glm::vec3(r, g, b);
			return *this;
		}

		// Set Specular Shininess
		inline Material & setShininess(Float shininess)
		{
			_shininess = shininess;
			return *this;
		}

		// Set Reflectivity
		inline Material & setReflectivity(Float reflectivity)
		{
			_reflectivity = reflectivity;
			return *this;
		}



		const inline std::shared_ptr<ITexture> getMaskTexture() const { return _maskTexture; }
		const inline std::shared_ptr<ITexture> getDiffuseTexture() const { return _diffuseTexture; }
		const inline std::shared_ptr<ITexture> getNormalTexture() const { return _normalTexture; }


		// Set Mask Texture
		inline Material & setMaskTexture(const std::shared_ptr<ITexture> & tex)
		{
			_maskTexture = tex;
			return *this;
		}

		// Set Diffuse Texture
		inline Material & setDiffuseTexture(const std::shared_ptr<ITexture> & tex)
		{
			_diffuseTexture = tex;
			return *this;
		}

		// Set Normal Texture
		inline Material & setNormalTexture(const std::shared_ptr<ITexture> & tex)
		{
			_normalTexture = tex;
			return *this;
		}



	private:
		// General
		std::string _name;			// May not be needed at all ... 

		// Color
		Float _opacity = 1.0f;		// Opacity of the material

		MatColor _ambient{ 0.0f, 0.0f, 0.0f };			// Ambient Color
		MatColor _diffuse{ 1.0f, 1.0f, 1.0f };			// Diffuse Color
		MatColor _specular{ 0.0f, 0.0f, 0.0f };			// Specular Color
		MatColor _emissive{ 0.0f, 0.0f, 0.0f };			// Emissive Color [Self illiminating]

		Float _shininess = 0.0f;						// Specular Exponent
		Float _reflectivity = 0.0f;						// Environment Reflectivity

		// Texturing
		std::shared_ptr<ITexture> _maskTexture;			// Mask Texture
		std::shared_ptr<ITexture> _diffuseTexture;		// Diffuse Texture
		std::shared_ptr<ITexture> _normalTexture;		// Normal Texture
	};
}


#endif