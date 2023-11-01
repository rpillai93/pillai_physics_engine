#include "PhysicsBox.hpp"

void PhysicsBox::Initialize()
{
	setVelocity(0.f, 0.f);
	setAcceleration(0.f, 4600.f); //assuming gravity is some large value here
}

void PhysicsBox::Update(float deltaTime)
{
	const sf::Vector2<float>& p = getPosition();
	const sf::Vector2<float>& v = getVelocity();
	const sf::Vector2<float>& a = getAcceleration();


	// Formula used below: 
	// displacement = v * deltaTime + 0.5 * a * (deltaTime)^2 approximately equals v * deltaTime for small deltaTime:
	setPosition(p.x + v.x * deltaTime, p.y + v.y * deltaTime); // approximated

	// v(final) = v(initial) + a * deltaTime
	setVelocity(v.x + a.x * deltaTime, v.y + a.y * deltaTime);

	setAcceleration(a.x, a.y); // unchanged for only gravity acting on the body

}

const sf::Vector2f& PhysicsBox::getPosition() const
{
	return sf::Transformable::getPosition();
}

void PhysicsBox::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
}

const sf::Vector2f& PhysicsBox::getVelocity() const
{
	return m_Velocity;
}

void PhysicsBox::setVelocity(float x, float y)
{
}

const sf::Vector2f& PhysicsBox::getAcceleration() const
{
	return m_Acceleration;
}

void PhysicsBox::setAcceleration(float x, float y)
{
}

void PhysicsBox::addForce(const sf::Vector2f& g)
{
}

const sf::Vector2f& PhysicsBox::getForceAccumulator() const
{
	return m_ForceAccumulator;
}

const sf::Vector2f& PhysicsBox::getCenterOfMass()
{
	const sf::Vector2f& p = getPosition();
	const sf::Vector2f& s = getSize();
	m_CenterOfMass.x = p.x + (s.x / 2);	m_CenterOfMass.y = p.y + (s.y / 2);
	return m_CenterOfMass;

}

bool PhysicsBox::isFixedPosition() const
{
	return m_IsFixed;
}

void PhysicsBox::setIsFixedPosition(bool isFixed)
{
	m_IsFixed = isFixed;
}

bool PhysicsBox::getGravityOn() const
{
	return false;
}

void PhysicsBox::setGravityOn()
{
}

void PhysicsBox::setGravityOff()
{
}

float PhysicsBox::getGravityValue() const
{
	return 0.0f;
}

void PhysicsBox::setGravityValue(float g)
{
}

bool PhysicsBox::getDampingOn() const
{
	return false;
}

void PhysicsBox::setDampingOn()
{
}

void PhysicsBox::setDampingOff()
{
}

float PhysicsBox::getDampingValue() const
{
	return 0.0f;
}

void PhysicsBox::setDampingValue(float d)
{
}

float PhysicsBox::getInverseMass() const
{
	return m_InverseMass;
}

void PhysicsBox::setInverseMass(float m)
{
	m_InverseMass = m;
}

void PhysicsBox::setInitializeComplete()
{
	InitializeComplete = true;
}

bool PhysicsBox::getInitializeComplete() const
{
	return InitializeComplete;
}

void PhysicsBox::setShapeProperties(const sf::Vector2f& position, float width, float height, const sf::Color& color)
{
	setShapeType(ShapeType::BOX);
	sf::RectangleShape::setSize(sf::Vector2f(width, height));
	sf::RectangleShape::setFillColor(color);
	sf::RectangleShape::setPosition(position.x, position.y);
}

void PhysicsBox::setShapeType(ShapeType shapeType)
{
	m_ShapeType = shapeType;
}

ShapeType PhysicsBox::getShapeType() const
{
	return m_ShapeType;
}

const sf::RectangleShape* PhysicsBox::getShape()
{
	sf::RectangleShape* rectangle = dynamic_cast<sf::RectangleShape*>(this);

	return rectangle;
}
