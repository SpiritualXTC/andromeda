#pragma once

#include <GL/glew.h>

#include <common/types.h>
#include <core/Graphics/buffer.h>

namespace andromeda
{
	namespace opengl
	{
		class IndexBufferGL : public IIndexBuffer
		{
		public:
			IndexBufferGL();
			virtual ~IndexBufferGL();


			// BInd Vertex Buffer
			void bind() override;

			// Unbind Vertex Buffer
			void unbind() override;

			// Get Vertex Buffer Length
			inline UInt32 length() const override { return _length; }

			// Allocate GPU Memory, and copy data to GPU
			void data(const UInt32 * ptr, UInt32 length) override;

			// Copy data to GPU :: Does not allocate
			void subdata(const UInt32 * ptr, UInt32 offset, UInt32 length) override;

		private:
			GLuint _handle = 0;

			UInt32 _length = 0;
		};
	}
}
