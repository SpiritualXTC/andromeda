#ifndef _ANDROMEDA_GRAPHICS_MATERIAL_H_
#define _ANDROMEDA_GRAPHICS_MATERIAL_H_

#include <andromeda/stddef.h>

#include <andromeda/glm.h>



namespace andromeda
{
	struct Material
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
}


#endif