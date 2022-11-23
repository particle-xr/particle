project(particle-bees)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} PRIVATE Particle::particle Threads::Threads)
