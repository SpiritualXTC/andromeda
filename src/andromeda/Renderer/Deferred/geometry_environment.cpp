#include "geometry_environment.h"

#include <andromeda/Graphics/texture.h>
#include <andromeda/Graphics/effect.h>

#include <andromeda/Renderer/graphics_state.h>

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
void DeferredGeometryEnvironment::begin(GraphicsState & state)
{

	if (_enviromentReflection)
	{
		_enviromentReflection->bind(10);

		/*
		TODO: Setup Texture Annotations
		*/
		state.setUniform("u_envReflection", 10);
	}



}

/*

*/
void DeferredGeometryEnvironment::end(GraphicsState & state)
{
	if (_enviromentReflection)
	{
		_enviromentReflection->unbind(10);
	}
}