#pragma once

#include <memory>

#include <andromeda/stddef.h>

// Forward Declarations
namespace andromeda
{
	class GameObject;
}



/*
	Creates Objects!
*/
class Factory
{
public:


	static std::shared_ptr<andromeda::GameObject> createCube();

	static std::shared_ptr<andromeda::GameObject> createSphere(aFloat angle);


};