#ifndef _MASS_H_
#define _MASS_H_

#include <glm/glm.hpp>

class Mass
{
public:
	Mass(float m) : mass(m), force(glm::vec3(0, 0, 0)) {}
	// ~Mass();
	void init();
	void simulate(float dt);
	void applyForce(glm::vec3 force);

	// Setter, Getter
	void setPos(glm::vec3 p);
	void setVel(glm::vec3 v);
	glm::vec3 getPos();
	glm::vec3 getVel();
	float getM();

private:
	// Mass
	float mass;
	// Postion
	glm::vec3 pos;
	// Velocity
	glm::vec3 vel;
	// Force applied to this mass at an instance
	glm::vec3 force;
};

#endif // !_MASS_H_

