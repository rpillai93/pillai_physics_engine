#include "ObjectContact.hpp"
#include "../helpers/MyMath.hpp"

void ObjectContact::resolve(float deltaTime)
{

	resolveInterpenetration(deltaTime);
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

	sf::Vector2<float> accelerationAffectingVelocity = m_ContactObjects[0]->getAcceleration();
	if (m_ContactObjects.size() > 1) {
		accelerationAffectingVelocity -= m_ContactObjects[1]->getAcceleration();
	}

	float seperatingVelocityDueToAcceleration = mymath::vector2::dotProduct(accelerationAffectingVelocity, m_ContactNormal) * deltaTime;

	if (seperatingVelocityDueToAcceleration < 0) // build up is causing closing velocity instead, we need to correct this error
	{
		finalSeparatingVelocity += m_CoeffRestitution * seperatingVelocityDueToAcceleration;

		if (finalSeparatingVelocity < 0) {
			finalSeparatingVelocity = 0; //if there is closing velocity after accounting for acceleration, we set it to 0
		}
	}
	float deltaVelocity = finalSeparatingVelocity - separatingVelocity;

	float totalInverseMass = m_ContactObjects[0]->getInverseMass();
	if (m_ContactObjects.size() > 1) {
		totalInverseMass += m_ContactObjects[1]->getInverseMass();
	}

	if (totalInverseMass <= 0) return; // no impulse if particules are infinite mass bodies 

	float impulse = deltaVelocity / totalInverseMass;
	sf::Vector2<float> impulsePerIMass = m_ContactNormal * impulse;

	//Apply impulse to body 1
	const sf::Vector2f velBody1 = m_ContactObjects[0]->getVelocity();

	m_ContactObjects[0]->setVelocity(velBody1.x + impulsePerIMass.x * m_ContactObjects[0]->getInverseMass(), velBody1.y + impulsePerIMass.y * m_ContactObjects[0]->getInverseMass());

	//Apply impulse to body 2 if it exists
	if (m_ContactObjects.size() > 1) {
		const sf::Vector2f velBody2 = m_ContactObjects[1]->getVelocity();
		m_ContactObjects[1]->setVelocity(velBody2.x + -impulsePerIMass.x * m_ContactObjects[1]->getInverseMass(), velBody2.y + -impulsePerIMass.y * m_ContactObjects[1]->getInverseMass());
	}



}

void ObjectContact::resolveInterpenetration(float deltaTime)
{
	/*
	* If total penetration depth is 'd', then penetration for each body is related to their masses as follows:
	* Penetration of body A = (mass of body B / mass of body B + mass of body A) * d * contact normal vector  = (m(B) / m(B) + m(A)) * d * cNormal' (+ve sign indicates normal is in the direction of this body)
	* Penetration of body B = (mass of body A / mass of body B + mass of body A) * d * -contact normal vector = (m(A) / m(B) + m(A)) * d * -cNormal'(-ve sign indicates normal is in opp direction of this body)
	*
	* Now, total inverse mass = 1/m(A) + 1/m(B) = m(A)+m(B) / (m(A)*m(B)) ==> In other words, reciprocal of inverse mass = 1 / total inverse mass = m(A) * m(B)) / m(A) + m(B)
	* Substituting this into the equations for penetration above:
	* Penetration of body A = inverse mass of A * (1/total inverse mass of both bodies) * d * cNormal'  = (1/m(A)) * (1/m(A) + 1/m(B)) * d * cNormal'
	* Penetration of body B = inverse mass of B * (1/total inverse mass of both bodies) * d * -cNormal' = (1/m(B)) * (1/m(A) + 1/m(B)) * d * -cNormal'
	*/

	if (m_Penetration < 0)
		return;

	float totalInverseMass = m_ContactObjects[0]->getInverseMass();
	if (m_ContactObjects.size() > 1) {
		totalInverseMass += m_ContactObjects[1]->getInverseMass();
	}

	if (totalInverseMass <= 0) return;

	sf::Vector2<float> movePerInverseMass = m_ContactNormal * m_Penetration / totalInverseMass;

	m_ContactObjects[0]->setPosition(m_ContactObjects[0]->getPosition().x + movePerInverseMass.x * m_ContactObjects[0]->getInverseMass(),
		m_ContactObjects[0]->getPosition().y + movePerInverseMass.y * m_ContactObjects[0]->getInverseMass());

	if (m_ContactObjects.size() > 1) {
		m_ContactObjects[1]->setPosition(m_ContactObjects[1]->getPosition().x + -movePerInverseMass.x * m_ContactObjects[1]->getInverseMass(),
			m_ContactObjects[1]->getPosition().y + -movePerInverseMass.y * m_ContactObjects[1]->getInverseMass());
	}
}
