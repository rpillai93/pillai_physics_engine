#include "Project.hpp"
#include "helpers/MyMath.hpp"
#include "helpers/DebugMacros.hpp"


void Project::Launch()
{
	Tick();
}

void Project::Initialize()
{
	std::cout << "Project::Initialize()" << '\n';

	m_Window.create(sf::VideoMode(1920, 1080), "Physics Engine");

	sf::Vector2u windowSize = m_Window.getSize();
	//INITIALIZE PHYSICS WORLD
	mPhysicsWorld = new PhysicsWorld();
	//SET THE GROUND FOR THE WORLD
	float groundThickness = 200;
	mPhysicsWorld->setGround(new PhysicsBox(sf::Vector2f(0, windowSize.y - groundThickness), windowSize.x, groundThickness));
	mPhysicsWorld->getGround()->setIsFixedPosition(true);


	m_Event.window = &m_Window;
	m_Event.world = mPhysicsWorld;

	m_InitialTime = std::chrono::high_resolution_clock::now();
}

//Update():Updates object positions every frame
void Project::Update()
{
	m_FinalTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(m_FinalTime - m_InitialTime).count();
	m_InitialTime = m_FinalTime;

	mPhysicsWorld->Update(deltaTime);
}


void Project::Draw()
{
	m_Window.clear();

	PhysicsBox* ground = mPhysicsWorld->getGround();
	m_Window.draw(*ground->getShape());

	for (auto* obj : mPhysicsWorld->PhysicsObjects) {
		auto* circle = dynamic_cast<PhysicsSphere*>(obj);
		if (circle != nullptr) {
			m_Window.draw(*circle);
		}
	}

	m_Window.display();
}


void Project::EventListener()
{
	while (m_Window.pollEvent(m_Event)) {
		m_Event.handle();
	}
}

void Project::Tick()
{

	Initialize(); // Initialize the project, the physics world and it's objects and start the clock

	while (m_Window.isOpen()) {
		{
			Clock TickClock;
			TickClock.start();
			EventListener(); // Listening for keyboard events from the user
			Update();		 // Updating the Physics world and all if it's physics bodies
			Draw();          // Drawing the objects to the canvas
			TickClock.stop();
			//std::cout << "Project::Tick()" << '\n';
		}
	}

}



