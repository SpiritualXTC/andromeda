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
		

		inline Boolean getEnabled() const { return _enabled; }
		inline void setEnabled(Boolean enabled) { _enabled = enabled; }

		inline Boolean getCastsShadow() const { return _shadow; }
		inline void setCastsShadow(Boolean castsShadow) { _shadow = castsShadow; }


		// Set Ambient Color
		inline void setAmbient(const glm::vec3 & ambient)
		{
			_ambient = ambient;
		}

		// Set Diffuse Color
		inline void setDiffuse(const glm::vec3 & diffuse)
		{
			_diffuse = diffuse;
		}

		// Set Specular Color
		inline void setSpecular(const glm::vec3 & specular)
		{
			_specular = specular;
		}


		inline const glm::vec3 & getAmbient() const { return _ambient; }
		inline const glm::vec3 & getDiffuse() const { return _diffuse; }
		inline const glm::vec3 & getSpecular() const { return _specular; }



	private:
		Boolean _enabled = true;
		Boolean _shadow = true;

		LightColor _ambient;
		LightColor _diffuse;
		LightColor _specular;
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