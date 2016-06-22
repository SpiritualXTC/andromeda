#include <andromeda/Renderer/layer.h>


#include <andromeda/Graphics/effect.h>

#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/renderable.h>


#include <andromeda/Utilities/log.h>

using namespace andromeda;



// TODO: Remove this
// This is a temporary method to give an effect to a layer
#include <andromeda/andromeda.h>


/*

*/
Layer::Layer(std::shared_ptr<Effect> & effect)
	: _effect(effect)
{
	log_warn("Creating default effect");

	/*
		TODO:
		This needs to be redone.
		Effect needs to be injected from the View - Which Needs to be injected from the Application
	*/
}



/*

*/
Layer::~Layer()
{

}


/*

*/
Boolean Layer::addRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;
	
	// TEMP, just add the renderable immediately
	_renderables.insert(renderable);

	return true;
}

/*

*/
Boolean Layer::removeRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;

	// TEMP, remove the renderable immediately
	_renderables.erase(renderable);

	return true;
}








/*
	render():

	Renders the Layer
*/
Boolean Layer::render(std::shared_ptr<IProjection> projection, const std::shared_ptr<ICamera> camera)
{
	// Get Effect
//	std::shared_ptr<Effect> effect = _effect.lock();

	assert(_effect);
	
	// Get Technique Name :: Dont worry about for now






	// Begin the Technique 
	_effect->beginTechnique();

	// Push Projection Matrix to Effect :: Constant for a Layer
//	_effect->setUniformMat4("u_projection", projection->matrix());

	// Push Lighting :: Constant for a Layer


	// Setup Matrix Stack :: Initialise with Camera View Matrix 
	// Camera needs to be Rewritten
	MatrixStack ms(camera->matrix());
	
	

	/*
		NEW SYSTEM
	*/
	std::shared_ptr<ITechnique> t = _effect->getTechnique("t1");

	if (t != nullptr)
	{
		for (Int32 i = 0; i < t->getNumPasses(); ++i)
		{
			std::shared_ptr<IPass> p = t->getPass(i);

			if (!p->apply())
				continue;

			// Set Project Matrix
			p->setUniform("u_projection", projection->matrix());


			// Render Objects With This Effect
			for (const auto renderable : _renderables)
			{
				// Render the Renderable
				renderable->render(p, ms);
			}
		}
	}

	return true;
}