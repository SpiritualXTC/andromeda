#pragma once

#include <cassert>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/graphics/effect.h>
#include <andromeda/Graphics/material.h>
#include <andromeda/Graphics/light.h>

#include <andromeda/Renderer/camera.h>

namespace andromeda
{




	/*
		This is a temp class
		It is to be used until shader annotations are setup

		Annotations may just go through this class
		Central point to change things... related to the shader

		This is at the "pass" level
	*/
	class GraphicsState : public IShader
	{
	private:
		// Matrices
		const std::string PROJECTION_MATRIX = "u_projection";
		const std::string VIEW_MATRIX = "u_view";
		const std::string MODEL_MATRIX = "u_model";
		const std::string NORMAL_MATRIX = "u_normalMatrix";

		const std::string VIEWMODEL_MATRIX = "u_modelview";

		// Material
		const std::string MATERIAL_AMBIENT = "u_ambientMaterial";				// This is ignored when using the GBuffer
		const std::string MATERIAL_DIFFUSE = "u_diffuseMaterial";
		const std::string MATERIAL_SPECULAR = "u_specularMaterial";				// This needs to be added to the GBuffer once the "white" specular is working correctly :: Seems to be working correctly -- or im going insane :)
		const std::string MATERIAL_SHININESS = "u_shininessMaterial";	
		const std::string MATERIAL_REFLECTIVITY = "u_reflectivityMaterial";

		// Material Textures
		const std::string TEXTURE_DIFFUSE = "u_diffuseTexture";


		// Lighting
		const std::string LIGHT_AMBIENT = "u_lightAmbient";
		const std::string LIGHT_DIFFUSE = "u_lightDiffuse";
		const std::string LIGHT_SPECULAR = "u_lightSpecular";

		const std::string LIGHT_POSITION = "u_lightPosition";

		const std::string LIGHT_SHADOW = "u_lightShadow";
		const std::string LIGHT_SHADOW_MAP = "u_lightShadowMap";

		// Environment


		// GBuffer


	public:
		GraphicsState(const IShader * shader, const Camera * camera)
			: _shader(shader)
			, _camera(camera)
		{
			assert(_camera);
			assert(_shader);

			// Assign Matrices
			_projection = camera->getProjectionMatrix();
			_view = camera->getViewMatrix();


			// Initial Shader States
			_shader->setUniform(PROJECTION_MATRIX, _projection);
			_shader->setUniform(VIEW_MATRIX, _view);

			// Set Default Model Matrix
			setModelMatrix(glm::mat4(1.0f));
		}
		virtual ~GraphicsState(){}




		// Set Identity Model Matrix
		inline void setModelMatrix()
		{
			setModelMatrix(glm::mat4(1.0f));
		}

		// Set Model Matrix
		inline void setModelMatrix(const glm::mat4 & m) 
		{
			_model = m;
			_viewModel = _view * _model;
			_normalMatrix = glm::transpose(glm::inverse(glm::mat3(_model)));

			_shader->setUniform(MODEL_MATRIX, _model);
			_shader->setUniform(NORMAL_MATRIX, _normalMatrix);
			_shader->setUniform(VIEWMODEL_MATRIX, _viewModel);
		}





		// Set Material States
		inline void setMaterial(const Material & material)
		{
			setMaterialAmbient(material.getAmbient());
			setMaterialDiffuse(material.getDiffuse());
			setMaterialSpecular(material.getSpecular());
			setMaterialShininess(material.getShininess());
			setMaterialReflectivity(material.getReflectivity());

			if (material.getDiffuseTexture())
				setTextureDiffuse(0);
		}

		// Set Ambient Color
		inline void setMaterialAmbient(const glm::vec3 & v)
		{
			_shader->setUniform(MATERIAL_AMBIENT, v);
		}
		// Set Diffuse Color
		inline void setMaterialDiffuse(const glm::vec3 & v)
		{
			_shader->setUniform(MATERIAL_DIFFUSE, v);
		}
		// Set Specular Color
		inline void setMaterialSpecular(const glm::vec3 & v)
		{
			_shader->setUniform(MATERIAL_SPECULAR, v);
		}

