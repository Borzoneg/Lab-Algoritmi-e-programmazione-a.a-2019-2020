# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Es__1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Es__1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Es__1.dir/flags.make

CMakeFiles/Es__1.dir/main.c.o: CMakeFiles/Es__1.dir/flags.make
CMakeFiles/Es__1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Es__1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Es__1.dir/main.c.o   -c "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/main.c"

CMakeFiles/Es__1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Es__1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/main.c" > CMakeFiles/Es__1.dir/main.c.i

CMakeFiles/Es__1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Es__1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/main.c" -o CMakeFiles/Es__1.dir/main.c.s

# Object files for target Es__1
Es__1_OBJECTS = \
"CMakeFiles/Es__1.dir/main.c.o"

# External object files for target Es__1
Es__1_EXTERNAL_OBJECTS =

Es__1: CMakeFiles/Es__1.dir/main.c.o
Es__1: CMakeFiles/Es__1.dir/build.make
Es__1: CMakeFiles/Es__1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Es__1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Es__1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Es__1.dir/build: Es__1

.PHONY : CMakeFiles/Es__1.dir/build

CMakeFiles/Es__1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Es__1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Es__1.dir/clean

CMakeFiles/Es__1.dir/depend:
	cd "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1" "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1" "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug" "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug" "/media/guglielmo/9E7B-0448/Programmazione/C/Algoritmi-e-programmazione-a.a-2019-2020/Lab 6/Es. 1/cmake-build-debug/CMakeFiles/Es__1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Es__1.dir/depend

