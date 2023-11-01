#include "ForceRegistry.hpp"
#include "physics_objects/PhysicsBox.hpp"
#include "physics_objects/PhysicsSphere.hpp"
#include "force_generators/IForceGenerator.hpp"

void ForceRegistry::add(IPhysicsObject* object, IForceGenerator* forceGen)
{
	registrations.emplace_back(object, forceGen);
}

void ForceRegistry::remove(IPhysicsObject* object, IForceGenerator* forceGen)
{
	for (Registry::iterator i = registrations.begin(); i != registrations.end(); i++) {
		if (object == i->object && forceGen == i->forceGen) {
			registrations.erase(i);
		}
	}
}

void ForceRegistry::clear()
{
	registrations.clear();
}

void ForceRegistry::updateForces(float duration)

{
	for (auto& r : registrations) {
		IForceGenerator* fg = r.forceGen;
		fg->updateForce(r.object, duration);
	}

}
