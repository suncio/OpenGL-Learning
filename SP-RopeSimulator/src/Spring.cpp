#include "Spring.h"

void Spring::solve()
{
	glm::vec3 springVector = mass1->getPos() - mass2->getPos();

	/*
	std::cout << "Mass1 pos: " << "("
		<< mass1->getPos().x << ", "
		<< mass1->getPos().y << ", "
		<< mass1->getPos().z << ")" << std::endl;
	std::cout << "Mass2 pos: " << "("
		<< mass2->getPos().x << ", "
		<< mass2->getPos().y << ", "
		<< mass2->getPos().z << ")" << std::endl;
	*/

	float r = glm::length(springVector);

	glm::vec3 force(0);
	
	if (r != 0)
	{
		force += (-springConstant) * (springVector / r) * (r - restLength);
		// std::cout << "Spring force: " << "(" << force.x << ", " << force.y << ", " << force.z << ")" << std::endl;
	}

	// Opposite dir for m1 & m2
	mass1->applyForce(force);
	mass2->applyForce(-force);
}