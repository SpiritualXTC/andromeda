#include "x_shader.h"

#include <unordered_map>

#include <andromeda/Utilities/log.h>

#include "x_exception.h"

using namespace andromeda;
using namespace andromeda::xeffect;



GLenum XShader::GetShaderType(XShaderType type)
{
	// TODO: Move this to somewhere more appriopriate (This could be part of the Graphics API)
	static std::unordered_map<XShaderType, GLenum> nodeName =
	{
		{ XShaderType::Vertex, GL_VERTEX_SHADER },
		{ XShaderType::Fragment, GL_FRAGMENT_SHADER },
		{ XShaderType::Geometry, GL_GEOMETRY_SHADER }
	};

	const auto & it = nodeName.find(type);
	return it == nodeName.end() ? GL_INVALID_ENUM : it->second;
}






/*

*/
XShader::XShader(XShaderType shaderType)
	: _shaderType(shaderType)
{

}

/*

*/
XShader::~XShader()
{
	release();
}


/*

*/
void XShader::release()
{
	// Delete Shader
	if (_handle != SHADER_INVALID_HANDLE)
		glDeleteShader(_handle);
	
	// Reset Handle
	_handle = SHADER_INVALID_HANDLE;

	return;
}


/*

*/
GLuint XShader::compile(const std::string & source)
{
	/*
		TODO:

		Implementation to inject values into the shader:
	*/

	// Release Existing Shader
	release();

	// Get Shader Type
	GLenum type = XShader::GetShaderType(_shaderType);


	if (type == GL_INVALID_ENUM)
		throw XShaderException("Invalid Shader Type");


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









/*

*/
XShaderProgram::XShaderProgram()
{

}


/*

*/
XShaderProgram::~XShaderProgram()
{
	release();
}



void XShaderProgram::release()
{
	// Delete Shader
	if (_handle != PROGRAM_INVALID_HANDLE)
		glDeleteProgram(_handle);

	// Reset Handle
	_handle = PROGRAM_INVALID_HANDLE;
	_linked = false;
}



/*

*/
Boolean XShaderProgram::create()
{
	release();

	_handle = glCreateProgram();

	return isValid();
}


/*

*/
Boolean XShaderProgram::attach(std::shared_ptr<XShader> & shader)
{
	assert(isValid());
	assert(! isLinked());
	assert(shader);
	assert(shader->isValid());

	glAttachShader(_handle, shader->handle());

	return true;
}


/*

*/
GLuint XShaderProgram::link()
{
	assert(! isLinked());

	// Link
	glLinkProgram(_handle);

	GLint linked;
	glGetProgramiv(_handle, GL_LINK_STATUS, &linked);
	if (! linked)
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


/*

*/
Boolean XShaderProgram::apply()
{
	assert(isValid());

	glUseProgram(handle());

	return isValid();
}