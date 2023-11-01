#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "physics_objects/PhysicsSphere.hpp"
#include "physics_objects/PhysicsBox.hpp"
#include "PhysicsWorld.hpp"
class EventHandler : public sf::Event {
private:

public:

	EventHandler() = default;

	void handle();
	void handleClosed();
	void handleMouseButtonPressed();

	sf::RenderWindow* window;
	PhysicsWorld* world;
};