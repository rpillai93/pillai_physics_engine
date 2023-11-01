#include "ForceDrag.hpp"
#include "../helpers/MyMath.hpp"

void ForceDrag::updateForce(IPhysicsObject* obj, float forceDuration)
{

	sf::Vector2f objVelocity = obj->getVelocity();
	float vMag = mymath::vector2::magnitude(objVelocity);
	float multFactor = k1 * vMag + k2 * vMag * vMag;
	mymath::vector2::normalize(objVelocity);
	obj->addForce(sf::Vector2f(objVelocity.x * multFactor * -1, objVelocity.y * multFactor * -1));
}
