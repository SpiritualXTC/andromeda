#pragma once

#include <common/types.h>
#include <common/glm.h>

namespace andromeda
{
	glm::vec3 & calcNormal(glm::vec3 & normal, const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2)
	{
		// Subtraction
		glm::vec3 vs1 = v0 - v1;
		glm::vec3 vs2 = v1 - v2;

		// Cross Product : Calculate Normal
		normal.x = vs1.y * vs2.z - vs1.z * vs2.y;
		normal.y = vs1.z * vs2.x - vs1.x * vs2.z;
		normal.z = vs1.x * vs2.y - vs1.y * vs2.x;

		normal = normal / glm::length(normal);
	
		return normal;
	}
}
