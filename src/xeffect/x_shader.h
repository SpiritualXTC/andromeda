#pragma once

#include <string>

#include <andromeda/stddef.h>
#include <andromeda/graphics.h>


/*
	TODO:


	XShader, XShaderProgram

	should be part of the core graphics API, rather than the XEffect system. YES THIS. MOFO
*/


namespace andromeda
{
	namespace xeffect
	{
		// This should be part of the graphics header
		enum class XShaderType
		{
			// TODO: Tesselation shaders

			Vertex,
			// Tesselation1,	
			// Tesselation2,
			Geometry,
			Fragment,
		};






		/*
		
		*/
		class XShader
		{
		public:
			static const GLuint SHADER_INVALID_HANDLE = 0xFFFFFFFF;
			static GLenum GetShaderType(XShaderType shaderType);		// TODO: this can be moved to the central graphics routines

		public:
			XShader(XShaderType type);
			virtual ~XShader();

			/* Checks whether their is a valid handle */
			inline Boolean isValid() const { return _handle != SHADER_INVALID_HANDLE; }

			/* Compiles a Shader */
			GLuint compile(const std::string & source);

			/* Release Shader */
			void release();


			const inline GLuint handle() { return _handle; }

		private:
			XShaderType _shaderType;
			GLuint _handle = SHADER_INVALID_HANDLE;
		};








		/*
			TODO: A Clearer state engine would make this easier to understand wtf is going on :)
		*/
		class XShaderProgram : public virtual IShader
		{
		public:
			static const GLuint PROGRAM_INVALID_HANDLE = 0xFFFFFFFF;

		public:
			XShaderProgram();
			virtual ~XShaderProgram();

			/* Checks whether their is a valid handle */
			inline Boolean isValid() const { return _handle != PROGRAM_INVALID_HANDLE; }
			inline Boolean isLinked() const { return _linked; }

			// Creates the Program
			Boolean create();

		
			/* Attach Shader */
			Boolean attach(std::shared_ptr<XShader> & shader);


			/* Link Program */
			GLuint link();

			// Apply the Shader
			Boolean apply();

			/* Release Program */
			void release();

			/* Get Handle */
			const inline GLuint handle() const { return _handle; }




			/*
				TODO:
				Should these all be moved to the Graphics API??
			*/

			/* Get Handle of a Uniform  */
			const GLint getUniformHandle(const std::string &name) const
			{
				return glGetUniformLocation(handle(), name.c_str());
			}



			const inline void setUniform(const std::string & name, glm::mat4 &m) const override
			{
				glUniformMatrix4fv(getUniformHandle(name), 1, false, glm::value_ptr(m));
			}

			const inline void setUniform(const std::string &name, const glm::fvec2 &v) const override
			{
				glUniform2fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			const inline void setUniform(const std::string &name, const glm::fvec3 &v) const override
			{
				glUniform3fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			const inline void setUniform(const std::string &name, const glm::fvec4 &v) const override
			{
				glUniform4fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}

			const inline void setUniform(const std::string &name, const glm::ivec2 &v) const override
			{
				glUniform2iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			const inline void setUniform(const std::string &name, const glm::ivec3 &v) const override
			{
				glUniform3iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			const inline void setUniform(const std::string &name, const glm::ivec4 &v) const override
			{
				glUniform4iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}

			const inline void setUniformTexture(const std::string &name, UInt32 bindIndex) const override
			{
				glUniform1i(getUniformHandle(name), bindIndex);
			}



		private:



			GLuint _handle = PROGRAM_INVALID_HANDLE;

			Boolean _linked = false;
		};
	}
}