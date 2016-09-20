#include <andromeda/Renderer/layer.h>

#include <cassert>


#include <andromeda/Graphics/effect.h>

#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Math/projection_matrix.h>
#include <andromeda/Math/view_matrix.h>


#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/graphics_state.h>
#include <andromeda/Renderer/renderable.h>


#include "renderable_group.h"

#include <andromeda/Utilities/log.h>

using namespace andromeda;















/*

*/
Layer::Layer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<Effect> & effect, RenderableGroup * rg)
	: _camera(camera)
	, _effect(effect)
	, _renderGroup(rg)
{
	assert(_camera);
	assert(_effect);

	// Get Default Technique
	_technique = _effect->getTechniqueDefault();
}



/*

*/
Layer::~Layer()
{

}


/*
	Sets the Active Techqniue Used by a Layer
*/
Boolean Layer::setActiveTechnique(const std::string & technique)
{
	assert(_effect);

	// Get Technique
	if (_effect->hasTechnique(technique))
		_technique = _effect->getTechnique(technique);
	else
		return false;

	return ! _technique.expired();
}




#if 0
/*

*/
Boolean Layer::addExtension(const std::shared_ptr<ILayerExtension> & extension)
{
	assert(extension);

	_extensions.push_back(extension);

	return true;
}
#endif








/*
	
*/
Boolean Layer::render(ILayerEnvironment * environment)
{
	assert(_effect);
	assert(_camera);

	// Lock Technique
	std::shared_ptr<ITechnique> t = _technique.lock();

	if (t == nullptr)
		return false;

	// Iterate through passes
	for (Int32 i = 0; i < t->getNumPasses(); ++i)
	{
		// Get Pass
		std::shared_ptr<IPass> p = t->getPass(i);

		// Pass isn't valid.
		// Pass isn't enabled
		// Pass fails to Apply
		if (!p || !p->isEnabled() || !p->apply())
			continue;

		// Set Graphics States
		GraphicsState gs(p.get(), _camera.get());
		

		
		// Apply Environment Options
		// TODO: RenderEnvironment ?
		if (environment)
			environment->begin(gs);
		//	environment->begin(p.get());

		// Apply Extensions
//		for (const auto & ext : _extensions)
//			ext->begin(p);

		// Render the RenderGroup
		if (_renderGroup)
			_renderGroup->render(gs);

		// Apply Environment Options
		if (environment)
			environment->end(gs);
			//environment->end(p.get());

//		for (const auto & ext : _extensions)
//			ext->end(p);
	}

	return true;
}









