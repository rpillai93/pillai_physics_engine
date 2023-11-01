#pragma once
#include "../physics_objects/IPhysicsObject.hpp"

enum ForceType {
	GRAVITY = 1,
};


class IForceGenerator {

public:

	~IForceGenerator() = default;
	virtual void updateForce(IPhysicsObject* obj, float forceDuration) = 0;
};




