cmake_minimum_required(VERSION 3.2)
project(osqp_demo)
add_definitions(-std=c++11)
# Find OSQP library and headers
find_package(osqp REQUIRED)


find_package(PythonLibs 3.6)
include_directories(${PYTHON_INCLUDE_DIRS})  #使用这方式可以替代下面这行


include_directories(
)
set(CMAKE_BUILD_TYPE Debug)
# Link the OSQP shared library
set (SRCS osqp_demo.cc osqp_problem.cc)

add_executable(osqp_demo ${SRCS})
target_link_libraries(osqp_demo PRIVATE osqp::osqp)

# or...

# Link the OSQP static library
# target_link_libraries(yourTarget PRIVATE osqp::osqpstatic)
