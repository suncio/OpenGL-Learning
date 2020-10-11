#ifndef _SPRING_H_
#define _SPRING_H_

#include "Mass.h"
#include <memory>

class Spring
{
public:
	Spring()
		: mass1(nullptr), mass2(nullptr)
	{}

	Spring(std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2, 
		float k, float l)
		: mass1(m1), mass2(m2), 
		springConstant(k), 
		restLength(l)
		// frictionConstant(f)
	{}

	void solve();

private:
	std::shared_ptr<Mass> mass1;
	std::shared_ptr<Mass> mass2;

	float springConstant;
	float restLength;
	// float frictionConstant;
};

#endif // !_SPRING_H_
