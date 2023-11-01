#pragma once
#include "../physics_objects/IPhysicsObject.hpp"
#include <iostream>
class ObjectContact {
public:
	std::vector<IPhysicsObject*> m_ContactObjects;
	float m_CoeffRestitution;
	float m_Penetration;
	sf::Vector2f m_ContactNormal;

	ObjectContact() = delete;

	ObjectContact(std::vector<IPhysicsObject*>& objects, float restitution, float penetration, const sf::Vector2f& normal) {
		m_ContactObjects.reserve(2);
		m_ContactObjects.emplace_back(std::move(objects[0]));
		if (objects.size() > 1) m_ContactObjects.emplace_back(std::move(objects[1]));
		m_CoeffRestitution = restitution;
		m_Penetration = penetration;
		m_ContactNormal.x = normal.x; m_ContactNormal.y = normal.y;
	}

	~ObjectContact() = default;

	void resolve(float deltaTime);
	float getSeparatingVelocity() const;
	void resolveVelocity(float deltaTime);
	void resolveInterpenetration(float deltaTime);
};
