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

# Utility rule file for debug-StrTestConstructorTests.NullInputConstructor.

# Include the progress variables for this target.
include str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/progress.make

str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging StrTestConstructorTests.NullInputConstructor with GDB..."
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol && gdb --args /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/str_tests/str_tests --gtest_filter=StrTestConstructorTests.NullInputConstructor

debug-StrTestConstructorTests.NullInputConstructor: str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor
debug-StrTestConstructorTests.NullInputConstructor: str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/build.make

.PHONY : debug-StrTestConstructorTests.NullInputConstructor

# Rule to build all files generated by this target.
str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/build: debug-StrTestConstructorTests.NullInputConstructor

.PHONY : str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/build

str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/clean:
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/str_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/cmake_clean.cmake
.PHONY : str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/clean

str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/depend:
	cd /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/str_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/str_tests /home/cs104/Desktop/grading_testing/grading-tools/hw1_sol/hw1_tests/str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : str_tests/CMakeFiles/debug-StrTestConstructorTests.NullInputConstructor.dir/depend

