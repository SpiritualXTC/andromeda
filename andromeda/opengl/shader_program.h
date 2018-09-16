#include <string>
#include <memory>

#include <core/Graphics/shader.h>

#include <GL/glew.h>

namespace andromeda
{
	namespace opengl
	{
		class ShaderGL;

		/*
		TODO: A Clearer state engine would make this easier to understand wtf is going on :)
		*/
		class ShaderProgramGL : public virtual IShader
		{
		public:
			static const GLuint PROGRAM_INVALID_HANDLE = 0xFFFFFFFF;

		public:
			ShaderProgramGL();
			virtual ~ShaderProgramGL();

			// Checks whether their is a valid handle 
			inline Boolean isValid() const { return _handle != PROGRAM_INVALID_HANDLE; }
			inline Boolean isLinked() const { return _linked; }

			// Creates the Program
			Boolean create();

			// Attach Shader 
			Boolean attach(std::shared_ptr<ShaderGL> & shader);

			// Link Program 
			GLuint link();

			// Apply the Shader
			Boolean apply();

			// Release Program 
			void release();

			// Get Handle 
			const inline GLuint handle() const { return _handle; }

			// Get Handle of a Uniform
			const GLint getUniformHandle(const std::string &name) const
			{
				return glGetUniformLocation(handle(), name.c_str());
			}



			inline void setUniform(const std::string & name, const glm::mat4 &m) const override
			{
				glUniformMatrix4fv(getUniformHandle(name), 1, false, glm::value_ptr(m));
			}

			inline void setUniform(const std::string & name, const glm::mat3 &m) const override
			{
				glUniformMatrix3fv(getUniformHandle(name), 1, false, glm::value_ptr(m));
			}


			inline void setUniform(const std::string &name, const glm::fvec2 &v) const override
			{
				glUniform2fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			inline void setUniform(const std::string &name, const glm::fvec3 &v) const override
			{
				glUniform3fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			inline void setUniform(const std::string &name, const glm::fvec4 &v) const override
			{
				glUniform4fv(getUniformHandle(name), 1, glm::value_ptr(v));
			}

			inline void setUniform(const std::string &name, const glm::ivec2 &v) const override
			{
				glUniform2iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			inline void setUniform(const std::string &name, const glm::ivec3 &v) const override
			{
				glUniform3iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}
			inline void setUniform(const std::string &name, const glm::ivec4 &v) const override
			{
				glUniform4iv(getUniformHandle(name), 1, glm::value_ptr(v));
			}

#if 0
			inline void setUniformTexture(const std::string &name, UInt32 bindIndex) const override
			{
				glUniform1i(getUniformHandle(name), bindIndex);
			}
#endif
			inline void setUniform(const std::string &name, const Float f) const override
			{
				glUniform1f(getUniformHandle(name), f);
			}
			inline void setUniform(const std::string &name, const Int32 i) const override
			{
				glUniform1i(getUniformHandle(name), i);
			}
			inline void setUniform(const std::string &name, const Boolean b) const override
			{
				glUniform1i(getUniformHandle(name), b);
			}

		private:

			GLuint _handle = PROGRAM_INVALID_HANDLE;

			Boolean _linked = false;
		};

	}
}