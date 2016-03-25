#include <andromeda/Renderer/layer.h>

#include <andromeda/Game/camera.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/renderable.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Layer::Layer(const std::string & effectFile)
{
	log_warn("Creating default effect");
	_effect = std::make_shared<Effect>();

}



/*

*/
Layer::~Layer()
{

}


/*

*/
//Boolean Layer::addRenderable(std::shared_ptr<IRenderable> renderable)
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
//Boolean Layer::removeRenderable(std::shared_ptr<IRenderable> renderable)
Boolean Layer::removeRenderable(IRenderable * renderable)
{
	if (renderable == nullptr)
		return false;

	// TEMP, remove the renderable immediately
	_renderables.erase(renderable);

	return true;
}




/*

*/
Boolean Layer::render(std::shared_ptr<IProjection> projection, const std::shared_ptr<ICamera> camera, const std::string & technique)
{
	// Get Effect
//	std::shared_ptr<Effect> effect = _effect.lock();

	assert(_effect);
	
	// Begin the Technique :: Ignore Technique Name for now
	_effect->beginTechnique(/*technique*/);


	// Push Projection Matrix to Effect :: Constant for a Layer
	_effect->setUniformMat4("u_projection", projection->matrix());

	// Push Lighting :: Constant for a Layer


	// Setup Matrix Stack :: Initialise with Camera View Matrix 
	// Camera needs to be Rewritten
	MatrixStack ms(camera->matrix());
	
	

	

	// Loop through Passes
	Int32 passes = _effect->getNumPasses();
	for (Int32 i = 0; i < passes; ++i)
	{
		// Begin the Pass
		_effect->beginPass(i);

		// Iteration 1: 
		/*
			Render all Objects for each pass!
		*/
		

		// Render Objects With This Effect
		for (const auto renderable : _renderables)
		{


			// Render the Renderable
			renderable->render(_effect, ms);		// Pass

		}


		// Iteration 2:
		/* 
			When the object is on screen, and wasn't on screen last frame 
			 - Append renderables to appropriate layers

			When the object is off screen, and was on screen last frame
			 - Remove renderables from appropriate layers

			This should PROBABLY be associated with the SCENE ???
		*/





		// End the Pass
		_effect->endPass();
	}

	return true;
}