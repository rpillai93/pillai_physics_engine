#pragma once
#include "IPhysicsObject.hpp"
#include <iostream>
////////////////////////////////////////////////////////////
//// PhysicsSphere  
//// An object with a sphere shape that can simulate physics. All of the shape
//// behavior is inherited from the parent CircleShape and physics behavior
//// from the parent interface IPhysicsObject. Only basic shape behavior
//// and properties are defined here. 
////////////////////////////////////////////////////////////
constexpr static float DEFAULT_RADIUS = 10.0f;
constexpr static size_t DEFAULT_POINT_COUNT = 16;
static sf::Color DEFAULT_SPHERE_FILL_COLOR = sf::Color::Blue;
class PhysicsSphere : public sf::CircleShape, public IPhysicsObject {

private:
	////////////////////////////////////////////////////////////
	//// IPhysicsObject Behavior Members
	//// *m_ShapeType = enum that represents the geometry type of the parent shape
	//// *m_Displacement = change in position of this object between two consecutive frames (calculation begins from 2nd frame onwards)
	//// *m_Velocity = displacement with respect to time between two consecutive frames (calculation begins from 2nd frame onwards)
	//// *m_Acceleration = velocity with respect to time between two consecutive frames (calculation begins from 3rd frame onwards)
	////////////////////////////////////////////////////////////
	ShapeType m_ShapeType;
	sf::Vector2f m_Displacement;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;
	sf::Vector2f m_ForceAccumulator;
	sf::Vector2f m_CenterOfMass;
	float m_InverseMass = 1.0f;
	bool m_IsFixed = false;
	float m_Gravity = 9.8f;
	bool m_GravityOn = false;
	float m_Damping = 0.99f;
	bool m_DampingOn = true;
public:
	////////////////////////////////////////////////////////////
	//// IPhysicsObject Behavior Functions
	//// *getPosition() = returns top left point of the bounding box containing the physics object
	//// *setPosition() = sets the top left point of the bounding box containing the physics object
	//// *getCenterOfMass() = returns the center of mass of the parent shape 
	//// *Initialize() = initialize all physics properties for this object for the first frame 
	//// *Update() = updates all physics properties for this object from the second frame onwards
	////////////////////////////////////////////////////////////
	bool InitializeComplete = false;
	virtual void Initialize() override;
	virtual void Update(float deltaTime) override;
	virtual const sf::Vector2f& getPosition() const;
	virtual void setPosition(float x, float y) override;
	virtual const sf::Vector2f& getVelocity() const override;
	virtual void setVelocity(float x, float y) override;
	virtual const sf::Vector2f& getAcceleration() const override;
	virtual void setAcceleration(float x, float y) override;
	virtual void addForce(const sf::Vector2f& g) override;
	virtual const sf::Vector2f& getForceAccumulator() const override;
	const sf::Vector2f& getCenterOfMass();
	virtual bool isFixedPosition() const override;
	virtual void setIsFixedPosition(bool isFixed) override;
	virtual bool getGravityOn() const override;
	virtual void setGravityOn() override;
	virtual void setGravityOff() override;
	virtual float getGravityValue() const override;
	virtual void setGravityValue(float g) override;
	virtual bool getDampingOn() const override;
	virtual void setDampingOn() override;
	virtual void setDampingOff() override;
	virtual float getDampingValue() const override;
	virtual void setDampingValue(float d) override;
	virtual float getInverseMass() const override;
	virtual void setInverseMass(float m) override;
	virtual void setInitializeComplete() override;
	virtual bool getInitializeComplete() const override;
	////////////////////////////////////////////////////////////
	//// CircleShape Behavior Functions
	////////////////////////////////////////////////////////////
	void setShapeProperties(const sf::Vector2f& position, float radius = DEFAULT_RADIUS, std::size_t pointCount = DEFAULT_POINT_COUNT, const sf::Color& color = DEFAULT_SPHERE_FILL_COLOR);
	void setShapeType(ShapeType shapeType);
	virtual ShapeType getShapeType() const override;
	const sf::CircleShape* getShape();

	////////////////////////////////////////////////////////////
	//// Put any constructors for this class here
	////////////////////////////////////////////////////////////
	PhysicsSphere() {
		setShapeType(ShapeType::SPHERE);
	};
	PhysicsSphere(const sf::Vector2f& position) {

		setShapeProperties(position);
	}
	PhysicsSphere(sf::Vector2f&& position) {

		setShapeProperties(position);
	}
	PhysicsSphere(const sf::Vector2f& position, float radius) {

		setShapeProperties(position, radius);
	}
	PhysicsSphere(sf::Vector2f&& position, float radius) {

		setShapeProperties(position, radius);
	}
	PhysicsSphere(const sf::Vector2f& position, float radius, std::size_t pointCount) {

		setShapeProperties(position, radius, pointCount);
	}
	PhysicsSphere(sf::Vector2f&& position, float radius, std::size_t pointCount) {

		setShapeProperties(position, radius, pointCount);
	}
	PhysicsSphere(const sf::Vector2f& position, float radius, std::size_t pointCount, const sf::Color& color) {

		setShapeProperties(position, radius, pointCount, color);
	}
	PhysicsSphere(sf::Vector2f&& position, float radius, std::size_t pointCount, const sf::Color& color) {

		setShapeProperties(position, radius, pointCount, color);
	}

	virtual ~PhysicsSphere() {
		std::cout << "DELETED " << "PHYSICS SPHERE" << '\n';
	}

};
