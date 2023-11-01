#pragma once
#include "IForceGenerator.hpp"

//Equation: F = -v * (k1 * |v| + k2 * |v|^2)
class ForceDrag : public IForceGenerator {
	float k1;  // velocity coefficient
	float k2;  // velocity square coefficient
public:
	ForceDrag(float ck1, float ck2) : k1(ck1), k2(ck2) {};

	virtual void updateForce(IPhysicsObject* obj, float forceDuration) override;
};