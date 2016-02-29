#include <andromeda/Renderer/view.h>

#include <glm/gtc/constants.hpp>

#include <andromeda/Game/camera.h>

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/pass.h>
#include <andromeda/Graphics/render_target.h>
#include <andromeda/Graphics/shader.h>

#include <andromeda/Renderer/renderable.h>
#include <andromeda/Renderer/render_list.h>
#include <andromeda/Renderer/scene_graph.h>


#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
View::View(Int32 layer) : View(0.0f, 0.0f, 1.0f, 1.0f, layer)
{

}


/*

*/
View::View(Float x, Float y, Float width, Float height, Int32 layer)
	: _layer(layer)
{
	_view = Region2f({ x, y }, { width + x, height + y });


	_projection = glm::mat4(1.0f);

	// Create Camera
	_camera = std::shared_ptr<Camera>(new Camera());

	/*
		TEMPORARY
	*/
	// Create a Shader
	//std::shared_ptr<andromeda::Shader> shader = andromeda::Shader::LoadShader("../res/shader/shader.vs", "../res/shader/shader.fs");

	// Create a Default Pass
	//std::shared_ptr<Pass> p = std::make_shared<Pass>(shader);
	//_passes.push_back(p);
	_effect = LoadEffect("../res/xml/effect.xml");
}



View::View(std::shared_ptr<IRenderTarget> target)
	: View(0, 0, 1, 1, View::Target)
{
	_target = target;

}



/*

*/
View::~View()
{

}


/*

*/
void View::resize(const Int32 width, const Int32 height)
{
	
	if (!_target)
	{
		// Recalculate Screen Region
		glm::fvec2 dim(width, height);

		_screen.minimum = _view.minimum * dim;
		_screen.maximum = _view.maximum * dim;
	}
	else
	{
		// This shouldn't change... but... shrugs!
		glm::fvec2 dim(_target->width(), _target->height());

		_screen.minimum = _view.minimum * dim;
		_screen.maximum = _view.maximum * dim;
	}


	// Recalculate Projection Matrix
	glm::ivec2 scrDim = _screen.size();

	Float aspect = (Float)scrDim.x / (Float)scrDim.y;

	_projection = glm::perspectiveFov(glm::pi<Float>() / 4.0f, (Float)scrDim.x, (Float)scrDim.y, 0.0001f, 100.0f);


	//	_projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -100.0f, 100.0f);

	return;
}



/*

*/
//void View::render(std::shared_ptr<RenderList> renderables)
void View::render(std::shared_ptr<SceneGraph> scene)
{
	assert(scene);
	assert(_effect);

	// Nothing to render....
//	if (!renderables)
//		return;
	
	// View Matrix
//	

	// Bind the RenderTarget if it exists
	if (_target)
	{
		_target->bindFrame();
	}


	Int32 passIndex = 0;

	// Set Viewport
	glViewport(_screen.minimum.x, _screen.minimum.y, _screen.maximum.x, _screen.maximum.y);


	// Clear the RenderTarget if it exists
	if (_target)
		_target->clear();


	// Loop through all techniques!
	for (auto it : *_effect)
	{
		std::shared_ptr<Technique> technique = it.second;





	//	if (_effect && _effect->hasActiveTechnique())
	//	{
			// Get Render Group ID.

			// Pre-process the Render Group (No Idea what this will entail. Probs just building matices)
			// Pull a List from the SceneGraph ?

			// FOR_EACH Pass
			//	 Render the Group!



			Int32 count = technique->numPasses();
			for (Int32 i = 0; i < count; ++i)
			{
				// Begin Pass
				if (technique->beginPass(i))
				{

					// Get Shader : THIS IS A HACK!
					std::shared_ptr<Shader> shader = technique->shader();

					// Get View Matrix
					glm::mat4 view = _camera->calcMatrix();

					// Set Projection Matrix
					shader->setUniformMat4("u_projection", _projection);

					// Set ModelView Matrix [This should be different for every object. Matrix Stack :)
					//shader->setUniformMat4("u_modelview", _camera->matrix());

					// shader->setProjectMatrix(_projection); ??
					// shader->setViewMatrix(_view);


					// Set up Lighting


					scene->render(technique->group(), shader.get(), view);

					// Iterate through Renderables
					//		for (auto renderable : *renderables)
					//		{
					// Render the Renderable
					//			renderable->render(passIndex, shader.get(), view);

					//		}



					// End Pass
					technique->endPass();
				}
//			}
		}
	}


	if (_target)
		_target->unbindFrame();
}


