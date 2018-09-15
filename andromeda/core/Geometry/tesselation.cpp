#include "tesselation.h"

#include <cassert>
#include <unordered_map>


#include <glm/gtc/type_ptr.hpp>
#include <Common/log.h>

#include "primitive_builder.h"
// No idea if this will work correctly... considering bezier curves needs to be built into the triangulation system with bary centric texture coordinates...
// But just  to get something up and running might be useful enough :)
// The functions are defined in Windows.h ... so yeah, an alternative will need to be found .... or a wrapper

/*
	TODO:
	The Triangulation stuff, will need to be moved to the Graphics API
*/





using namespace andromeda;
using namespace andromeda::geometry;


#if 1
// Begins Tesselation
void CALLBACK tesselationBegin(GLenum type, PrimitiveBuilder * tess)
{
	assert(tess);

	std::unordered_map<GLenum, PrimitiveMode> emap = {
		{ GL_TRIANGLE_FAN, PrimitiveMode::TriangleFan },
		{ GL_TRIANGLE_STRIP, PrimitiveMode::TriangleStrip },
		{ GL_TRIANGLES, PrimitiveMode::Triangles },
	};

	const auto & eit = emap.find(type);

	if (eit == emap.end())
		return;

	// Set the Primitive Type
	tess->setPrimitiveType(eit->second);


#if 0
	// Debug
	std::unordered_map<GLenum, std::string> smap = {
		{ GL_TRIANGLE_FAN, "Triangle Fan"},
		{ GL_TRIANGLE_STRIP, "Triangle Strip" },
		{ GL_TRIANGLES, "Triangles" },
	};

	const auto & sit = smap.find(type);

	log_infop("Tesselation :: Begin Tesselation. Type = %1%", (sit == smap.end() ? "Unknown" : sit->second));
#endif
}

// Ends Tesselation
void CALLBACK tesselationEnd(PrimitiveBuilder * tess)
{
	assert(tess);

//	log_infop("Tesselation :: End");
}


// New Vertex added to Tesselation Object
void CALLBACK tesselationVertex(GLvoid * vertex, PrimitiveBuilder * tess)
{
	assert(tess);

	GLdouble * p = (GLdouble*)vertex;

//	log_infop("Tesselation :: Add Vertex: (%1%, %2%, %3%)", p[0], p[1], p[2]);

	tess->addVertex(glm::dvec3(p[0], p[1], p[2]));
}


// Edge during Tesselation Process
void CALLBACK tesselationEdge(GLboolean flag, PrimitiveBuilder * tess)
{
	assert(tess);

	// No Idea what goes here :)

//	log_infop("Tesselation :: Edge = %1%", flag != 0);
}

// Combine
void tesselationCombine(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut, PrimitiveBuilder * tess)
{
	assert(tess);

	glm::dvec3 p = glm::dvec3(coords[0], coords[1], coords[2]);

	// Add to Cache
	glm::dvec3 & cache = tess->cache(p);

	// Assign Pointer
	*dataOut = glm::value_ptr(cache);
}

// Error during Tesselation Process
void CALLBACK tesselationError(GLenum errorCode, PrimitiveBuilder * tess)
{
	assert(tess);

	log_errp("Tesselation :: Error = %1%", errorCode);
}
#else

/*
----
Crashes when tesselationEnd is called... no understanding as to why :(

Works fine when passing the PrimitiveBuyilder into the Tesselator...
but not when passing the Tesselation Object into the Tesselator
----
*/


/*

*/
void tesselationBegin(GLenum type, Tesselation * tess)
{
	assert(tess);

	std::unordered_map<GLenum, PrimitiveMode> emap = {
		{ GL_TRIANGLE_FAN, PrimitiveMode::TriangleFan },
		{ GL_TRIANGLE_STRIP, PrimitiveMode::TriangleStrip },
		{ GL_TRIANGLES, PrimitiveMode::Triangles },
	};

	const auto & eit = emap.find(type);

	if (eit == emap.end())
		return;

	// Set the Primitive Type
	tess->getBuilder().setPrimitiveType(eit->second);

	// Debug
	std::unordered_map<GLenum, std::string> smap = {
		{ GL_TRIANGLE_FAN, "Triangle Fan" },
		{ GL_TRIANGLE_STRIP, "Triangle Strip" },
		{ GL_TRIANGLES, "Triangles" },
	};

	const auto & sit = smap.find(type);

	log_infop("Tesselation :: Begin Tesselation. Type = %1%", (sit == smap.end() ? "Unknown" : sit->second));
}


