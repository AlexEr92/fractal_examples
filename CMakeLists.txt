cmake_minimum_required(VERSION 3.10)
project(fractal_examples)

find_package(X11 REQUIRED)

if (NOT X11_FOUND)
  message(FATAL_ERROR "X11 Not found!")
endif()

add_executable(sierpinski src/sierpinski.c)
target_include_directories(sierpinski PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(sierpinski ${X11_LIBRARIES})

add_executable(mandelbrot src/mandelbrot.c)
target_include_directories(mandelbrot PRIVATE ${X11_INCLUDE_DIR})
target_link_libraries(mandelbrot ${X11_LIBRARIES})
