#include "ForceGravity.hpp"

void ForceGravity::updateForce(IPhysicsObject* obj, float forceDuration)
{
	obj->addForce(gravity * (1 / obj->getInverseMass()));
}