/*

*/
void tesselationEnd(Tesselation * tess)
{
	assert(tess);

	log_infop("Tesselation :: End");
}

/*

*/
void tesselationVertex(GLvoid * vertex, Tesselation * tess)
{
	assert(tess);

	GLdouble * p = (GLdouble*)vertex;

	log_infop("Tesselation :: Add Vertex: (%1%, %2%, %3%)", p[0], p[1], p[2]);

	tess->getBuilder().addVertex(glm::dvec3(p[0], p[1], p[2]));
}

/*

*/
void tesselationEdge(GLboolean flag, Tesselation * tess)
{
	assert(tess);

	// No Idea what goes here :)
	log_infop("Tesselation :: Edge = %1%", (Boolean)flag);
}


/*

*/
void tesselationCombine(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut, Tesselation * tess)
{
	assert(tess);

	glm::dvec3 p = glm::dvec3(coords[0], coords[1], coords[2]);

	log_infop("Tesselation :: Combine = (%1%, %2%, %3%)", p.x, p.y, p.z);

	// Need to Manage some memory somewhere
	// TEMP: Use the PrimitiveBuilder for caching...
	// TODO: Put the caching somewhere else... maybe

	glm::dvec3 & cache = tess->cache(p);

	// Assign Pointer
	*dataOut = glm::value_ptr(cache);
}

/*

*/
void tesselationError(GLenum errorCode, Tesselation * tess)
{
	assert(tess);

	log_infop("Tesselation :: Error = %1%", errorCode);
}
#endif





/*

*/
Tesselation::Tesselation(PrimitiveBuilder & pbuilder)
	: _primBuilder(pbuilder)
{
	// Triangulate
	_tess = gluNewTess();

	// Set Callbacks
	gluTessCallback(_tess, GLU_TESS_BEGIN_DATA, (void (CALLBACK*)())tesselationBegin);
	gluTessCallback(_tess, GLU_TESS_END_DATA, (void (CALLBACK*)())tesselationEnd);
	gluTessCallback(_tess, GLU_TESS_VERTEX_DATA, (void (CALLBACK*)())tesselationVertex);

	gluTessCallback(_tess, GLU_TESS_COMBINE_DATA, (void (CALLBACK*)())tesselationCombine);
	gluTessCallback(_tess, GLU_TESS_EDGE_FLAG_DATA, (void (CALLBACK*)())tesselationEdge);

	gluTessCallback(_tess, GLU_TESS_ERROR_DATA, (void (CALLBACK*)())tesselationError);


	// Appears to do cutouts slightly better during an overlap :D
	gluTessProperty(_tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NEGATIVE);

	// Set the Normal
	gluTessNormal(_tess, 0, 0, 1);
}


/*

*/
Tesselation::~Tesselation()
{

	// Delete Tesselator
	if (_tess)
		gluDeleteTess(_tess);
}


/*

*/
void Tesselation::beginPolygon()
{
	assert(_tess);

//	log_debugp("Tesselation :: Begin Polygon");

	// Begin Tesselation
	gluTessBeginPolygon(_tess, &_primBuilder);
	//gluTessBeginPolygon(_tess, this);
}


/*

*/
void Tesselation::endPolygon()
{
	assert(_tess);

//	log_debugp("Tesselation :: End Polygon");

	// End Tesselation
//	log_debugp("Tesselation :: Begin Tesselation");

	gluTessEndPolygon(_tess);

//	log_debugp("Tesselation :: End Tesselation");
}


/*

*/
void Tesselation::beginContour()
{
	assert(_tess);

//	log_infop("Tesselation :: Begin Contour");

	// Begin Contour
	gluTessBeginContour(_tess);
}


/*

*/
void Tesselation::endContour()
{
	assert(_tess);

//	log_infop("Tesselation :: End Contour");

	// End Contour
	gluTessEndContour(_tess);
}


/*

*/
void Tesselation::addContour(glm::dvec3 * p, UInt32 count)
{
	glm::dvec3 * pv = p;

	beginContour();

	for (UInt32 i = 0; i < count; ++i, ++pv)
	{
		//glm::dvec3 p = *pv++;
		gluTessVertex(_tess, glm::value_ptr(*pv), glm::value_ptr(*pv));
	}

	endContour();
}


#if 0
/*

*/
glm::dvec3 & Tesselation::cache(const glm::dvec3 & v)
{
	_cache.push_back(v);

	return _cache.back();
}
#endif