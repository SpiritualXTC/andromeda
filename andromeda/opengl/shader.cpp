#include "shader.h"

#include <unordered_map>

#include "common/log.h"

using namespace andromeda;
using namespace andromeda::opengl;

GLenum ShaderGL::GetShaderType(ShaderType type)
{
	// TODO: Move this to somewhere more appriopriate (This could be part of the Graphics API)
	static std::unordered_map<ShaderType, GLenum> nodeName =
	{
		{ ShaderType::VertexShader, GL_VERTEX_SHADER },
		{ ShaderType::FragmentShader, GL_FRAGMENT_SHADER },
		{ ShaderType::GeometryShader, GL_GEOMETRY_SHADER }
	};

	const auto & it = nodeName.find(type);
	return it == nodeName.end() ? GL_INVALID_ENUM : it->second;
}

ShaderGL::ShaderGL(ShaderType shaderType)
	: _shaderType(shaderType)
{

}

ShaderGL::~ShaderGL()
{
	release();
}

void ShaderGL::release()
{
	// Delete Shader
	if (_handle != SHADER_INVALID_HANDLE)
		glDeleteShader(_handle);

	// Reset Handle
	_handle = SHADER_INVALID_HANDLE;

	return;
}

GLuint ShaderGL::compile(const std::string & source)
{
	// Release Existing Shader
	release();

	// Get Shader Type
	GLenum type = ShaderGL::GetShaderType(_shaderType);
	if (type == GL_INVALID_ENUM)
		throw ShaderException("Invalid Shader Type");

	// Create the Shader
	_handle = glCreateShader(type);

	// Get Source
	const GLchar * src = source.c_str();
	GLint length = source.length();

	// Attach Source to Shader
	glShaderSource(_handle, 1, &src, &length);

	// Compile
	glCompileShader(_handle);

	// Check Compile Status
	GLint compiled;

	glGetShaderiv(_handle, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint logLength;
		glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &logLength);

		GLchar* log = new GLchar[logLength + 1];
		glGetShaderInfoLog(_handle, logLength, NULL, log);

		//fprintf(stderr, "Compilation error in shader %s: %s\n", this->name, strInfoLog);
		log_errp("Error Compilating Shader...");
		log_errp("%1%", log);

		delete[] log;

		// It Failed, so release it.
		release();
	}

	return _handle;
}