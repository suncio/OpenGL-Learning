#ifndef _ROPE_SIMULATOR_H_
#define _ROPE_SIMULATOR_H_

#include <vector>

#include "Spring.h"

class RopeSimulator
{
public:
	RopeSimulator(size_t num);

	void init();
	void solve();
	void simulate(float deltaTime);
	void resetMassesForce();
	void updateStates(float deltaTime);


private:
	float mass = 1.0f;
	float restLength = 0.1f;
	// Huke's law constant
	float k = 10.0f;
	size_t numberOfMasses;

public:
	// std::vector<glm::vec3> positions;
	// std::vector<glm::vec3> velocities;
	// std::vector<glm::vec3> forces;
	std::vector<std::shared_ptr<Mass>> masses;
	std::vector<Spring> edges;
};

#endif // _ROPE_SIMULATOR_H_

