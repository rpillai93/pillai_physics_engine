#include "PhysicsWorld.hpp"
#include "physics_objects/PhysicsSphere.hpp"
#include "physics_objects/PhysicsBox.hpp"
#include "physics_objects/IPhysicsObject.hpp"
#include "helpers/DebugMacros.hpp"
#include "helpers/MyMath.hpp"


void PhysicsWorld::Initialize()
{	// 1. Set all physics world objects
	// 2. Call Initialize() on all physics objects

	for (auto* PhysicsObject : PhysicsObjects)
	{
		PhysicsObject->Initialize();
		PhysicsObject->setInitializeComplete();
	}
	mGround->Initialize();
}

void PhysicsWorld::Update(float deltaTime)
{	// 1. Set the force accumulator on each object
	// 2. Calculate acceleration, velocity and displacement 
	// 3. Run collision checks -> resolve if needed
	// 4. Call Update() on all objects 


	//for (auto* object : PhysicsObjects) {
	//	float penetration = checkCollisionObjectToObject(object, mGround);

	//	if (penetration > 0) {
	//		//If collision occurs, we resolve for interpenetration here
	//		std::vector<IPhysicsObject*> obj; obj.emplace_back(object);
	//		sf::Vector2<float> contactNormal(0.f, -1.0f);                                     /*HARD CODED VALUE*/
	//		ObjectContacts.emplace_back(obj, 0.7f, penetration, contactNormal); // Add contacts for resolution
	//	}
	//	else {
	//		object->Update(deltaTime);
	//	}
	//}




	for (int i = PhysicsObjects.size() - 1; i >= 3; i--) {
		auto object = PhysicsObjects[i];
		for (int j = i - 1; j >= 0; j--) {

			float penetration = checkCollisionObjectToObject(object, PhysicsObjects[j]);

			if (penetration > 0) {
				//If collision occurs, we resolve for interpenetration here
				std::vector<IPhysicsObject*> obj;
				if (object->getInverseMass() > 0)
					obj.emplace_back(object);
				if (PhysicsObjects[j]->getInverseMass() > 0)
					obj.emplace_back(PhysicsObjects[j]);
				sf::Vector2<float> contactNormal(0.f, -1.f);
				float restitution = 0.4;
				if (j == 0) {
					restitution = 0.7;
				}
				else if (j == 1) {
					contactNormal.x = 1.0f;
					contactNormal.y = 0.f;
					restitution = 0.7;

				}
				else if (j == 2) {
					contactNormal.x = -1.0f;
					contactNormal.y = 0.f;
					restitution = 0.7;
				}

				if (object->getShapeType() == ShapeType::SPHERE && PhysicsObjects[j]->getShapeType() == ShapeType::SPHERE) {
					auto& pos1 = object->getCenterOfMass();
					auto& pos2 = PhysicsObjects[j]->getCenterOfMass();
					contactNormal.x = pos1.x - pos2.x;
					contactNormal.y = pos1.y - pos2.y;
					mymath::vector2::normalize(contactNormal);
				}

				ObjectContacts.emplace_back(obj, restitution, penetration, contactNormal); // Add contacts for resolution
			}
			else {
				object->Update(deltaTime);
			}
		}
	}

	if (ObjectContacts.size() > 0) {
		resolver.setIterations(ObjectContacts.size()); // setting number of iterations to same size as num contacts
		resolver.resolveContacts(ObjectContacts, ObjectContacts.size(), deltaTime);
		ObjectContacts.clear();
		setContacts();
	}

}

void PhysicsWorld::setContacts()
{
	ObjectContacts.reserve((numObjects * (numObjects - 1)) / 2);
}

void PhysicsWorld::addObjectToWorld(IPhysicsObject* object)
{
	if (!object->getInitializeComplete())
	{
		object->Initialize();
		object->setInverseMass(1.0f);
		object->setInitializeComplete();
	}

	PhysicsObjects.emplace_back(object);

	numObjects++;
}

