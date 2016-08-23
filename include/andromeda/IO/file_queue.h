#pragma once



#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

//#include <boost/lockfree/queue.hpp>


#include <andromeda/stddef.h>

namespace andromeda
{
	// Forward Declarations
	class IFileLocation;
	class File;



	/*
		File Handler
	*/
	class IFileHandler
	{
	public:
		virtual void onLoadPrepare() = 0;
		virtual void onLoadSuccess(const std::shared_ptr<File> & file) = 0;

		virtual void onLoadFail() {}
	};








	/*
		This needs to be a module
	*/
	class FileQueue
	{
	private:
		struct _File
		{
			std::string filename;
			Boolean binary;

			IFileLocation * location = nullptr;
			IFileHandler * handler = nullptr;


			Int32 priority = 0;




			// Comparison
			friend Boolean operator < (const _File & lhs, const _File & rhs)
			{
				return lhs.priority < rhs.priority;
			}
		};

	public:
		FileQueue();
		virtual ~FileQueue();

		/*
			Loads the File ... eventually
		*/
		void loadFile(const std::string & filename, Boolean binary, IFileLocation * location, IFileHandler * handler);


		void start();
		void run();
		void stop();

	protected:
		void load(const _File & file);

	private:
		
		


		Boolean _running = false;

//		boost::lockfree::queue<_File> _files;
		std::queue<_File> _files;

		std::thread _thread;
		std::mutex _mutex;
		std::mutex _mutexQueue;

		//std::unique_lock<std::mutex> _lock;
		std::condition_variable _conditional;
	};
}