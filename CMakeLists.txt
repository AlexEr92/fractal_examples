cmake_minimum_required(VERSION 3.10)
project(fractal_examples)

find_package(X11 REQUIRED)

if (NOT X11_FOUND)
  message(FATAL_ERROR "X11 Not found!")
endif()

add_executable(sierpinski src/sierpinski.c)
target_include_directories(sierpinski PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(sierpinski ${X11_LIBRARIES})

add_executable(maldenbrot src/maldenbrot.c)
target_include_directories(maldenbrot PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(maldenbrot ${X11_LIBRARIES})
