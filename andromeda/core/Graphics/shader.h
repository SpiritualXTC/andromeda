#pragma once

#include <string>

#include <common/glm.h>
#include <common/types.h>

namespace andromeda
{
	class IShader
	{
	public:
		IShader() {}
		virtual ~IShader() {}

		/*
		TODO:

			Logically, Should these even be const functions?
			They dont change the state of class itself -- yet are still "setters"
		*/

		// Matrices
		virtual inline void setUniform(const std::string &name, const glm::mat3 &m) const = 0;
		virtual inline void setUniform(const std::string &name, const glm::mat4 &m) const = 0;

		// Float Vec
		virtual inline void setUniform(const std::string &name, const glm::fvec2 &v) const = 0;
		virtual inline void setUniform(const std::string &name, const glm::fvec3 &v) const = 0;
		virtual inline void setUniform(const std::string &name, const glm::fvec4 &v) const = 0;

		// Int Vec
		virtual inline void setUniform(const std::string &name, const glm::ivec2 &v) const = 0;
		virtual inline void setUniform(const std::string &name, const glm::ivec3 &v) const = 0;
		virtual inline void setUniform(const std::string &name, const glm::ivec4 &v) const = 0;

		// Primitives
		virtual inline void setUniform(const std::string &name, const Float f) const = 0;
		virtual inline void setUniform(const std::string &name, const Int32 i) const = 0;
		virtual inline void setUniform(const std::string &name, const Boolean b) const = 0;

		// TODO:: This one is special :: Remove it :)
		//virtual const inline void setUniformTexture(const std::string &name, UInt32 bindIndex) const = 0;
		// TODO:: Add, one for TextureAnnotations
	};

}