#include "directional_light.h"

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Renderer/graphics_state.h>

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredDirectionalLight::DeferredDirectionalLight(const std::shared_ptr<LightDirectional> & directional)
	: _light(directional)
{
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
	render():

*/
void DeferredDirectionalLight::render(GraphicsState & state)
{
	// Set Identity Matrix
	state.setModelMatrix();



	// Bind Shadow Map
	if (_shadowMap)
		_shadowMap->bind(20);

	// Set Other Attributes
	glm::mat4 biasMatrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0);

	// Precalculate
	glm::mat4 biasMVP = biasMatrix * _lightMatrix;

	// Set Light Attributes
	if (_light)
		state.setLight(*_light.get());

	// Light Matrices
	//rs.setUniform("u_lightShadow", !!_shadowMap);	// Casts Shadow :: IE Do Shadow Mapping
	state.setUniform("u_lightShadowMatrix", biasMVP);
	
	// TODO :: This should be part of the Light Class
	// Shadow Map
	//rs.setUniform("u_lightShadowMap", 20);	//20 = Texture Annotation .... <,<



	// Render Full Screen Quad
	_geometry->render();


	// Unbind Shadow Map
	if (_shadowMap)
		_shadowMap->unbind(20);

	/*
		To Process Lighting in the Fragment Shader, the following is needed:

		Global: (Handled by layer environment)
		- GBuffer			: Numerous textures defining the geometry @ the pixel level.

		Light: (Handled by the renderable)
		- ShadowMap			: DepthTexture
		- Light Matrices	: Camera matrices used to generate the shadow map
		- Light Data		: Color, Intensity, Shadowed, etc
		- Geometry			: This is used to define the "area" of the screen that needs lighting calculations done.
	*/

}















