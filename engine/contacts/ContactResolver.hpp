#pragma once
#include <vector>
#include "ObjectContact.hpp"

class ContactResolver {
protected:
	unsigned int m_Iterations;
	unsigned int m_IterationsUsed;
public:
	void setIterations(unsigned int iterations);
	void resolveContacts(std::vector<ObjectContact>& contacts, unsigned int numContacts, float deltaTime);

	ContactResolver() : m_Iterations(0), m_IterationsUsed(0) {};
	ContactResolver(unsigned int iterations) : m_Iterations(iterations), m_IterationsUsed(0) {};
};
