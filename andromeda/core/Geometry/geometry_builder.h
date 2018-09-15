#pragma once 

#include <memory>
#include <string>
#include <list>
#include <vector>

#include <Common/types.h>
#include <Common/glm.h>
#include <Core/Graphics/geometry.h>

//#include <andromeda/opengl.h>



namespace andromeda
{
	// Forward Declarations
	class Mesh;
	

	/*
		AttributeLocation:

		TODO:

		Matches up to a description of the geometry for the shader to use.

		This enum should be used for shader annotations.

		in GLSL:
		layout(location={ANNOTATION}) in <type> <name>

		Rename to ShaderAnnotation
	*/

	/*
	enum class GeometryLocation
	{
		Position,
		Normal,
		Texture0,
		Texture1,

		Color,


		Auto = 0xFF,
	};
	*/



	class GeometryBuilder
	{
	private:
		struct _VertexData
		{
			std::string id;

			VertexAttribute attribute;	// Attribute Location, for mapping into the shader

			Size length;				// Number of elements in the array
			Size elements;				// Number of elements in the structure
			Size stride;				// Size of the structure

			DataType dataType;			// Data type
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
		inline void addVertexData(const std::string& id, Float* data, Size length, VertexAttribute attribute = VertexAttribute::Auto)
		{
			return addVertexData(id, data, length, sizeof(Float), 1, DataType::Float, attribute);
		}
		inline void addVertexData(const std::string& id, glm::vec2* data, Size length, VertexAttribute attribute = VertexAttribute::Auto)
		{
			return addVertexData(id, data, length, sizeof(glm::vec2), 2, DataType::Float, attribute);
		}
		inline void addVertexData(const std::string& id, glm::vec3* data, Size length, VertexAttribute attribute = VertexAttribute::Auto)
		{
			return addVertexData(id, data, length, sizeof(glm::vec3), 3, DataType::Float, attribute);
		}
		inline void addVertexData(const std::string& id, glm::vec4* data, Size length, VertexAttribute attribute = VertexAttribute::Auto)
		{
			return addVertexData(id, data, length, sizeof(glm::vec4), 4, DataType::Float, attribute);
		}



		/*
			Template Version!
		*/
		template <typename T>
		void addVertexData(const std::string & id, T * data, Size length, Size elements, DataType type, VertexAttribute attribute = VertexAttribute::Auto)
		{
			addVertexData(id, (void*)data, length, sizeof(T), elements, type, attribute);
		}


		/*
			Generic Version
		*/
		void addVertexData(const std::string & id, void * data, Size length, Size stride, Size elements, DataType type, VertexAttribute attribute = VertexAttribute::Auto);




		/*
			Indices
		*/
		void setIndexData(UInt32 * indices, Size length);



		/*
			Build
		*/
		//Boolean build(std::shared_ptr<IVertexBuffer> vb, std::shared_ptr<IGeometryDescription> desc, std::shared_ptr<IIndexBuffer> ib = nullptr);

		/*
			Build
		*/
		std::shared_ptr<Mesh> build();

	private:

		/*
			Interleave
		*/
		Boolean interleave(std::shared_ptr<Mesh> mesh);

	//	Boolean index();	// Copies Indexing
	//	Boolean deindex();	// Removes indexing from the data

		
	
		Size _stride = 0;					// Size of the total structure 
		Size _length = 0;					// Number of array elements in the array

		std::list<_VertexData> _geometry;

		std::vector<UInt32> _indices;
	};
}

