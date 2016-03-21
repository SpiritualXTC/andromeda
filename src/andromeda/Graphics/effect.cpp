#include <andromeda/Graphics/effect.h>

#include <andromeda/Resources/resource_manager.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


void errorCallbackFunc(const char *errMsg)
{
	log_err(errMsg);
}

void msgCallbackFunc(const char *msg)
{
	log_info(msg);
}

void includeCallbackFunc(const char *incName, FILE *&fp, const char *&buf)
{
	log_warn("NVFX:: Include = ", incName);

	// Load File
	std::shared_ptr<andromeda::ResourceStream> res = ResourceManager::instance()->load(incName);

	std::string contents = res->read();

	//log_debug(contents.c_str());

	if (buf == nullptr)
		log_debug("BUFFER IS NULL");
	else
		log_debug(buf);


	
	
	buf = new char[contents.length() + 2];


	const char * buffer = buf;

	memcpy((void*)buffer, contents.c_str(), contents.length());

	buffer += contents.length();
	memcpy((void*)&buffer[0], "\0", 1);
	
	log_info(buf);


	// BUG ???
	fp = fopen("../res/shader/empty.txt", "r");
}


/*

*/
Effect::Effect()
{
	// Load File
	std::shared_ptr<andromeda::ResourceStream> res = ResourceManager::instance()->load("shader.glslfx");

	// Read Entire Contents
	std::string contents = res->read();
	//log_info("File:", contents.c_str());


	// This should prolly go "elsewhere"
	nvFX::setErrorCallback(errorCallbackFunc);
	nvFX::setMessageCallback(msgCallbackFunc);
	nvFX::setIncludeCallback(includeCallbackFunc);
	


	// Create the Container
	_effect = nvFX::IContainer::create("test");

	nvFX::IContainerEx * effect = _effect->getExInterface();

	//log_infop("----\n%1%\n----", contents);

	
	
	// Load Effect
	Boolean result = nvFX::loadEffect(_effect, contents.c_str());
	//Boolean result = nvFX::loadEffectFromFile(_effect, "../res/shader/shader.glslfx");
	//Boolean result = nvFX::loadEffectFromFile(_effect, "../res/shader/simpleEffect1.glslfx");

	if (result)
	{
		log_debug("Effect Loaded");
	}
	else
		log_err("Failed to load effect");


	// HACKITY-HACK
	shaderHack();


	// Validate Everything!
	nvFX::ITechnique * technique = nullptr;
	for (aInt t = 0; technique = _effect->findTechnique(t); t++)
	{
		Boolean bt = technique->validate();

		result &= bt;

		log_debug("Technique =", technique->getName());
		log_debug("-> Valid=", bt);
		log_debug("-> Passes = ", technique->getNumPasses());
		
		if (!bt)
			log_warn("Technique:", technique->getName(), "Failed Validation");

		nvFX::IPass * pass = nullptr;
		for (aInt p = 0; pass = technique->getPass(p); ++p)
		{
			Boolean bp = pass->validate();

			log_debug("--> Pass =", pass->getName());
			if (!bp)
				log_warn("Technique:", technique->getName(), "Pass:", pass->getName(), "Failed Validation");

			result &= bp;

		}
	}


	

	
	// Show Output information
	infoOutput();



	if (!result)
	{
		nvFX::IContainer::destroy(_effect);
		_effect = nullptr;
	}


}

/*

*/
Effect::~Effect()
{
	if (_effect)
		nvFX::IContainer::destroy(_effect);
	_effect = nullptr;
}


/*
	shaderHack():

	A Hack that forces the version to GLSL/OpenGL 4.0, while allowing global GLSLShader blocks
	to be appended into shaders during compilation.

	Without this here, Error: "EC0408" will occur.
		#Version defined multiple times or not on first line

	ONLY WHEN LOADING FROM SOURCE. 
	WHEN LOADING FROM FILE THIS ISN'T REQUIRED.

	Bug in the nvFX Library (?)
		
*/
void Effect::shaderHack()
{
	// BUGFIX WHEN LOADING FROM SOURCE
	// HACKITY-HACK

	// The First unamed shader (global) shader has header information appended
	// This shader is then appended to every shader used.
	Boolean version = false;
	nvFX::IShader * shader = nullptr;
	for (aInt32 s = 0; shader = _effect->findShader(s); ++s)
	{
		log_info("-> Shader =", shader->getName());
		nvFX::IShaderEx * sh = shader->getExInterface();

		const char* name = shader->getName();
		if ((*name == '\0') && (shader->getType() == nvFX::TGLSL) && !version)
		{
			log_warn("Addition Shader Header Information appended to First 'Global' Shader...\n");

			sh->addHeaderCode("#extension GL_ARB_separate_shader_objects : enable");
			sh->addHeaderCode("#version 420");

			version = true;
		}
	}
}







/*

*/
Boolean Effect::setActiveTechnique(const std::string & technique)
{
	_active = _effect->findTechnique(technique.c_str());
	return !_active;
}





/*

*/
Boolean Effect::beginTechnique(const std::string & technique)
{
	return setActiveTechnique(technique) & beginTechnique();
}


/*

*/
Boolean Effect::beginTechnique()
{
	assert(_effect);

	// Select Default Technique
	if (_active == nullptr)
	{
		_active = _effect->findTechnique(0);
	}


	return ! _active;
}




/*

*/
Boolean Effect::endTechnique()
{
	// Do Nothing
	return true;
}


/*

*/
Boolean Effect::beginPass(Int32 pass)
{
	assert(! _activePass); /* Should be nullptr */

	//nvFX::PassInfo info;
	//nvFX::IPass * p = _active->getPass(pass, &info);

	// Get Pass
	_activePass = _active->getPass(pass);

	// Execute Pass
	_activePass->execute();
	
	return true;
}

/*

*/
Boolean Effect::endPass()
{
	assert(_activePass);
	_activePass = nullptr;

	return true;
}


/*

*/
void Effect::infoOutput()
{
	assert(_effect);

	log_debug(_effect->getName());

	nvFX::ITechnique * technique = nullptr;
	for (aInt t = 0; technique = _effect->findTechnique(t); t++)
	{
		log_info("Technique =", technique->getName(), ", Passes=", technique->getNumPasses());

		nvFX::IPass * pass = nullptr;
		for (aInt p = 0; pass = technique->getPass(p); ++p)
		{
			log_info("-> Pass =", pass->getName());
		}
	}

	nvFX::IShader * shader = nullptr;
	for (aInt32 s = 0; shader = _effect->findShader(s); ++s)
	{
		log_info("-> Shader =", shader->getName());
		nvFX::IShaderEx * sh = shader->getExInterface();
		//log_info(sh->getShaderCode());
	}

	nvFX::IUniform * uniform = nullptr;
	for (aInt u = 0; uniform = _effect->findUniform(u); ++u)
	{
		log_info("-> Uniforms =", uniform->getName());

		
	}

	

	nvFX::ICstBuffer * buffer = nullptr;
	for (aInt c = 0; buffer = _effect->findCstBuffer(c); ++c)
	{
		log_info("-> Buffer = ", buffer->getName());
	}
	
}


