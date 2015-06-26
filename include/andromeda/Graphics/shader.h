#ifndef _ANDROMEDA_GRAPHICS_SHADER_H_
#define _ANDROMEDA_GRAPHICS_SHADER_H_

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../stddef.h"

#include "opengl.h"

namespace andromeda
{
	class Shader
	{
	public:
		// Static
		static std::shared_ptr<Shader> LoadShader(const std::string & vsFilename, const std::string & fsFilename);

	protected:
		static GLuint CompileShader(const std::string & filename, GLenum type);


	public:
		Shader();
		virtual ~Shader();

		const inline Boolean isLinked() { return _linked; }


		void bind();
		void unbind();

		

		// Set Uniforms
		const inline void setUniformMat4(const std::string & name, const glm::mat4 &m) const
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
		}
		const inline void setUniformVec2(const std::string &name, const glm::vec2 &v)const
		{
			glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(v));
		}
		const inline void setUniformVec3(const std::string &name, const glm::vec3 &v)const
		{
			glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(v));
		}
		const inline void setUniformVec4(const std::string &name, const glm::vec4 &v)const
		{
			glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(v));
		}




	protected:
		void create();
		void destroy();
		Boolean attach(GLuint handle, GLenum type);
		Boolean link();



	private:
		/*
			Retrieve the location for a uniform
		*/
		const inline GLuint getUniformLocation(const std::string &name) const
		{
			return glGetUniformLocation(_program, name.c_str());
		}

		/*
			Retrieve the location for an attribute
		*/
		const inline GLuint getAttribLocation(const std::string &name) const
		{
			return glGetAttribLocation(_program, name.c_str());
		}


		void dumpLocations(GLenum locs);


		Boolean _linked = false;
		GLuint _program = 0;
	};
}


typedef andromeda::Shader aShader;

#endif