float PhysicsWorld::checkCollisionSphereToBox(PhysicsSphere* s, PhysicsBox* b)
{
	// collision of a sphere and axis aligned binding box (AABB)
	// y-axis here is flipped (ie downward is +ve, upward is negative) 


	const sf::Vector2f& sphereCenter = s->getCenterOfMass();
	const sf::Vector2f& boxCenter = b->getCenterOfMass();
	const sf::Vector2f& boxSize = b->getSize();
	float left = boxCenter.x - (boxSize.x / 2);		// left edge of box
	float right = boxCenter.x + (boxSize.x / 2);	// right edge of box
	float top = boxCenter.y - (boxSize.y / 2);		// top edge of box
	float bottom = boxCenter.y + (boxSize.y / 2);   // bottom edge of box
	sf::Vector2<float> clampedPoint(mymath::clamp(sphereCenter.x, left, right), mymath::clamp(sphereCenter.y, top, bottom));


	sf::Vector2f clampedPointToSphere(sphereCenter.x - clampedPoint.x, sphereCenter.y - clampedPoint.y);
	float clampedPointToSphereMagSq = mymath::vector2::magnitudeSq(clampedPointToSphere); // using squared distance as it is faster
	float sphereRad = s->getRadius();

	if (sphereRad * sphereRad > clampedPointToSphereMagSq) {
		return (sphereRad - mymath::sqrt(clampedPointToSphereMagSq)); // return the correct penetration only if it occurs as sqrt is an expsensive calculation
	}

	return -1.0f; // return negative penetration if no penetration occurs

}

float PhysicsWorld::checkCollisionSphereToSphere(PhysicsSphere* s1, PhysicsSphere* s2)
{


	const sf::Vector2f& s1Center = s1->getCenterOfMass();
	float s1Radius = s1->getRadius();
	const sf::Vector2f& s2Center = s2->getCenterOfMass();
	float s2Radius = s2->getRadius();

	float distanceCentersSq = mymath::vector2::getDistSq(s1Center, s2Center); // using squared distance as it is faster
	if ((s1Radius + s2Radius) * (s1Radius + s2Radius) > distanceCentersSq) {
		return (s1Radius + s2Radius - mymath::sqrt(distanceCentersSq));  // return the correct penetration only if it occurs as sqrt is an expsensive calculation
	}

	return -1.0f; // return negative penetration if no penetration occurs
}

float PhysicsWorld::checkCollisionBoxToBox(PhysicsBox* s1, PhysicsBox* s2)
{

	//COLLISION CHECK GOES HERE
	return 0.0f;
}

float PhysicsWorld::checkCollisionObjectToGround(IPhysicsObject* o, PhysicsBox* g)
{

	ShapeType st = o->getShapeType();
	if (st == ShapeType::SPHERE) {
		PhysicsSphere* s = dynamic_cast<PhysicsSphere*>(o);
		if (s == nullptr) {
			DEBUG_ERROR(x);

			return 0.0f;
		}
		return checkCollisionSphereToBox(s, g);
	}
	if (st == ShapeType::BOX) {
		PhysicsBox* b = dynamic_cast<PhysicsBox*>(o);
		if (b == nullptr) {
			DEBUG_ERROR(x);

			return 0.0f;
		}
		return checkCollisionBoxToBox(b, g);
	}

	return 0.0f;
}

float PhysicsWorld::checkCollisionObjectToObject(IPhysicsObject* o1, IPhysicsObject* o2)
{


	ShapeType st1 = o1->getShapeType();
	ShapeType st2 = o2->getShapeType();

	if (st1 == ShapeType::SPHERE && st2 == ShapeType::SPHERE) {
		PhysicsSphere* s1 = dynamic_cast<PhysicsSphere*>(o1);
		PhysicsSphere* s2 = dynamic_cast<PhysicsSphere*>(o2);
		if (s1 == nullptr || s2 == nullptr) {
			DEBUG_ERROR(x);
			return 0.0f;
		}

		return checkCollisionSphereToSphere(s1, s2);
	}

	if (st1 == ShapeType::BOX && st2 == ShapeType::BOX) {
		PhysicsBox* b1 = dynamic_cast<PhysicsBox*>(o1);
		PhysicsBox* b2 = dynamic_cast<PhysicsBox*>(o2);
		if (b1 == nullptr || b2 == nullptr) {
			DEBUG_ERROR(x);
			return 0.0f;
		}

		return checkCollisionBoxToBox(b1, b2);
	}

	if (st1 == ShapeType::SPHERE && st2 == ShapeType::BOX || st1 == ShapeType::BOX && st2 == ShapeType::SPHERE) {
		PhysicsSphere* s = dynamic_cast<PhysicsSphere*>(o1);
		PhysicsBox* b = dynamic_cast<PhysicsBox*>(o2);
		if (s != nullptr && b != nullptr) {
			return checkCollisionSphereToBox(s, b);
		}

		s = dynamic_cast<PhysicsSphere*>(o2);
		b = dynamic_cast<PhysicsBox*>(o1);
		if (s != nullptr && b != nullptr) {
			return checkCollisionSphereToBox(s, b);

		}
		DEBUG_ERROR(x);
		return 0.0f;
	}

	return 0.0f;
}

