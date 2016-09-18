#include "geometry_environment.h"

#include <andromeda/Graphics/texture.h>
#include <andromeda/Graphics/effect.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::deferred;

/*

*/
DeferredGeometryEnvironment::DeferredGeometryEnvironment()
{

}


/*

*/
DeferredGeometryEnvironment::~DeferredGeometryEnvironment()
{

}



/*

*/
void DeferredGeometryEnvironment::begin(const IShader * shader)
{

	if (_enviromentReflection)
	{
		_enviromentReflection->bind(10);

		/*
			TODO: Setup Texture Annotations
		*/
		shader->setUniform("u_envReflection", 10);
	}

	

}

/*

*/
void DeferredGeometryEnvironment::end(const IShader * shader)
{
	if (_enviromentReflection)
	{
		_enviromentReflection->unbind(10);
	}
}