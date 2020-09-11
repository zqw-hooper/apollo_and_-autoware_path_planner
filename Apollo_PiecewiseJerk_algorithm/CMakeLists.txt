cmake_minimum_required(VERSION 3.5)
project(apollo_speed)

## Compile as C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11 -w)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Eigen3 REQUIRED)



include_directories(
        include
        osqp/include
        ${EIGEN3_INCLUDE_DIR}
)

link_directories(osqp/lib)

add_library(demo_lib
        src/ConstantJerkTrajectory1d.cpp
        src/DiscretizedPath.cpp
        src/IpoptInterface.cpp
        src/math.cpp
        src/PathPoint.cpp
        src/PiecewiseJerkPathProblem.cpp
        src/PiecewiseJerkProblem.cpp
        src/PiecewiseJerkSpeedNonlinearIpoptInterface.cpp
        src/PiecewiseJerkSpeed_nonlinear_Optimizer.cpp
        src/PiecewiseJerkSpeedProblem.cpp
        src/PiecewiseJerkTrajectory1d.cpp
        src/SpeedData.cpp
        src/SpeedLimit.cpp
        src/SpeedPoint.cpp
        src/SpeedProfileGenerator.cpp)

target_include_directories(demo_lib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        
        ${EIGEN3_INCLUDE_DIR} 
        osqp/include

        )
target_link_libraries(demo_lib
        
        glog
        osqp
        ipopt
        )




add_executable(demo
  src/demo.cpp)
target_link_libraries(demo  demo_lib)
