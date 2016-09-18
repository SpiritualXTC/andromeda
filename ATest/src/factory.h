#pragma once

#include <memory>
#include <string>

#include <andromeda/stddef.h>

// Forward Declarations
namespace andromeda
{
	class ITexture;
	class GameObject;
}



/*
	Creates Objects!
*/
class Factory
{
public:

	static std::shared_ptr<andromeda::GameObject> createSkybox();


	static std::shared_ptr<andromeda::GameObject> createCube();

	static std::shared_ptr<andromeda::GameObject> createSphere(aFloat angle);

	static std::shared_ptr<andromeda::GameObject> createGround();

	// andThenThereWasLight(...)
	// Creates the Directional Light
	static std::shared_ptr<andromeda::GameObject> createLight();



	static std::shared_ptr<andromeda::GameObject> createText();


	static std::shared_ptr<andromeda::GameObject> createRenderBufferDebug(const std::string & name, aFloat x, aFloat y, const std::shared_ptr<andromeda::ITexture> & debugTex);
};