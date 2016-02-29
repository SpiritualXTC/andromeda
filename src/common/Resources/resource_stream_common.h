#ifndef _ANDROMEDA_COMMON_FILE_STREAM_COMMON_H_
#define _ANDROMEDA_COMMON_FILE_STREAM_COMMON_H_

#include <fstream>
#include <andromeda/Resources/resource_stream.h>

namespace andromeda
{
	/*
	
	*/
	class CommonResourceStream : public ResourceStream
	{
	public:
		CommonResourceStream(std::string & fullPath, Boolean binary);
		virtual ~CommonResourceStream();


		const inline Boolean isBinary() const override
		{
			return _binary;
		}

		/*
			Returns whether the file is open
		*/
		const inline Boolean isOpen() const override
		{
			return _file.is_open();
		}

		/*
			Length of File
		*/
		const inline UInt64 length() const override
		{
			return _length;
		}

		/*
			Open a File
		*/
		void open(const std::string & fullPath, const Boolean binary) override;

		/*
			Close the File
		*/
		void close() override;



		void begin() override;

		void end() override;

		UInt64 tell() override;

		void seek(UInt64 pos) override;

	private:

		Boolean _binary;
		UInt64 _length;

		std::ifstream _file;
	};

}

#endif
