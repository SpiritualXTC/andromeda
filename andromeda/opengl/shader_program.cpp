#include "shader_program.h"

#include "common/log.h"

#include "shader.h"


using namespace andromeda;
using namespace andromeda::opengl;

ShaderProgramGL::ShaderProgramGL()
{

}

ShaderProgramGL::~ShaderProgramGL()
{
	release();
}

void ShaderProgramGL::release()
{
	// Delete Shader
	if (_handle != PROGRAM_INVALID_HANDLE)
		glDeleteProgram(_handle);

	// Reset Handle
	_handle = PROGRAM_INVALID_HANDLE;
	_linked = false;
}

Boolean ShaderProgramGL::create()
{
	release();

	_handle = glCreateProgram();

	return isValid();
}

Boolean ShaderProgramGL::attach(std::shared_ptr<ShaderGL> & shader)
{
	assert(isValid());
	assert(!isLinked());
	assert(shader);
	assert(shader->isValid());

	glAttachShader(_handle, shader->handle());

	return true;
}

GLuint ShaderProgramGL::link()
{
	assert(!isLinked());

	// Link
	glLinkProgram(_handle);

	GLint linked;
	glGetProgramiv(_handle, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint logLength;
		glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

		GLchar* log = new GLchar[logLength + 1];
		glGetProgramInfoLog(_handle, logLength, NULL, log);

		log_errp("Error Linking Program....");
		log_errp("%1%", log);

		delete[] log;

		// Release the Program
		release();
	}

	return _handle;
}

Boolean ShaderProgramGL::apply()
{
	assert(isValid());

	glUseProgram(handle());

	return isValid();
}