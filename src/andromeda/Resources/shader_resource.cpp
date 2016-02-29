#include <andromeda/Graphics/shader.h>

#include <andromeda/opengl.h>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
GLuint andromeda::CompileShader(const std::string & filename, GLenum type)
{
	// Create Shader Handle
	GLuint handle = glCreateShader(type);

	// Compile
	//const Char * src = source.c_str();
	std::string source = andromeda::LoadFile(filename);
	const Char * src = source.c_str();

	// Load Source and Compile
	glShaderSource(handle, 1, (const GLchar**)&src, NULL);
	glCompileShader(handle);

	// Check for Errors
	GLint compiled = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
		log_err("Error Compiling Shader.", filename);
	else
		log_debug("Shader Compiled. Handle =", handle);

	// Output Log
	GLint len = 0;
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);
	if (len)
	{
		Char * log = new Char[len];
		if (log)
		{
			glGetShaderInfoLog(handle, len, &len, log);

			if (len != 0)
				log_debug("# Shader Log:\n", log);

			delete[] log;
		}
	}

	// Failed Compilation, Delete
	if (!compiled)
	{
		glDeleteShader(handle);

		return 0;
	}

	return handle;
}



/*

*/
std::shared_ptr<Shader> andromeda::LoadShader(const std::string & vsFilename, const std::string & fsFilename)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();

	// Compile Shader
	GLuint vs = andromeda::CompileShader(vsFilename, GL_VERTEX_SHADER);
	GLuint fs = andromeda::CompileShader(fsFilename, GL_FRAGMENT_SHADER);

	if (vs != 0 && fs != 0)
	{
		// Create Shader
		//	shader->create();

		// Attach Shaders
		shader->attach(vs, GL_VERTEX_SHADER);
		shader->attach(fs, GL_FRAGMENT_SHADER);

		// Link
		shader->link();
	}

	if (vs)
		glDeleteShader(vs);

	if (fs)
		glDeleteShader(fs);

	return shader;
}