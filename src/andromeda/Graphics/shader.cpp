#include <andromeda/Graphics/shader.h>

#include <cassert>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


using namespace andromeda;












/*
	Class
*/

/*

*/
Shader::Shader()
{
	_program = glCreateProgram();
}

/*

*/
Shader::~Shader()
{
	destroy();
}


/*
	destroy();
*/
void Shader::destroy()
{
	if (_program)
		glDeleteProgram(_program);
	_program = 0;

	return;
}


/*

*/
Boolean Shader::attach(GLuint handle, GLenum type)
{
	assert(! _linked);

	// Validate
	if (_program == 0 || handle == 0)
		return false;

	glAttachShader(_program, handle);

	return true;
}


/*
	
*/
Boolean Shader::attach(std::shared_ptr<ShaderPartial> partial)
{
	assert(!_linked);
	assert(_program);
	assert(partial);

	glAttachShader(_program, partial->handle());
	return true;
}





/*

*/
Boolean Shader::link()
{
	assert(!_linked);

	// Validate
	if (_program == 0)
		return false;

	// Link the Shader Program
	glLinkProgram(_program);

	// Validate for Linking Errors
	GLint linked = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		log_err("Error Linking Shader");

		GLint len = 0;

		// Get Length of _program Log
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &len);

		// Create Buffer
		Char * log = new Char[len];
		if (log)
		{
			// Get Program Log
			glGetProgramInfoLog(_program, len, &len, log);

			log_err("Shader Log:\n", log);

			// Delete Buffer
			delete[] log;
		}

		// Delete the Program
		glDeleteProgram(_program);

		return 0;
	}
	else
		log_debug("Shader Program Linked. Handle = ", _program);

	
	
	dumpLocations(GL_ACTIVE_UNIFORMS);
	dumpLocations(GL_ACTIVE_ATTRIBUTES);
	



	// Set Flag
	_linked = true;

	return true;
}




/*

*/
void Shader::bind()
{
	assert(_linked);

	if (_program == 0)
		return;

	glUseProgram(_program);
}


/*

*/
void Shader::unbind()
{
	assert(_linked);

	glUseProgram(0);

	return;
}




/*
	dumpLocations():

	Shader Debugging
*/
void Shader::dumpLocations(GLenum locs)
{
	assert(_program);

	const Int32 NAME_SIZE = 80;

	Char name[NAME_SIZE];


	GLint active = 0;

	if (!(locs == GL_ACTIVE_UNIFORMS || locs == GL_ACTIVE_ATTRIBUTES))
		return;

	glGetProgramiv(_program, locs, &active);


	// Setup Attributes
	for (int i = 0; i < active; ++i)
	{
		std::string s = name;
		GLint size = 0;
		GLenum type = 0;
		GLint len = 0;
		GLint handle = 0;



		if (locs == GL_ACTIVE_ATTRIBUTES)
		{
			glGetActiveAttrib(_program, i, NAME_SIZE, &len, &size, &type, name);
			handle = glGetAttribLocation(_program, name);
		}
		else if (locs == GL_ACTIVE_UNIFORMS)
		{
			glGetActiveUniform(_program, i, NAME_SIZE, &len, &size, &type, name);
			handle = glGetUniformLocation(_program, name);
		}
		log_verbose("\t", name, "=", handle);
	}
}
