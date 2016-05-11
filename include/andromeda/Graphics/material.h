#ifndef _ANDROMEDA_GRAPHICS_MATERIAL_H_
#define _ANDROMEDA_GRAPHICS_MATERIAL_H_

#include <memory>
#include <string>

#include <andromeda/stddef.h>

#include <andromeda/glm.h>



namespace andromeda
{
	class Texture;

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

		/*
		
		*/
		Material()
		{

		}

		/*
		
		*/
		Material(const std::string & name) 
			: _name(name)
		{
		}
		
		virtual ~Material() {}

		/* Binds the Material to the shader -- This will probably be unneeded */
		void bind();

		/* Set Material Name */
		inline Material & setName(const std::string & name)
		{
			_name = name;
			return *this;
		}

		/* Set Opacity */
		inline Material & setOpacity(Float opacity)
		{
			_opacity = opacity;
			return *this;
		}


		const inline MatColor & getAmbient() { return _ambient; }
		const inline MatColor & getDiffuse() { return _diffuse; }
		const inline MatColor & getSpecular() { return _specular; }

		/* Set Ambient Color */
		inline Material & setAmbient(const MatColor & ambient)
		{
			_ambient = ambient;
			return *this;
		}

		/* Set Ambient Color */
		inline Material & setAmbient(Float r, Float g, Float b)
		{
			_ambient = glm::vec3(r, g, b);
			return *this;
		}


		/* Set Diffuse Color */
		inline Material & setDiffuse(const MatColor & diffuse)
		{
			_diffuse = diffuse;
			return *this;
		}

		/* Set Diffuse Color */
		inline Material & setDiffuse(Float r, Float g, Float b)
		{
			_diffuse = glm::vec3(r, g, b);
			return *this;
		}


		/* Set Specular Color */
		inline Material & setSpecular(const MatColor & specular)
		{
			_specular = specular;
			return *this;
		}

		/* Set Specular Color */
		inline Material & setSpecular(Float r, Float g, Float b)
		{
			_specular = glm::vec3(r, g, b);
			return *this;
		}
		



		inline Material & setDiffuseTexture(const std::shared_ptr<Texture> & tex)
		{
			_diffuseTexture = tex;
			return *this;
		}
		inline Material & setNormalTexture(const std::shared_ptr<Texture> & tex)
		{
			_normalTexture = tex;
			return *this;
		}



	private:
		// General
		std::string _name;			// May not be needed at all ... 

		// Color
		Float _opacity = 1.0f;		// Opacity of the material

		MatColor _ambient;			// Ambient Color
		MatColor _diffuse;			// Diffuse Color
		MatColor _specular;			// Specular Color

		// Texturing
		std::shared_ptr<Texture> _diffuseTexture;	// Diffuse Texture
		std::shared_ptr<Texture> _normalTexture;	// Normal Texture

	};
}


#endif