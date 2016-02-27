#ifndef _ANDROMEDA_GRAPHICS_GEOMETRY_BUILDER_H_
#define _ANDROMEDA_GRAPHICS_GEOMETRY_BUILDER_H_

#include <memory>
#include <string>
#include <list>
#include <vector>

#include "../stddef.h"
#include "opengl.h"

#include <glm/glm.hpp>

namespace andromeda
{
	// Forward Declarations
	class Geometry;
	class GeometryDescription;
	class IndexBuffer;
	class VertexBuffer;
	


	class GeometryBuilder
	{
	private:
		struct _VertexData
		{
			std::string id;

			Size length;				// Number of elements in the array
			Size elements;				// Number of elements in the structure
			Size stride;				// Size of the structure

			GLenum dataType;			// Data type
			std::vector<UInt8> data;	// Data, this copies rather than a pointer to arbituary data that could be created anywhere!... ((temporary))
		};

		


	public:
		enum _GenerateFlags
		{
			Normal = 0x01,
			Texture = 0x01,
		};


		GeometryBuilder();
		~GeometryBuilder();


		// Getters
		const inline Size stride() const { return _stride; }
		const inline Size length() const { return _length; }


		/*
			There is a lot more common tyes that could be useful here!
		*/
		inline void addVertexData(const std::string & attribute, Float * data, Size length)
		{
			return addVertexData(attribute, data, length, sizeof(Float), 1, GL_FLOAT);
		}
		inline void addVertexData(const std::string & attribute, glm::vec2 * data, Size length)
		{
			return addVertexData(attribute, data, length, sizeof(glm::vec2), 2, GL_FLOAT);
		}
		inline void addVertexData(const std::string & attribute, glm::vec3 * data, Size length)
		{
			return addVertexData(attribute, data, length, sizeof(glm::vec3), 3, GL_FLOAT);
		}
		inline void addVertexData(const std::string & attribute, glm::vec4 * data, Size length)
		{
			return addVertexData(attribute, data, length, sizeof(glm::vec4), 4, GL_FLOAT);
		}



		/*
			Generic Version!
		*/
		template <typename T>
		void addVertexData(const std::string & id, T * data, Size length, Size elements, GLenum type)
		{
			addVertexData(id, (void*)data, length, size(T), elements, type);
		}


		/*
			Build
		*/
		Boolean build(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc, std::shared_ptr<IndexBuffer> ib = nullptr);

	private:

		/*
			Interleave
		*/
		Boolean interleave(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc);

	//	Boolean index();	// Copies Indexing
	//	Boolean deindex();	// Removes indexing from the data

		void addVertexData(const std::string & id, void * data, Size length, Size stride, Size elements, GLenum type);


		Size _stride = 0;					// Size of the total structure 
		Size _length = 0;					// Number of array elements in the array

		std::list<_VertexData> _geometry;
	};
}


#endif