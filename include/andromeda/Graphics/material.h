#ifndef _ANDROMEDA_GRAPHICS_MATERIAL_H_
#define _ANDROMEDA_GRAPHICS_MATERIAL_H_

#include <glm/glm.hpp>

namespace andromeda
{
	struct Material
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
	};
}


#endif