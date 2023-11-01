# all root CMakeLists should start with a cmake_minimum_required command
cmake_minimum_required(VERSION 3.14)

# also need a project command
project(PhysicsEngine)

# find sfml
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

file(GLOB_RECURSE PHYSICS_ENGINE_SOURCES "engine/*.cpp" "engine/*.hpp")
# add executables with this and main source file
add_executable(PhysicsEngine PhysicsEngine.cpp ${PHYSICS_ENGINE_SOURCES})
# this is a VS specific property to set your project as default run
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PhysicsEngine)
target_link_libraries(PhysicsEngine PRIVATE sfml-system sfml-graphics sfml-window)