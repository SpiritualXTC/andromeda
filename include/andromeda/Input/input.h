#ifndef _ANDROMEDA_INPUT_INPUT_H_
#define _ANDROMEDA_INPUT_INPUT_H_

#include "../Engine/module.h"

namespace andromeda
{
	template <class T>
	class Input : public Module<T>
	{
	public:
		Input() : Module(Module::Input)
		{

		}
		virtual ~Input()
		{
		
		}

//		inline const SystemClass getSystemClass() override { return SystemClass::Input; }

	private:


		// ISystem
	//	Boolean isRequired() override { return false; }
		void onResume() override { return; }
		void onPause() override { return; }
	};

}


#endif