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
CMAKE_SOURCE_DIR = /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests

# Include any dependencies generated for this target.
include tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/depend.make

# Include the progress variables for this target.
include tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/flags.make

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/flags.make
tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o: tweet_parse_tests/tweet_parse_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o"
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o -c /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests/tweet_parse_test.cpp

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.i"
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests/tweet_parse_test.cpp > CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.i

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.s"
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests/tweet_parse_test.cpp -o CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.s

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.requires:

.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.requires

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.provides: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.requires
	$(MAKE) -f tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/build.make tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.provides.build
.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.provides

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.provides.build: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o


# Object files for target tweet_parse_tests
tweet_parse_tests_OBJECTS = \
"CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o"

# External object files for target tweet_parse_tests
tweet_parse_tests_EXTERNAL_OBJECTS =

tweet_parse_tests/tweet_parse_tests: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o
tweet_parse_tests/tweet_parse_tests: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/build.make
tweet_parse_tests/tweet_parse_tests: testing_utils/libtesting_utils.a
tweet_parse_tests/tweet_parse_tests: /usr/lib/libgtest_main.a
tweet_parse_tests/tweet_parse_tests: /usr/lib/libgtest.a
tweet_parse_tests/tweet_parse_tests: testing_utils/kwsys/libkwsys.a
tweet_parse_tests/tweet_parse_tests: testing_utils/libperf/libperf.a
tweet_parse_tests/tweet_parse_tests: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tweet_parse_tests"
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tweet_parse_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/build: tweet_parse_tests/tweet_parse_tests

.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/build

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/requires: tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/tweet_parse_test.cpp.o.requires

.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/requires

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/clean:
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests && $(CMAKE_COMMAND) -P CMakeFiles/tweet_parse_tests.dir/cmake_clean.cmake
.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/clean

tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/depend:
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tweet_parse_tests/CMakeFiles/tweet_parse_tests.dir/depend

