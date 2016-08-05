#include "deferred_directional_light.h"

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Math/matrix_stack.h>

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredRendererDirectionalLight::DeferredRendererDirectionalLight()
{
	_lightDirection = glm::vec3(-0.5, -0.7, -0.7);
	_lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);


	// Setup FullScreen Quad
	glm::vec3 pos[] =
	{
		{-1, 1, 0},
		{1, 1, 0},
		{-1, -1, 0},
		{ 1, -1, 0 }
	};

	glm::vec2 tex[] = 
	{
		{0, 1},
		{1, 1},
		{0, 0},
		{1, 0}
	};

	UInt32 ind[] = { 0, 1, 2, 2, 1, 3 };


	GeometryBuilder gb;

	// Add Vertex Data
	gb.addVertexData("pos", pos, 4, GeometryLocation::Position);
	gb.addVertexData("tex", tex, 4, GeometryLocation::Texture0);

	gb.setIndexData(ind, 6);


	// Build Geometry
	_geometry = gb.build();
}



/*

*/
void DeferredRendererDirectionalLight::render(const std::shared_ptr<IShader> shader, MatrixStack & ms)
{
	// Configure Light Settings

	//glm::mat4 identity(1.0f);

	shader->setUniform("u_modelview", ms.top());

	// Render Full Screen Quad
	_geometry->render();
}