		// Set Shininess
		inline void setMaterialShininess(Float f) 
		{
			_shader->setUniform(MATERIAL_SHININESS, f);
		}

		// Set Reflectivity
		inline void setMaterialReflectivity(Float f)
		{
			_shader->setUniform(MATERIAL_REFLECTIVITY, f);
		}


		// Set Diffuse Texture
		inline void setTextureDiffuse(Int32 bindIndex)
		{
			/*
				TODO: Texture Annotation ???
			*/
			_shader->setUniform(TEXTURE_DIFFUSE, bindIndex);
		}







		// Set Light
		inline void setLight(const LightDirectional & light)
		{
			setLightAmbient(light.getAmbient());
			setLightDiffuse(light.getDiffuse());
			setLightSpecular(light.getSpecular());

			setLightPosition(-light.getDirection());

			setLightShadowMap(light.getCastsShadow());
		}

		// Set Light Ambient Color
		inline void setLightAmbient(const glm::vec3 & v)
		{
			_shader->setUniform(LIGHT_AMBIENT, v);
		}
		// Set Light Diffuse Color
		inline void setLightDiffuse(const glm::vec3 & v)
		{
			_shader->setUniform(LIGHT_DIFFUSE, v);
		}
		// Set Light Specular Color
		inline void setLightSpecular(const glm::vec3 & v)
		{
			_shader->setUniform(LIGHT_SPECULAR, v);
		}
		// Set Light Position
		inline void setLightPosition(const glm::vec3 & v)
		{
			_shader->setUniform(LIGHT_POSITION, v);
		}
		// Set Light Shadow Map
		inline void setLightShadowMap(Boolean enabled)
		{
			_shader->setUniform(LIGHT_SHADOW, enabled);
			if (enabled)
				_shader->setUniform(LIGHT_SHADOW_MAP, 20);	//20 = Texture Annotation
		}




		// Pass through
		inline void setUniform(const std::string &name, const glm::mat3 &m) const override
		{
			_shader->setUniform(name, m);
		}
		inline void setUniform(const std::string &name, const glm::mat4 &m) const override
		{
			_shader->setUniform(name, m);
		}

		inline void setUniform(const std::string &name, const glm::fvec2 &v) const override
		{
			_shader->setUniform(name, v);
		}
		inline void setUniform(const std::string &name, const glm::fvec3 &v) const  override
		{
			_shader->setUniform(name, v);
		}
		inline void setUniform(const std::string &name, const glm::fvec4 &v) const  override
		{
			_shader->setUniform(name, v);
		}

		inline void setUniform(const std::string &name, const glm::ivec2 &v) const  override
		{
			_shader->setUniform(name, v);
		}
		inline void setUniform(const std::string &name, const glm::ivec3 &v) const  override
		{
			_shader->setUniform(name, v);
		}
		inline void setUniform(const std::string &name, const glm::ivec4 &v) const override
		{
			_shader->setUniform(name, v);
		}
		inline void setUniform(const std::string &name, const Float f) const override
		{
			_shader->setUniform(name, f);
		}
		inline void setUniform(const std::string &name, const Int32 i) const override
		{
			_shader->setUniform(name, i);
		}
		inline void setUniform(const std::string &name, const Boolean b) const override
		{
			_shader->setUniform(name, b);
		}


	private:
		const IShader * _shader = nullptr;
		const Camera * _camera = nullptr;


		glm::mat4 _projection;
		glm::mat4 _view;
		glm::mat4 _model;


		glm::mat4 _viewModel;			// View * Model
		
		glm::mat3 _normalMatrix;		// transpose(inverse(mat3(_viewModel)))
	};


}
