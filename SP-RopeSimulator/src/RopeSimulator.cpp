#include "RopeSimulator.h"

RopeSimulator::RopeSimulator(size_t num = 10)
	: numberOfMasses(num), 
	masses({}),
	edges({})
{
	masses.clear();
	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses.push_back(std::shared_ptr<Mass>(new Mass{ mass }));
	}

	size_t numberOfEdges = numberOfMasses - 1;

	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses[i]->init();
		masses[i]->setPos(glm::vec3(static_cast<float>(i), static_cast<float>(i), 0));
	}

	edges.clear();
	for (size_t i = 0; i < numberOfEdges; i++)
	{
		edges.push_back(Spring{masses[i], masses[i + 1], k, restLength });
	}
}

void RopeSimulator::init()
{
	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses[i]->init();
		masses[i]->setPos(glm::vec3(static_cast<float>(i), static_cast<float>(i), 0));
	}
}

void RopeSimulator::solve()
{
	// Apply spring force
	for (size_t i = 0; i < numberOfMasses - 1; i++)
	{
		edges[i].solve();
	}

	glm::vec3 gravity(0.0f, -9.8f, 0.0f);
	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses[i]->applyForce(gravity * masses[i]->getM());
	}

	// Set 0 point fixed
	masses[0]->init();
}

void RopeSimulator::simulate(float deltaTime)
{
	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses[i]->simulate(deltaTime);
	}
}

void RopeSimulator::resetMassesForce()
{
	for (size_t i = 0; i < numberOfMasses; i++)
	{
		masses[i]->init();
	}
}

void RopeSimulator::updateStates(float deltaTime)
{
	resetMassesForce();
	solve();
	simulate(deltaTime);
}