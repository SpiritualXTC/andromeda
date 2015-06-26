#include <andromeda/Graphics/shader.h>

#include <cassert>

#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


using namespace andromeda;

/*
	Static
*/

/*

*/
std::shared_ptr<Shader> Shader::LoadShader(const std::string & vsFilename, const std::string & fsFilename)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();

	// Compile Shader
	GLuint vs = Shader::CompileShader(vsFilename, GL_VERTEX_SHADER);
	GLuint fs = Shader::CompileShader(fsFilename, GL_FRAGMENT_SHADER);

	if (vs != 0 && fs != 0)
	{
		// Create Shader
		shader->create();

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


/*

*/
GLuint Shader::CompileShader(const std::string & filename, GLenum type)
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
	Class
*/

/*

*/
Shader::Shader()
{

}

/*

*/
Shader::~Shader()
{
	destroy();
}



/*
	create();
*/
void Shader::create()
{
	assert(! _program);

	_program = glCreateProgram();
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
