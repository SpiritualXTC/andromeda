#include "deferred_environment.h"

#include <andromeda/Graphics/texture.h>
#include <andromeda/Graphics/effect.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::deferred;

/*

*/
DeferredEnvironment::DeferredEnvironment()
{

}


/*

*/
DeferredEnvironment::~DeferredEnvironment()
{

}



/*

*/
void DeferredEnvironment::begin(const IShader * shader)
{

	if (_enviromentReflection)
	{
		_enviromentReflection->bind(10);

		/*
			TODO: Setup Texture Annotations
		*/
		shader->setUniformTexture("u_envReflection", 10);
	}

	

}

/*

*/
void DeferredEnvironment::end(const IShader * shader)
{
	if (_enviromentReflection)
	{
		_enviromentReflection->unbind(10);
	}
}