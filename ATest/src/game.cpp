#include "game.h"


/*

*/
Game::Game()
{

	/*
		GOOGLE: SIMD (single instruction multiple data)
	*/
	for (aInt32 i = 0; i < _entities.size; ++i)
	{
		_entities.status[i] = 0;

		_entities.pos[i] = glm::vec3(0, 0, 0);
		_entities.vel[i] = glm::vec3(0, 0, 0);
		_entities.acc[i] = glm::vec3(0, 0, 0);
	}
}

/*

*/
Game::~Game()
{

}


/*

*/
void Game::update(aFloat ft)
{
	aFloat ft2 = ft * 0.5f;

	// Physics Update
	for (aInt32 i = 0; i < _entities.size; ++i)
	{
		// No Entity
		if (! _entities.status[i])
			continue;


		_entities.vel[i] += _entities.acc[i] * ft;
		_entities.pos[i] += _entities.acc[i] * ft2 + _entities.vel[i] * ft;
	}


	// Collision Detection



	// Entity Update (Entity Specific Updates - animation / scripts / shrugs)


	// Render Sync
}



















