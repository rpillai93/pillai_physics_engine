#include "ObjectContact.hpp"
#include "../helpers/MyMath.hpp"

void ObjectContact::resolve(float deltaTime)
{
	resolveVelocity(deltaTime);
}

float ObjectContact::getSeparatingVelocity() const
{
	sf::Vector2f relativeVelocity = m_ContactObjects[0]->getVelocity();
	if (m_ContactObjects.size() > 1) {
		relativeVelocity -= m_ContactObjects[1]->getVelocity();
	}
	return mymath::vector2::dotProduct(relativeVelocity, m_ContactNormal);
}

void ObjectContact::resolveVelocity(float deltaTime)
{
	float separatingVelocity = getSeparatingVelocity();

	if (separatingVelocity > 0) //positive separating velocity => contacts are separating or stationary and need no impulse applied to them
	{
		return;
	}

	float finalSeparatingVelocity = -separatingVelocity * m_CoeffRestitution;
	float deltaVelocity = finalSeparatingVelocity - separatingVelocity;
	float totalInverseMass = m_ContactObjects[0]->getInverseMass();
	if (m_ContactObjects.size() > 1) {
		totalInverseMass += m_ContactObjects[1]->getInverseMass();
	}

	float impulse = deltaVelocity / totalInverseMass;
	sf::Vector2<float> impulsePerIMass = m_ContactNormal * impulse;

	//Apply impulse to body 1
	const sf::Vector2f velBody1 = m_ContactObjects[0]->getVelocity();
	m_ContactObjects[0]->setVelocity(velBody1.x + impulsePerIMass.x * m_ContactObjects[0]->getInverseMass(), velBody1.y + impulsePerIMass.y * m_ContactObjects[0]->getInverseMass());

	//Apply impulse to body 2 if it exists
	if (m_ContactObjects.size() > 1) {
		const sf::Vector2f velBody2 = m_ContactObjects[1]->getVelocity();
		m_ContactObjects[1]->setVelocity(velBody2.x + impulsePerIMass.x * -m_ContactObjects[1]->getInverseMass(), velBody2.y + impulsePerIMass.y * -m_ContactObjects[1]->getInverseMass());
	}



}
