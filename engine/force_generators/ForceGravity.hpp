#pragma once
#include "IForceGenerator.hpp"

//Equation: F = m * g
class ForceGravity : public IForceGenerator {
	sf::Vector2f gravity;
public:
	ForceGravity(const sf::Vector2f& g) : gravity(g) {};

	virtual void updateForce(IPhysicsObject* obj, float forceDuration) override;
};