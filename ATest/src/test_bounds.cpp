#include "test_bounds.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>


#include <andromeda/Math/region.h>

#include <andromeda/Utilities/log.h>









void testBounds()
{
	aBoolean b = false;

//	test1D<aInt32>();
//	test2D();

//	glm::vec2 v1(0, 0);
//	glm::vec2 v2(-1, 1);

	//aBoolean b = glm::lessThan(v1, v2);

	andromeda::Region2i r1({ -1, -1 }, { 1, 1 });
	andromeda::Region2i r2({ 0, 0 }, { 2, 2 });

	andromeda::Region2i rr;

	b = r1.intersect(r2, rr);
	log_info("Intersect: ", b, glm::to_string(rr.minimum), glm::to_string(rr.maximum));


	

	andromeda::Region3f f1({ -1.0f, -2.0f, -0.5f }, {2.0f, 4.0f, 1.0f});
	andromeda::Region3f f2({ -0.5f, -2.5f, -1.5f }, { 2.5f, 5.0f, 1.3f });
	andromeda::Region3f fr;

	f1.intersect(f2, fr);

	b = f1.intersect(f2, fr);
	log_info("Intersect: ", b, glm::to_string(fr.minimum), glm::to_string(fr.maximum));



	andromeda::Region2f test2f(f1);
	andromeda::Region2i test2i(f1);
	andromeda::Region4d test4d(f1);

	log_info("3Df: ", b, glm::to_string(f1.minimum), glm::to_string(f1.maximum));
	log_info("2Df: ", b, glm::to_string(test2f.minimum), glm::to_string(test2f.maximum));
	log_info("2Di: ", b, glm::to_string(test2i.minimum), glm::to_string(test2i.maximum));

	log_info("4Dd: ", b, glm::to_string(test4d.minimum), glm::to_string(test4d.maximum));

}