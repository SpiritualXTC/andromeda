#pragma once

namespace andromeda
{
	/*
		Binds to all Input classes
		Redispatches input into a more direct structure, uses polling mechanisms of Input systems when it can

		EG: Keyboard inputs would be rebound into a Digital Input
			Mouse Buttons are digital

	*/
	class Input
	{
	public:

		void registerAction() {}	// TODO: Input Type, matching value, handler

	};
}