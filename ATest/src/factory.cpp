#include "factory.h"

#include <string>

#include <andromeda/Game/game_object.h>

#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/transform_component.h>


#include <andromeda/andromeda.h>
#include <andromeda/geometry.h>
#include <andromeda/graphics.h>

#include "plane_test_component.h"
#include "circular_path_component.h"


using namespace andromeda;



/*

*/
std::shared_ptr<andromeda::GameObject> Factory::createCube()
{
	static Int32 counter = 0;

	counter++;

	std::stringstream name("cube_");
	name << counter;

	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name.str());

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	// Add Standard Components
	obj->addComponent<andromeda::TransformComponent>(transform);


	// Create Material
	std::shared_ptr<andromeda::Texture> tex = andromeda::LoadResource<andromeda::Texture>("pattern0.png");
	andromeda::Material material;

	material.setDiffuse(1, 1, 1)
		.setDiffuseTexture(tex);


	// Temp Visualisation for GBuffer
	andromeda::geometry::Cube geom;

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, material, transform);

		obj->addComponent<andromeda::RenderComponent>(render);
	}

	return obj;
}



/*

*/
std::shared_ptr<andromeda::GameObject> Factory::createSphere(aFloat angle)
{
	static Int32 counter = 0;

	counter++;

	std::stringstream name("sphere_");
	name << counter;




	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>(name.str());

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();


	// Add Components
	obj->addComponent<andromeda::TransformComponent>(transform);

	// Setup Pathing
	std::shared_ptr<CircularPathComponent> circle = std::make_shared<CircularPathComponent>(obj->getComponentPtr<andromeda::TransformComponent>(), angle);
	obj->addComponent<CircularPathComponent>(circle);


	// Create Geometry
	andromeda::geometry::Ellipse geom(0.5f);
	geom.setSlices(32).setStacks(16);


	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::GeometryRenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		obj->addComponent<andromeda::GeometryRenderComponent>(render);

		render->getMaterial().setDiffuseTexture(andromeda::LoadResource<andromeda::Texture>("white.png"));

		// Add Plane Test Component
		std::shared_ptr<PlaneTestComponent> planeTest = std::make_shared<PlaneTestComponent>(render, transform);
		obj->addComponent<PlaneTestComponent>(planeTest);
	}
	else
		return nullptr;




	return obj;
}