#pragma once
#include <vector>
class IPhysicsObject;
class IForceGenerator;
class ForceRegistry {

protected:
	struct ForceRegistration {
		ForceRegistration(IPhysicsObject* o, IForceGenerator* f) : object(o), forceGen(f) {}
		IPhysicsObject* object;
		IForceGenerator* forceGen;
	};

	typedef std::vector<ForceRegistration> Registry;
	Registry registrations;
public:

	void add(IPhysicsObject* object, IForceGenerator* forceGen);

	void remove(IPhysicsObject* object, IForceGenerator* forceGen);

	void clear();

	void updateForces(float duration);
};
