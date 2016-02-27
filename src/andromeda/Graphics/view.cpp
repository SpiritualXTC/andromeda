#include <andromeda/Graphics/view.h>

#include <glm/gtc/constants.hpp>


#include <andromeda/Graphics/camera.h>
#include <andromeda/Graphics/pass.h>
#include <andromeda/Graphics/renderable.h>
#include <andromeda/Graphics/render_list.h>
#include <andromeda/Graphics/shader.h>


#include <andromeda/Math/matrix_stack.h>



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

	_camera = std::shared_ptr<Camera>(new Camera());


	/*
		TEMPORARY
	*/
	// Create a Shader
	std::shared_ptr<andromeda::Shader> shader = andromeda::Shader::LoadShader("../res/shader/shader.vs", "../res/shader/shader.fs");

	// Create a Default Pass
	std::shared_ptr<Pass> p = std::make_shared<Pass>(shader);

	_passes.push_back(p);
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
	// Recalculate Screen Region
	glm::fvec2 dim(width, height);

	_screen.minimum = _view.minimum * dim;
	_screen.maximum = _view.maximum * dim;


	// Recalculate Projection Matrix
	glm::ivec2 scrDim = _screen.size();

	Float aspect = (Float)scrDim.x / (Float)scrDim.y;

	_projection = glm::perspectiveFov(glm::pi<Float>() / 4.0f, (Float)scrDim.x, (Float)scrDim.y, 0.0001f, 100.0f);

//	_projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -100.0f, 100.0f);

	return;
}



/*

*/
void View::render(std::shared_ptr<RenderList> renderables)
{
	// Nothing to render....
	if (!renderables)
		return;
	
	// View Matrix
//	

	


	Int32 passIndex = 0;

	// Set Viewport
	glViewport(_screen.minimum.x, _screen.minimum.y, _screen.maximum.x, _screen.maximum.y);

	// Iterate through Passes
	for (auto pass : _passes)
	{
		// Pass is Disabled? 
		if (!pass->isEnabled())
		{
			passIndex++;
			continue;
		}

		// Get Shader
		std::shared_ptr<Shader> shader = pass->shader();

		// Get View Matrix
		glm::mat4 view = _camera->calcMatrix();


		// Configure Pass
		pass->begin();

		// Set Projection Matrix
		shader->setUniformMat4("u_projection", _projection);

		// Set ModelView Matrix [This should be different for every object. Matrix Stack :)
		//shader->setUniformMat4("u_modelview", _camera->matrix());

		// shader->setProjectMatrix(_projection); ??
		// shader->setViewMatrix(_view);


		// Set up Lighting



		// Iterate through Renderables
		for (auto renderable : *renderables)
		{
			// Render the Renderable
			renderable->render(passIndex, shader.get(), view);

		}

		// End Pass
		pass->end();

		passIndex++;
	}



	
}

