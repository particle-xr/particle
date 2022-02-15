enable_testing()

find_package(doctest REQUIRED)

file(GLOB TESTS particle/*.test.cpp)

foreach(TEST ${TESTS})
  get_filename_component(NAME ${TEST} NAME_WE)
  set(TESTNAME test-${NAME})

  add_executable(${TESTNAME} ${TEST})
  target_link_libraries(${TESTNAME} PRIVATE Particle::particle doctest::doctest)

  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endforeach()
