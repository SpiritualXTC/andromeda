#ifndef _GAME_H_
#define _GAME_H_

#include <array>

#include <glm/glm.hpp>

#include <andromeda/stddef.h>


/*

*/
enum EntityStatus
{
	ENTITY_NONE = 0x0000,
};


/*

*/
template <int COUNT>
struct Ents
{
	const aInt32 size = COUNT;

	std::array<aUInt32, COUNT> status;

	std::array<glm::vec3, COUNT> pos;
	std::array<glm::vec3, COUNT> vel;
	std::array<glm::vec3, COUNT> acc;
};




/*

*/
class Game
{
	

public:
	Game();
	virtual ~Game();


	void update(aFloat ft);

private:
	Ents<10000> _entities;
};

#endif