#include "PhysicsSphere.hpp"

const sf::Vector2f& PhysicsSphere::getPosition() const
{
	return sf::Transformable::getPosition();
}

void PhysicsSphere::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
}

const sf::Vector2f& PhysicsSphere::getVelocity() const
{
	return m_Velocity;
}

void PhysicsSphere::setVelocity(float x, float y)
{
	m_Velocity.x = x; m_Velocity.y = y;
}

const sf::Vector2f& PhysicsSphere::getAcceleration() const
{
	return m_Acceleration;
}

void PhysicsSphere::setAcceleration(float x, float y)
{
	m_Acceleration.x = x; m_Acceleration.y = y;
}

const sf::Vector2f& PhysicsSphere::getForceAccumulator() const
{
	return m_ForceAccumulator;
}

void PhysicsSphere::addForce(const sf::Vector2f& g)
{
	m_ForceAccumulator.x += g.x; m_ForceAccumulator.y += g.y;
}

const sf::Vector2f& PhysicsSphere::getCenterOfMass()
{
	const sf::Vector2f& p = getPosition();
	float r = getRadius();
	m_CenterOfMass.x = p.x + r;	m_CenterOfMass.y = p.y + r;
	return m_CenterOfMass;
}

void PhysicsSphere::Initialize()
{
	const sf::Vector2f& p = getPosition();
	m_Displacement.x = p.x; m_Displacement.y = p.y;
	m_Velocity.x = 0; m_Velocity.y = 0;
	m_Acceleration.x = 0; m_Acceleration.y = 4600.f;
}

void PhysicsSphere::Update(float deltaTime)
{
	sf::Vector2<float> p = getPosition();
	m_Displacement.x = (m_Velocity.x * deltaTime) + 0.5f * m_Acceleration.x * (deltaTime * deltaTime);
	if (m_Displacement.x < 0.009) m_Displacement.x = 0; if (m_Displacement.y < 0.009) m_Displacement.y = 0;
	m_Displacement.y = (m_Velocity.y * deltaTime) + 0.5f * m_Acceleration.y * (deltaTime * deltaTime);
	m_Velocity.x = m_Velocity.x + m_Acceleration.x * deltaTime;
	m_Velocity.y = m_Velocity.y + m_Acceleration.y * deltaTime;
	setPosition(p.x + m_Displacement.x, p.y + m_Displacement.y);

}

float PhysicsSphere::getInverseMass() const
{
	return m_InverseMass;
}

void PhysicsSphere::setInverseMass(float im)
{
	m_InverseMass = im;
}

void PhysicsSphere::setShapeProperties(const sf::Vector2f& position, float radius, std::size_t pointCount, const sf::Color& color)
{
	setShapeType(ShapeType::SPHERE);
	sf::CircleShape::setRadius(radius);
	sf::CircleShape::setPointCount(pointCount);
	sf::CircleShape::setFillColor(color);
	sf::CircleShape::setPosition(position.x, position.y);
}

void PhysicsSphere::setShapeType(ShapeType shapeType)
{
	m_ShapeType = shapeType;
}


const sf::CircleShape* PhysicsSphere::getShape()
{
	sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(this);

	return circle;
}

void PhysicsSphere::setInitializeComplete()
{
	InitializeComplete = true;
}

bool PhysicsSphere::getInitializeComplete() const
{
	return InitializeComplete;
}

bool PhysicsSphere::isFixedPosition() const
{
	return m_IsFixed;
}

void PhysicsSphere::setIsFixedPosition(bool isFixed) {
	m_IsFixed = isFixed;
}

bool PhysicsSphere::getGravityOn() const {
	return m_GravityOn;
}

void PhysicsSphere::setGravityOn() {
	m_GravityOn = true;
}

void PhysicsSphere::setGravityOff() {
	m_GravityOn = false;
}

float PhysicsSphere::getGravityValue() const {
	return m_Gravity;
}

void PhysicsSphere::setGravityValue(float g) {
	m_Gravity = g;
}

bool PhysicsSphere::getDampingOn() const {
	return m_DampingOn;
}

void PhysicsSphere::setDampingOn() {
	m_DampingOn = true;
}

void PhysicsSphere::setDampingOff() {
	m_DampingOn = false;
}

float PhysicsSphere::getDampingValue() const {
	return m_Damping;
}

void PhysicsSphere::setDampingValue(float d) {
	m_Damping = d;
}

ShapeType PhysicsSphere::getShapeType() const
{
	return m_ShapeType;
}

