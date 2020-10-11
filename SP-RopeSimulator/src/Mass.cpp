#include "Mass.h"

void Mass::init()
{
	force = glm::vec3(0, 0, 0);
	vel = glm::vec3(0, 0, 0);
}

void Mass::simulate(float dt)
{
	vel += (force / mass) * dt;
	pos += vel * dt;
}

void Mass::applyForce(glm::vec3 f)
{
	force += f;
}

void Mass::setPos(glm::vec3 p)
{
	pos = p;
}

void Mass::setVel(glm::vec3 v)
{
	vel = v;
}

glm::vec3 Mass::getPos()
{
	return pos;
}

glm::vec3 Mass::getVel()
{
	return vel;
}

float Mass::getM()
{
	return mass;
}
