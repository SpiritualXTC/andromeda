#include <andromeda/Graphics/Deprecated/shader.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
ShaderPartial::ShaderPartial(const std::string & source, GLenum type)
	: _type(type)
{
	// Get pointer to source
	const Char * src = source.c_str();

	// Create Shader Handle
	_handle = glCreateShader(_type);

	// Load Source and Compile
	glShaderSource(_handle, 1, (const GLchar**)&src, NULL);
	glCompileShader(_handle);

	// Check for Errors
	GLint compiled = 0;
	glGetShaderiv(_handle, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
		log_err("Error Compiling Shader.");
	else
		log_debug("Shader Compiled. Handle =", _handle);

	// Output Log
	GLint len = 0;
	glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &len);
	if (len)
	{
		Char * log = new Char[len];
		if (log)
		{
			glGetShaderInfoLog(_handle, len, &len, log);

			if (len != 0)
				log_debug("# Shader Log:\n", log);

			delete[] log;
		}
	}

	// Failed Compilation, Delete
	if (!compiled)
	{
		glDeleteShader(_handle);
		_handle = 0;
	}
}


/*

*/
ShaderPartial::~ShaderPartial()
{
	if (_handle != 0)
		glDeleteShader(_handle);
}