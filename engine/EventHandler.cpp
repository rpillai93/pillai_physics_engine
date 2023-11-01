#include "EventHandler.hpp"
#include <cstdlib>
void EventHandler::handle()
{
	switch (type) {
	case sf::Event::MouseButtonPressed:
		handleMouseButtonPressed();
		break;
	case sf::Event::Closed:
		handleClosed();
		break;
	default:
		break;
	}
}

void EventHandler::handleClosed()
{
	window->close();
}

void EventHandler::handleMouseButtonPressed()
{

	int r = std::rand() % 256;
	int g = std::rand() % 256;
	int b = std::rand() % 256;
	sf::Color c(r, g, b, 255);

	switch (mouseButton.button) {
	case sf::Mouse::Button::Left:
		if (mouseButton.x > world->xConstraintLow && mouseButton.x < world->xConstraintHigh &&
			mouseButton.y > world->yConstraintLow && mouseButton.y < world->yConstraintHigh) {
			world->addObjectToWorld(new PhysicsSphere(sf::Vector2f(mouseButton.x, mouseButton.y), 30, 32, c));
		}
		break;
	case sf::Mouse::Button::Right:
		break;
	default:
		break;
	}
}
