#include "factory.h"

#include <string>


#include <andromeda/andromeda.h>
#include <andromeda/geometry.h>
#include <andromeda/graphics.h>
#include <andromeda/resources.h>

#include <andromeda/Game/game_object.h>

#include <andromeda/Game/mesh_component.h>
#include <andromeda/Game/geometry_component.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/Utilities/image.h>

#include "plane_test_component.h"
#include "circular_path_component.h"


using namespace andromeda;



std::shared_ptr<andromeda::GameObject> Factory::createSkybox()
{
	// Create Game Object
	std::shared_ptr<andromeda::GameObject> obj = std::make_shared<andromeda::GameObject>("skybox");


	// Load a Cube Texture
	CubeTextureLoadArgs args;
	args.filename_posX = "../res/textures/skybox_xpos.png";
	args.filename_negX = "../res/textures/skybox_xneg.png";

	args.filename_posY = "../res/textures/skybox_ypos.png";
	args.filename_negY = "../res/textures/skybox_yneg.png";

	args.filename_posZ = "../res/textures/skybox_zpos.png";
	args.filename_negZ = "../res/textures/skybox_zneg.png";


	// Manually Build the Skybox :: Only way for now until the resource manager is rewritten
	//std::shared_ptr<andromeda::CubeTexture> cubeTex = andromeda::LoadCubeTexture("skybox", &args);

	// Create a Cube Texture
	std::shared_ptr<andromeda::CubeTexture> cubeTex = graphics()->createCubeTexture(1024, 1024);

	// Load the 6 Images Manually
	std::shared_ptr<Image> posX = Image::LoadImageFromFile(args.filename_posX);
	std::shared_ptr<Image> posY = Image::LoadImageFromFile(args.filename_posY);
	std::shared_ptr<Image> posZ = Image::LoadImageFromFile(args.filename_posZ);
	std::shared_ptr<Image> negX = Image::LoadImageFromFile(args.filename_negX);
	std::shared_ptr<Image> negY = Image::LoadImageFromFile(args.filename_negY);
	std::shared_ptr<Image> negZ = Image::LoadImageFromFile(args.filename_negZ);

	cubeTex->data(CubeTextureFace::X_Positive, (UInt8*)posX->data());
	cubeTex->data(CubeTextureFace::Y_Positive, (UInt8*)posY->data());
	cubeTex->data(CubeTextureFace::Z_Positive, (UInt8*)posZ->data());
	cubeTex->data(CubeTextureFace::X_Negative, (UInt8*)negX->data());
	cubeTex->data(CubeTextureFace::Y_Negative, (UInt8*)negY->data());
	cubeTex->data(CubeTextureFace::Z_Negative, (UInt8*)negZ->data());









	// Create Standard Components
	std::shared_ptr<andromeda::TransformComponent> transform = std::make_shared<andromeda::TransformComponent>();
	obj->addComponent<andromeda::TransformComponent>(transform);



	// Create Material
	//std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("pattern0.png");

	std::shared_ptr<andromeda::Texture> tex = graphics()->createTexture(1024, 1024);
	tex->data((UInt8*)posX->data());


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
	std::shared_ptr<andromeda::Texture> tex = andromeda::LoadTexture("pattern0.png");
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

		render->getMaterial().setDiffuseTexture(andromeda::LoadTexture("white.png"));

		// Add Plane Test Component
		std::shared_ptr<PlaneTestComponent> planeTest = std::make_shared<PlaneTestComponent>(render, transform);
		obj->addComponent<PlaneTestComponent>(planeTest);
	}
	else
		return nullptr;




	return obj;
}