#pragma once

#include "SFML/Graphics.hpp"

#include "helpers/Clock.hpp"
#include "physics_objects/PhysicsSphere.hpp"
#include "physics_objects/PhysicsBox.hpp"
#include "PhysicsWorld.hpp"
#include "EventHandler.hpp"
enum Direction {
	Downward,
	Upward
};
class Project {
public:
	~Project() {
		std::cout << "Calling ~Project() (Destroying Project...) " << '\n';
		delete mPhysicsWorld;
	}
	void Launch();
	std::chrono::steady_clock::time_point m_InitialTime;
	std::chrono::steady_clock::time_point m_FinalTime;
	float deltaTime;
private:
	sf::RenderWindow m_Window;
	PhysicsWorld* mPhysicsWorld;
	EventHandler m_Event;



	////////////////////////////////////////////////////////////
	//// Initialize(): Initializes all Physics World Objects 
	//// for the first frame
	////////////////////////////////////////////////////////////
	void Initialize();

	////////////////////////////////////////////////////////////
	//// EventListener(): Listens for input events by the user 
	////////////////////////////////////////////////////////////
	void EventListener();

	////////////////////////////////////////////////////////////
	//// Update():  Updates all Physics World Objects every 
	//// frame
	////////////////////////////////////////////////////////////
	void Update();


	////////////////////////////////////////////////////////////
	//// Draw(): Draws / renders objects in the scene 
	//// after their positions are updated
	////////////////////////////////////////////////////////////
	void Draw();


	////////////////////////////////////////////////////////////
	//// Tick(): Handles tick events every frame
	////////////////////////////////////////////////////////////
	void Tick();



};
