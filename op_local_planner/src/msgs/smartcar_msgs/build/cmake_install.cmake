# Install script for directory: /home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE PROGRAM FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/_setup_util.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE PROGRAM FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/env.sh")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/setup.bash;/usr/local/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE FILE FILES
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/setup.bash"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/setup.sh;/usr/local/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE FILE FILES
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/setup.sh"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/setup.zsh;/usr/local/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE FILE FILES
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/setup.zsh"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local" TYPE FILE FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/msg" TYPE FILE FILES
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/Lane.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ControlCommand.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ControlCommandStamped.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/Waypoint.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/LaneArray.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/PointsImage.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ProjectionMatrix.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageObj.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageObjects.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageObjTracked.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageObjRanged.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageRect.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageRectRanged.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/DetectedObject.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/DetectedObjectArray.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/TrafficLightResult.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/TrafficLight.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/TrafficLightResultArray.msg"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg/ImageLaneObjects.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/smartcar_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/include/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/share/roseus/ros/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/share/common-lisp/ros/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/share/gennodejs/ros/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/lib/python2.7/dist-packages/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/devel/lib/python2.7/dist-packages/smartcar_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/smartcar_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/smartcar_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs/cmake" TYPE FILE FILES
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/smartcar_msgsConfig.cmake"
    "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/catkin_generated/installspace/smartcar_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/smartcar_msgs" TYPE FILE FILES "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
