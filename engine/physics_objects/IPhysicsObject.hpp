#pragma once
#include "SFML/Graphics.hpp"


enum ShapeType {
	UNSET = 0,
	SPHERE = 1,
	BOX = 2
};


class IPhysicsObject {

public:

	virtual ~IPhysicsObject() = default;
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual const sf::Vector2f& getPosition() const = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual const sf::Vector2f& getVelocity() const = 0;
	virtual void setVelocity(float x, float y) = 0;
	virtual const sf::Vector2f& getAcceleration() const = 0;
	virtual void setAcceleration(float x, float y) = 0;
	virtual const sf::Vector2f& getCenterOfMass() = 0;
	virtual void addForce(const sf::Vector2f& g) = 0;
	virtual const sf::Vector2f& getForceAccumulator() const = 0;
	virtual bool isFixedPosition() const = 0;
	virtual void setIsFixedPosition(bool isFixed) = 0;
	virtual bool getGravityOn() const = 0;
	virtual void setGravityOn() = 0;
	virtual void setGravityOff() = 0;
	virtual float getGravityValue() const = 0;
	virtual void setGravityValue(float g) = 0;
	virtual bool getDampingOn() const = 0;
	virtual void setDampingOn() = 0;
	virtual void setDampingOff() = 0;
	virtual float getDampingValue() const = 0;
	virtual void setDampingValue(float d) = 0;
	virtual float getInverseMass() const = 0;
	virtual void setInverseMass(float m) = 0;
	virtual ShapeType getShapeType() const = 0;
	virtual void setInitializeComplete() = 0;
	virtual bool getInitializeComplete() const = 0;
	/////////////////////////////////////////

};




