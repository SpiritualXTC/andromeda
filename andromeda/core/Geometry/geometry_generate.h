#pragma once

#include <vector>
#include <memory>

#include <Common/types.h>
#include <Common/glm.h>
#include <Core/Graphics/types.h>

namespace andromeda
{
	// Forward-Declarations
	class Mesh;


	enum GeometryGenerateEnum
	{
		GEN_NORMALS = 0x01,
		GEN_TEXTURE = 0x02,
	};


	namespace geometry
	{

		/*
			TODO:
			Base Class for Geometry Shapes
		*/
		class GeometryGenerate
		{
		private:
			enum _PostProcess
			{
				None = 0x00,
				Transform = 0x01,
			};

		public:
			enum _Generate
			{
				Position = 0x00,
				Normals = 0x01,
				Texture = 0x02,
			};


			GeometryGenerate();
			GeometryGenerate(PrimitiveMode mode);
			virtual ~GeometryGenerate();

			std::shared_ptr<Mesh> build(UInt32 genFlags);

			virtual UInt32 getVertexCount() const = 0;
			virtual UInt32 getFaceCount() const = 0;


			/*
				TODO:
				Make this function able to return the appropriate class (as a typical builder) -- 
				will require some templating :: but the templating CANNOT be on this class
			*/


			// Set Post Process Transformation
			void setTransformation(glm::mat4 & m)
			{
				_matrix = m;
				_postProcessFlags |= GeometryGenerate::Transform;
			}


		protected:
			// A Process that begins immediately before geometry construction
			virtual Boolean prebuild() { return true; }

			virtual void buildPosition(glm::vec3 * pvertices, UInt32 count) = 0;
			virtual void buildNormals(glm::vec3 * pvertices, UInt32 count) = 0;
			virtual void buildTexCoords(glm::vec2 * pvertices, UInt32 count) = 0;

			virtual void buildIndices(UInt32 * pindices, UInt32 count) = 0;


			const glm::vec3 * getPositionData() const { return _position; }
			const glm::vec3 * getNormalData() const { return _normals; }
			const glm::vec2 * getTexCoord0Data() const { return _texCoord0; }

			const UInt32 * getIndexData() const { return _indices; }



		private:
			// Post Process
			void postProcess();
			void transformPosition();
			void transformNormals();
			
			UInt32 _postProcessFlags = GeometryGenerate::None;


			PrimitiveMode _mode = PrimitiveMode::Triangles;

			
			glm::vec3 * _position = nullptr;
			glm::vec3 * _normals = nullptr;
			glm::vec2 * _texCoord0 = nullptr;

			UInt32 * _indices = nullptr;


			glm::mat4 _matrix{ 1.0f };
		};
	}


	// Builder Functions
	
	// 3D
//	std::shared_ptr<Geometry> CreateTorus(Float radius, Float tubeRadius, Int32 segments, Int32 stacks, UInt32 genMask); // TODO
//	std::shared_ptr<Geometry> CreateIcosahedron(Float radius); // TODO: Google & Implement

	// 2D
//	std::shared_ptr<Geometry> CreatePolygon(Float radius, Int32 sides, glm::vec3 & normal, UInt32 genMask); // ToDo


}
