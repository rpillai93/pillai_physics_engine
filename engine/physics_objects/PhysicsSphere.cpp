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
	setVelocity(0.f, 0.f);
	setAcceleration(0.f, 4600.f); //assuming gravity is some large value here
}

void PhysicsSphere::Update(float deltaTime)
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

	std::cout << "V = " << v.y << '\n';
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

