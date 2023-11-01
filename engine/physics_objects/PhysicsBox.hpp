#pragma once
#include "IPhysicsObject.hpp"
#include <iostream>
////////////////////////////////////////////////////////////
//// PhysicsBox
//// A box object with a rectangular shape that can simulate physics. All of the shape
//// behavior is inherited from the parent RectangleShape and physics behavior
//// from the parent interface IPhysicsObject. Only basic shape behavior
//// and properties are defined here. 
////////////////////////////////////////////////////////////
constexpr static float DEFAULT_WIDTH = 40.0f;
constexpr static float DEFAULT_HEIGHT = 20.0f;
static sf::Color DEFAULT_BOX_FILL_COLOR = sf::Color::White;
class PhysicsBox : public sf::RectangleShape, public IPhysicsObject {

private:
	ShapeType m_ShapeType;
	sf::Vector2f m_Displacement;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;
	sf::Vector2f m_ForceAccumulator;
	sf::Vector2f m_CenterOfMass;
	bool m_IsFixed = false;
	float m_InverseMass = 1.0f;
public:
	////////////////////////////////////////////////////////////
	//// IPhysicsObject Behavior Functions
	//// Position = top left point of the bounding box containing the physics object
	//// Cener of Mass = center point of the physics object
	//// Position is set to be the same as the shape / transformable position.
	//// All other behavior is newly defined behavior for all IPhysicsObjects.
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
	const sf::Vector2f& getCenterOfMass();
	virtual void addForce(const sf::Vector2f& g) override;
	virtual const sf::Vector2f& getForceAccumulator() const override;
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
	//// RectangleShape Behavior Functions
	////////////////////////////////////////////////////////////
	void setShapeProperties(const sf::Vector2f& position, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT, const sf::Color& color = DEFAULT_BOX_FILL_COLOR);
	void setShapeType(ShapeType shapeType);
	virtual ShapeType getShapeType() const override;
	const sf::RectangleShape* getShape();

	////////////////////////////////////////////////////////////
	//// Put any constructors for this class here
	////////////////////////////////////////////////////////////
	PhysicsBox() {
		setShapeType(ShapeType::BOX);
	};
	PhysicsBox(const sf::Vector2f& position) {

		setShapeProperties(position);
	}
	PhysicsBox(sf::Vector2f&& position) {

		setShapeProperties(position);
	}
	PhysicsBox(const sf::Vector2f& position, float width, float height) {

		setShapeProperties(position, width, height);
	}
	PhysicsBox(const sf::Vector2f&& position, float width, float height) {

		setShapeProperties(position, width, height);
	}
	PhysicsBox(const sf::Vector2f& position, float width, float height, const sf::Color& color) {

		setShapeProperties(position, width, height, color);
	}
	PhysicsBox(sf::Vector2f&& position, float width, float height, const sf::Color& color) {

		setShapeProperties(position, width, height, color);
	}

	virtual ~PhysicsBox() {
		std::cout << "DELETED " << "PHYSICS BOX" << '\n';
	}

};
