#include <andromeda/IO/file_queue.h>

// STL
#include <thread>


// Andromeda
#include <andromeda/IO/file.h>
#include <andromeda/IO/file_location.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
FileQueue::FileQueue()
{
	log_debug("FileQueue :: <init>()");

	start();
}

/*

*/
FileQueue::~FileQueue()
{
	log_debug("FileQueue :: <destroy>()");

	stop();

	_thread.join();

	log_debug("FileQueue :: <ended>()");
}




/*
	loadFile():


*/
void FileQueue::loadFile(const std::string & filename, Boolean binary, IFileLocation * location, IFileHandler * handler)
{
//	assert(location);
//	assert(handler);

	std::lock_guard<std::mutex> guard(_mutexQueue);

	// Add File to Load
	_File f;
	f.binary = binary;
	f.filename = filename;
	f.location = location;
	f.handler = handler;

	_files.push(f);

	_conditional.notify_all();

	// TEMP
//	std::this_thread::sleep_for(std::chrono::seconds(1));
}



/*

*/
void FileQueue::start()
{
	if (_running)
		return;

	log_debug("FileQueue :: start()");
	_thread = std::thread(&FileQueue::run, this);
}


/*
	run():

	Runs the FileQueue
*/
void FileQueue::run()
{
	log_debug("FileQueue :: run()");

	_running = true;

	Int32 count = 0;


	while (_running)
	{
		std::unique_lock<std::mutex> _locker(_mutex);

		log_warn("Queue ... Waiting");

		// Wait :: Appending to the Queue, or Stopping will send a notification
		_conditional.wait(_locker, [&]() {return ! _running || !_files.empty(); });	// waits if false

		// Exit loop if stopping
		if (_running == false)
			break;
		
		log_warn("Queue ... Processing");

		_File f;

		{
			std::lock_guard<std::mutex> guard(_mutexQueue);

			// Just make sure its empty, yeah?
			if (_files.empty())
				continue;

			// Retrieve Top
			f = _files.front();

			// Pop it.
			_files.pop();
		}

		// Load the File
		load(f);

		count++;
	}

	log_warnp("Counter = %1%", count);
}


/*

*/
void FileQueue::load(const _File & filedata)
{
	log_warnp("Loading File: %1%", filedata.filename);

	// Execute Handler Callbacks
	if (filedata.handler)
		filedata.handler->onLoadPrepare();

	// Load File
	std::shared_ptr<File> file;
	if (filedata.location)
		file = filedata.location->loadFile(filedata.filename, filedata.binary);

	// Execute Handler Callbacks
	if (filedata.handler)
	{
		if (file)
		{
			// Success callback
			filedata.handler->onLoadSuccess(file);
		}
		else
		{
			// Fail Callback
			filedata.handler->onLoadFail();
		}
	}
}




/*
	stop():


*/
void FileQueue::stop()
{
	log_debug("FileQueue :: stop()");

	if (_running == false)
		return;

	_running = false;
	_conditional.notify_all();
}
