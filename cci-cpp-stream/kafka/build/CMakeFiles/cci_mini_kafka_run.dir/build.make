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
CMAKE_SOURCE_DIR = /cci_src/cci-develop/cci-cpp-stream/kafka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cci_src/cci-develop/cci-cpp-stream/kafka/build

# Include any dependencies generated for this target.
include CMakeFiles/cci_mini_kafka_run.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cci_mini_kafka_run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cci_mini_kafka_run.dir/flags.make

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o: CMakeFiles/cci_mini_kafka_run.dir/flags.make
CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o: ../cci_mini_kafka_run.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cci_src/cci-develop/cci-cpp-stream/kafka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o"
	/usr/bin/clang++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o -c /cci_src/cci-develop/cci-cpp-stream/kafka/cci_mini_kafka_run.cpp

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.i"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cci_src/cci-develop/cci-cpp-stream/kafka/cci_mini_kafka_run.cpp > CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.i

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.s"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cci_src/cci-develop/cci-cpp-stream/kafka/cci_mini_kafka_run.cpp -o CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.s

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.requires:

.PHONY : CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.requires

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.provides: CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.requires
	$(MAKE) -f CMakeFiles/cci_mini_kafka_run.dir/build.make CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.provides.build
.PHONY : CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.provides

CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.provides.build: CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o


# Object files for target cci_mini_kafka_run
cci_mini_kafka_run_OBJECTS = \
"CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o"

# External object files for target cci_mini_kafka_run
cci_mini_kafka_run_EXTERNAL_OBJECTS =

cci_mini_kafka_run: CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o
cci_mini_kafka_run: CMakeFiles/cci_mini_kafka_run.dir/build.make
cci_mini_kafka_run: libcci_kafka_stream.so.1.0.0
cci_mini_kafka_run: CMakeFiles/cci_mini_kafka_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cci_src/cci-develop/cci-cpp-stream/kafka/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cci_mini_kafka_run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cci_mini_kafka_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cci_mini_kafka_run.dir/build: cci_mini_kafka_run

.PHONY : CMakeFiles/cci_mini_kafka_run.dir/build

CMakeFiles/cci_mini_kafka_run.dir/requires: CMakeFiles/cci_mini_kafka_run.dir/cci_mini_kafka_run.cpp.o.requires

.PHONY : CMakeFiles/cci_mini_kafka_run.dir/requires

CMakeFiles/cci_mini_kafka_run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cci_mini_kafka_run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cci_mini_kafka_run.dir/clean

CMakeFiles/cci_mini_kafka_run.dir/depend:
	cd /cci_src/cci-develop/cci-cpp-stream/kafka/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cci_src/cci-develop/cci-cpp-stream/kafka /cci_src/cci-develop/cci-cpp-stream/kafka /cci_src/cci-develop/cci-cpp-stream/kafka/build /cci_src/cci-develop/cci-cpp-stream/kafka/build /cci_src/cci-develop/cci-cpp-stream/kafka/build/CMakeFiles/cci_mini_kafka_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cci_mini_kafka_run.dir/depend

