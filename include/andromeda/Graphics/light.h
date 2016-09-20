#pragma once

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/Utilities/observer_v2.h>

namespace andromeda
{
	/*
		TODO:
		This needs to be observable.
		If shadowing is disabled, or the light moves, turned off etc. Then notifications need to be dispatched
		at the very least so the renderer can disable/remove shadow the pass

		TODO:
		Lights that cast shadows have a matrix -- that is used to render the scene from PoV of the light.
		Store it here -- and updating it whenever their is a change to the lights position/direction
		This will allow it to be assigned to the shader at the same time the light is "Set"
	*/



	enum class LightMessage
	{
		Enable,
	};
	



	class Light //: virtual public ObservableEx<Light, LightMessage>
	{
	public:
		typedef glm::vec3 LightColor;

	public:
		Light(){}
		virtual ~Light() {}
		

		// Set Enabled
		inline void setEnabled(Boolean enabled) { _enabled = enabled; }



		
		inline Boolean getEnabled() const { return _enabled; }
	


		// Set Ambient Color
		inline void setAmbient(const glm::vec3 & ambient)
		{
			_ambient = ambient;
		}

		// Set Ambient Color
		inline void setAmbient(Float r, Float g, Float b)
		{
			_ambient = glm::vec3(r, g, b);
		}

		// Set Diffuse Color
		inline void setDiffuse(const glm::vec3 & diffuse)
		{
			_diffuse = diffuse;
		}

		// Set Diffuse Color
		inline void setDiffuse(Float r, Float g, Float b)
		{
			_diffuse = glm::vec3(r, g, b);
		}

		// Set Specular Color
		inline void setSpecular(const glm::vec3 & specular)
		{
			_specular = specular;
		}

		// Set Specular Color
		inline void setSpecular(Float r, Float g, Float b)
		{
			_specular = glm::vec3(r, g, b);
		}


		inline const glm::vec3 & getAmbient() const { return _ambient; }
		inline const glm::vec3 & getDiffuse() const { return _diffuse; }
		inline const glm::vec3 & getSpecular() const { return _specular; }


		// Set Cast Shadow
		inline void setCastsShadow(Boolean castsShadow) { _shadow = castsShadow; }

		inline Boolean getCastsShadow() const { return _shadow; }


	private:
		Boolean _enabled = true;
		Boolean _shadow = true;

		LightColor _ambient{ 0.1f, 0.1f, 0.1f };
		LightColor _diffuse{ 1.0f, 1.0f, 1.0f };
		LightColor _specular{ 1.0f, 1.0f, 1.0f };
	};


	/*
	
	*/
	class LightDirectional : virtual public Light
	{
	public:
		LightDirectional(){}
		virtual ~LightDirectional(){}

		// Set Direction
		inline void setDirection(const glm::vec3 & direction)
		{
			_direction = glm::normalize(direction);
		}

		inline void setDirection(Float dx, Float dy, Float dz)
		{
			_direction = glm::normalize(glm::vec3(dx, dy, dz));
		}

		inline const glm::vec3 & getDirection() const { return _direction; }

	private:
		glm::vec3 _direction;
	};

}