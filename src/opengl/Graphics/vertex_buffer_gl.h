#pragma once

#include <andromeda/Graphics/buffer.h>

namespace andromeda
{
	namespace opengl
	{
		class VertexBufferGL : public VertexBuffer
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
