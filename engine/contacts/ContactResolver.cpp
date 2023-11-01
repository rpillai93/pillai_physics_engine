#include "ContactResolver.hpp"

void ContactResolver::setIterations(unsigned int iterations)
{
	m_Iterations = iterations;
}

void ContactResolver::resolveContacts(std::vector<ObjectContact>& contacts, unsigned int numContacts, float deltaTime)
{
	m_IterationsUsed = 0;
	while (m_IterationsUsed < m_Iterations) {
		float maxClosingVelocity = 0;
		unsigned int maxIndex = numContacts;
		for (unsigned int i = 0; i < numContacts; i++) {
			float sepVel = contacts[i].getSeparatingVelocity();
			if (sepVel < maxClosingVelocity) {
				maxClosingVelocity = sepVel;
				maxIndex = i;
			}
		}

		//Resolving the most severe collision (one with max closing velocity) as this gives realistic values for other collisions
		if (maxIndex < numContacts) {
			contacts[maxIndex].resolve(deltaTime);
		}


		m_IterationsUsed++;
	}


}
