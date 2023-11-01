#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include "contacts/ObjectContact.hpp"
class PhysicsSphere;
class PhysicsBox;
class IPhysicsObject;
/*Penetration distance along x and y directions. These are always non negative values. 0 value means no penetration*/

class PhysicsWorld {
private:

	PhysicsBox* mGround;
	unsigned int numObjects = 1; // Assuming ground always exists
public:
	PhysicsWorld() = default;
	~PhysicsWorld() {
		//DELETE OBJECTS
		for (auto* it : PhysicsObjects) {
			delete it;
		}
		delete mGround;
		PhysicsObjects.clear();



		std::cout << "DELETED " << "PHYSICS WORLD" << '\n';
	}
	std::vector<IPhysicsObject*> PhysicsObjects;
	std::vector<ObjectContact> ObjectContacts;
	void Initialize();
	void Update(float deltaTime);
	void setGround(PhysicsBox* ground);
	void setContacts();
	void addObjectToWorld(IPhysicsObject* object);
	PhysicsBox* getGround() const;

	/* All collision check functions return the penetration distance
	/* If penetration > 0, the bodies are penetrating
	/* Else the bodies are not penetrating */
	float checkCollisionSphereToBox(PhysicsSphere* s, PhysicsBox* b);
	float checkCollisionSphereToSphere(PhysicsSphere* s1, PhysicsSphere* s2);
	float checkCollisionBoxToBox(PhysicsBox* b1, PhysicsBox* b2);
	float checkCollisionObjectToGround(IPhysicsObject* o, PhysicsBox* g); //NOT RECOMMENDED DUE TO OVERHEADS, USE SPECIFIC COLLISION CHECK FUNCTIONS
	float checkCollisionObjectToObject(IPhysicsObject* o1, IPhysicsObject* o2); //NOT RECOMMENDED DUE TO OVERHEADS, USE SPECIFIC COLLISION CHECK FUNCTIONS
};
