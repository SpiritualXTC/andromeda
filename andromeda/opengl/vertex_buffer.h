#pragma once

#include <GL/glew.h>

#include <common/types.h>
#include <core/Graphics/buffer.h>

namespace andromeda
{
	namespace opengl
	{
		class VertexBufferGL : public IVertexBuffer
		{
		public:
			VertexBufferGL();
			virtual ~VertexBufferGL();



			void bind() override;
			void unbind() override;

			inline UInt32 length() const override { return _length; }

			void data(const void * ptr, UInt32 length) override;
			void subdata(const void * ptr, UInt32 offset, UInt32 length) override;



		private:
			GLuint _handle = 0;

			UInt32 _length = 0;
		};
	}
}
