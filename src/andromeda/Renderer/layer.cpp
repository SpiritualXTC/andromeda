#include <andromeda/Renderer/layer.h>

#include <cassert>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/renderable.h>


#include "renderable_group.h"

#include <andromeda/Utilities/log.h>

using namespace andromeda;
















/*

*/
Layer::Layer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<Effect> & effect, const std::shared_ptr<RenderableGroup> rg)
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








/*
	
*/
Boolean Layer::render()
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

		// Set Projection Matrix
		p->setUniform("u_projection", _camera->getProjectionMatrix());

		// Render the RenderGroup
		if (_renderGroup)
			_renderGroup->render(_camera, p);
	}

	return true;
}
