# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build

# Include any dependencies generated for this target.
include CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/flags.make

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/flags.make
CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o: ../src/demo_PiecewiseJerkSpeedOptimizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o -c /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/src/demo_PiecewiseJerkSpeedOptimizer.cpp

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/src/demo_PiecewiseJerkSpeedOptimizer.cpp > CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.i

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/src/demo_PiecewiseJerkSpeedOptimizer.cpp -o CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.s

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.requires:

.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.requires

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.provides: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/build.make CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.provides.build
.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.provides

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.provides.build: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o


# Object files for target demo_PiecewiseJerkSpeedOptimizer
demo_PiecewiseJerkSpeedOptimizer_OBJECTS = \
"CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o"

# External object files for target demo_PiecewiseJerkSpeedOptimizer
demo_PiecewiseJerkSpeedOptimizer_EXTERNAL_OBJECTS =

demo_PiecewiseJerkSpeedOptimizer: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o
demo_PiecewiseJerkSpeedOptimizer: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/build.make
demo_PiecewiseJerkSpeedOptimizer: libdemo_lib.a
demo_PiecewiseJerkSpeedOptimizer: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo_PiecewiseJerkSpeedOptimizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/build: demo_PiecewiseJerkSpeedOptimizer

.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/build

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/requires: CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/src/demo_PiecewiseJerkSpeedOptimizer.cpp.o.requires

.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/requires

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/clean

CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/depend:
	cd /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build /home/ak/Desktop/Apollo_and_Autoware_path_planner/Apollo_PiecewiseJerk_algorithm/build/CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo_PiecewiseJerkSpeedOptimizer.dir/depend

