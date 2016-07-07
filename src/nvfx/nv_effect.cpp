#include <nvfx/nv_effect.h>


#include <andromeda/andromeda.h>	//temp

#include <andromeda/Resources/resource_manager.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*
	TODO:
	- Fix Logging methods
	- Reimplement this to support the Effect interface
*/



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
	log_warnp("NVFX:: Include = %1%", incName);

	// Load File :: This won't load from the shader directory
	std::shared_ptr<andromeda::File> file = nullptr;// Andromeda::instance()->getResourceManager()->loadFile(incName, false);

	log_errp("NVFX needs to be restructured....... have fun with that :P");

	if (!file)
		log_errp("Unable to load Resource %1%", incName);
	else
		log_verbosep("%1%", file->data());

	// Read File
	//std::string contents = res->read();

	//log_debug(contents.c_str());

	if (buf == nullptr)
		log_debug("BUFFER IS NULL");
	else
		log_debugp("%1%", buf);


	Size length = file->length();
	
	
	// Allocate :: Deallocation occurs in nvFX ???
	buf = new char[length + 2];

	// Assign Pointer
	const char * pbuf = buf;

	// Copy Memory
	memcpy((void*)pbuf, file->data(), file->length());

	// Increment Pointer to end
	pbuf += file->length();

	// Append NTC
	memcpy((void*)&pbuf[0], "\0", 1);
	

	log_infop("%1%", buf);

	// BUG ??? This hack isn't needed when loading directly via a file
	fp = fopen("../res/shader/empty.txt", "r");
}


/*

*/
NVEffect::NVEffect()
{
	// Load File :: This is temporarily here
	//std::shared_ptr<andromeda::ResourceStream> res = ResourceManager::instance()->load("shader.glslfx");
	std::shared_ptr<andromeda::File> file = nullptr;// Andromeda::instance()->getResourceManager()->loadFile("shader/shader.glslfx", false);

	log_errp("NVFX needs to be restructured....... have fun with that :P");

	if (file)
	{
		log_warnp("Effect Loaded. Length = %1%", file->length());
	}
	else
		log_errp("File Reference is NULL");
	



	// Read Entire Contents
	//std::string contents = res->read();
	//log_info("File:", contents.c_str());

	if (!file)
	{
		log_errp("Unable to load Effect");
		return;
	}


	// This should prolly go "elsewhere"
	nvFX::setErrorCallback(errorCallbackFunc);
	nvFX::setMessageCallback(msgCallbackFunc);
	nvFX::setIncludeCallback(includeCallbackFunc);
	
	// Create the Container
	_effect = nvFX::IContainer::create("test");
	
	// Load Effect
	Boolean result = nvFX::loadEffect(_effect, file->data());

	if (result)
	{
		log_debug("Effect Loaded");
	}
	else
		log_err("Failed to load effect");

	// HACKITY-HACK
	shaderHack();

	// Validate Everything!
	result &= validate();
	
	// Show Output information
	//infoOutput();


	if (!result)
	{
		nvFX::IContainer::destroy(_effect);
		_effect = nullptr;
	}
}

/*

*/
NVEffect::~NVEffect()
{
	if (_effect)
		nvFX::IContainer::destroy(_effect);
	_effect = nullptr;
}


/*
	validate():

	Validates the shader
*/
Boolean NVEffect::validate()
{
	Boolean result = true;

	nvFX::ITechnique * technique = nullptr;
	for (aInt t = 0; technique = _effect->findTechnique(t); t++)
	{
		// Validate the Technique
		Boolean bt = technique->validate();

		result &= bt;

//		log_debug("Technique =", technique->getName());
//		log_debug("-> Valid=", bt);
//		log_debug("-> Passes = ", technique->getNumPasses());

		if (!bt)
			log_warnp("Technique: '%1%' Failed Validation", technique->getName());

		nvFX::IPass * pass = nullptr;
		for (aInt p = 0; pass = technique->getPass(p); ++p)
		{
			Boolean bp = pass->validate();
			
//			log_debug("--> Pass =", pass->getName());
			if (!bp)
				log_warnp("Technique: '%1%', Pass: %2% Failed Validation", technique->getName(), pass->getName());

			result &= bp;

		}
	}

	return result;
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
void NVEffect::shaderHack()
{
	// BUGFIX WHEN LOADING FROM SOURCE
	// HACKITY-HACK

	// The First unamed shader (global) shader has header information appended
	// This shader is then appended to every shader used.
	Boolean version = false;
	nvFX::IShader * shader = nullptr;
	for (aInt32 s = 0; shader = _effect->findShader(s); ++s)
	{
//		log_info("-> Shader =", shader->getName());
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
Boolean NVEffect::setActiveTechnique(const std::string & technique)
{
	_active = _effect->findTechnique(technique.c_str());
	return !_active;
}





/*

*/
Boolean NVEffect::beginTechnique(const std::string & technique)
{
	return setActiveTechnique(technique) & beginTechnique();
}


/*

*/
Boolean NVEffect::beginTechnique()
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
Boolean NVEffect::endTechnique()
{
	// Do Nothing
	return true;
}


/*

*/
Boolean NVEffect::beginPass(Int32 pass)
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
Boolean NVEffect::endPass()
{
	assert(_activePass);
	_activePass = nullptr;

	return true;
}


/*

*/
void NVEffect::infoOutput()
{
	assert(_effect);

	log_debug(_effect->getName());

	nvFX::ITechnique * technique = nullptr;
	for (aInt t = 0; technique = _effect->findTechnique(t); t++)
	{
		log_infop("Technique = '%1%', Passes=%2%", technique->getName(), technique->getNumPasses());

		nvFX::IPass * pass = nullptr;
		for (aInt p = 0; pass = technique->getPass(p); ++p)
		{
			log_infop("-> Pass = %1%", pass->getName());
		}
	}

	nvFX::IShader * shader = nullptr;
	for (aInt32 s = 0; shader = _effect->findShader(s); ++s)
	{
		log_infop("-> Shader = %1%", shader->getName());
		nvFX::IShaderEx * sh = shader->getExInterface();
		//log_infop("%1%", sh->getShaderCode());
	}

	nvFX::IUniform * uniform = nullptr;
	for (aInt u = 0; uniform = _effect->findUniform(u); ++u)
	{
		log_infop("-> Uniforms = %1%", uniform->getName());
	}

	

	nvFX::ICstBuffer * buffer = nullptr;
	for (aInt c = 0; buffer = _effect->findCstBuffer(c); ++c)
	{
		log_infop("-> Buffer = %1%", buffer->getName());
	}
	
}


