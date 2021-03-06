#include "factory.h"

#include <andromeda/andromeda.h>
#include <andromeda/geometry.h>
#include <andromeda/graphics.h>
#include <andromeda/resources.h>

#include <andromeda/Game/game_object.h>

#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Game/light_component.h>

#include <andromeda/Graphics/texture.h>

#include <andromeda/Resources/resource_factory.h>

#include <andromeda/Utilities/image.h>

#include "plane_test_component.h"
#include "circular_path_component.h"


using namespace andromeda;


/*

*/
std::shared_ptr<andromeda::GameObject> Factory::createSkybox()
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("skybox");


	// Load Cube Texture
	std::shared_ptr<andromeda::CubeTexture> cubeTex = andromeda::LoadCubeTexture("skybox");




	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
	obj->addComponent<andromeda::TransformComponent>(transform);



	// Create Material
	//std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("pattern0.png");
	andromeda::Material material;

	material.setDiffuse(1, 1, 1)
		.setDiffuseTexture(cubeTex);


	// Create Skybox Geometry (Inverted Cube)
	andromeda::geometry::Cube geom(500);

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(0);

	if (geometry)
	{
		std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, material, transform);

		render->setRenderGroup("background");

		obj->addComponent<andromeda::RenderComponent>(render);
	}

	return obj;
}



/*

*/
std::shared_ptr<andromeda::GameObject> Factory::createGround()
{
	andromeda::geometry::SurfaceFunctionLambda<> lamb(
		[&](aFloat x, aFloat z)
	{
		aFloat fx = 100.0f * x;
		aFloat fy = -8.0f;
		aFloat fz = 100.0f * z;

		fy += sinf(x * glm::pi<aFloat>() * 10.0f) * 1.0f;
		fy += sinf(z * glm::pi<aFloat>() * 10.0f) * 2.0f;

		fy += sinf(x * glm::pi<aFloat>() * 4.0f) * 2.0f;
		fy += sinf(z * glm::pi<aFloat>() * 4.0f) * 1.0f;

		fy += sinf((x + z) * glm::pi<aFloat>() * 20.0f) * 0.5f;

//		return glm::vec3(fx, -4.0f, fz);
		return glm::vec3(fx, fy, fz);
	});


	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("ground");

	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
	obj->addComponent(transform);

	// Create Material
	//std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("pattern0.png");
	std::shared_ptr<andromeda::Texture> tex = andromeda::resourceFactory()->getResource<andromeda::Texture>("pattern");
	andromeda::Material material;

	material.setDiffuse(1.0f, 1.0f, 1.0f)
		.setDiffuseTexture(tex);

	if (!tex)
	{
		log_err("No Texture for Ground");
	}


	aInt32 divisions = 250;

	// Create Geometry
	andromeda::geometry::Surface surface;
	surface.setDivisions(divisions, divisions)
		.setPositionFunction(&lamb);

	std::shared_ptr<andromeda::Geometry> geometry = surface.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);


	std::shared_ptr<andromeda::RenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, material, transform);
	render->setRenderGroup("terrain");
	obj->addComponent<andromeda::RenderComponent>(render);

	return obj;
}



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
	std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("white");
	andromeda::Material material;

	material.setDiffuse(1, 1, 1)
		.setDiffuseTexture(tex);
	material.setReflectivity(0.9f);

	// Temp Visualisation for GBuffer
#if 1
	andromeda::geometry::Cube geom(5.0f);
#else
	andromeda::geometry::Ellipse geom(5.0f);
	geom.setSlices(128).setStacks(64);
#endif
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
	circle->setRadius(8.0f);
	circle->setSpeed(0.25f);
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

		render->getMaterial().setDiffuseTexture(andromeda::LoadTexture("white"));

		// Add Plane Test Component
		std::shared_ptr<PlaneTestComponent> planeTest = std::make_shared<PlaneTestComponent>(render, transform);
		obj->addComponent<PlaneTestComponent>(planeTest);
	}
	else
		return nullptr;

	return obj;
}


/*

*/
std::shared_ptr<GameObject> Factory::createLight()
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>("globallight");

	// Create Components

	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();

	std::shared_ptr<andromeda::LightDirectionalComponent> ld = std::make_shared<andromeda::LightDirectionalComponent>(transform);

	ld->setDirection(-0.7f, -0.5f, -0.7f);
	ld->setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
	ld->setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));


	std::shared_ptr<CircularPathComponent> circle = std::make_shared<CircularPathComponent>(transform, 0.0f);
	circle->setRadius(10.0f);
	circle->setSpeed(0.125f);
	circle->setCenter(glm::vec3(0.0f, 10.0f, 0.0f));


	// Add Components
	go->addComponent<andromeda::TransformComponent>(transform);
	go->addComponent<andromeda::LightDirectionalComponent>(ld);
	go->addComponent<CircularPathComponent>(circle);



	// Create Geometry
	andromeda::geometry::Ellipse geom(0.5f);
	geom.setSlices(32).setStacks(16);


	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);

	// Add RenderComponent
	if (geometry)
	{
		std::shared_ptr<andromeda::GeometryRenderComponent> render = std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);
		go->addComponent<andromeda::GeometryRenderComponent>(render);

		render->getMaterial().setDiffuseTexture(andromeda::LoadTexture("white"));
	}


	return go;
}


/*

*/
std::shared_ptr<GameObject> Factory::createText()
{
	return nullptr;
}


/*

*/
std::shared_ptr<GameObject> Factory::createRenderBufferDebug(const std::string & name, aFloat x, aFloat y, const std::shared_ptr<andromeda::ITexture> & debugTex)
{
	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();

	// Add Transform Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
	go->addComponent<andromeda::TransformComponent>(transform);
	transform->position(x, y, 0.0f);
	transform->update(0.0f);

	// Create Geometry
	andromeda::geometry::Cube geom(0.5f);

	std::shared_ptr<andromeda::Geometry> geometry = geom.build(andromeda::geometry::GeometryGenerate::Texture | andromeda::geometry::GeometryGenerate::Normals);


	std::shared_ptr<andromeda::GeometryRenderComponent> render =
		std::make_shared<andromeda::GeometryRenderComponent>(geometry, transform);

	render->setRenderGroup("debug");

	go->addComponent<andromeda::GeometryRenderComponent>(render);

	render->getMaterial().setDiffuse(1.0f, 1.0f, 1.0f);
	render->getMaterial().setDiffuseTexture(debugTex);

	return go;
}