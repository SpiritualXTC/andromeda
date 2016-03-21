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
		CommonResourceStream();
		CommonResourceStream(std::string & fullPath);
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


		/*
			Move to Beginning of Stream
		*/
		void begin() override;

		/*
			Move to End of Stream
		*/
		void end() override;

		/*
			Get Current Position in Stream
		*/
		const UInt64 tell() override;

		/*
			Move to a position in Stream
		*/
		void seek(UInt64 pos) override;

		/*
			Read Entire Stream
		*/
		std::string read() override;

	private:

		Boolean _binary;
		UInt64 _length;

		std::ifstream _file;
	};

}

#endif
