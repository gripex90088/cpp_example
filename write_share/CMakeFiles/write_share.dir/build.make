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
CMAKE_COMMAND = /home/software/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/software/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/debian/Cprojects/write_share

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/debian/Cprojects/write_share

# Include any dependencies generated for this target.
include CMakeFiles/write_share.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/write_share.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/write_share.dir/flags.make

CMakeFiles/write_share.dir/main.cpp.o: CMakeFiles/write_share.dir/flags.make
CMakeFiles/write_share.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/debian/Cprojects/write_share/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/write_share.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/write_share.dir/main.cpp.o -c /home/debian/Cprojects/write_share/main.cpp

CMakeFiles/write_share.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/write_share.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/debian/Cprojects/write_share/main.cpp > CMakeFiles/write_share.dir/main.cpp.i

CMakeFiles/write_share.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/write_share.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/debian/Cprojects/write_share/main.cpp -o CMakeFiles/write_share.dir/main.cpp.s

# Object files for target write_share
write_share_OBJECTS = \
"CMakeFiles/write_share.dir/main.cpp.o"

# External object files for target write_share
write_share_EXTERNAL_OBJECTS =

write_share: CMakeFiles/write_share.dir/main.cpp.o
write_share: CMakeFiles/write_share.dir/build.make
write_share: CMakeFiles/write_share.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/debian/Cprojects/write_share/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable write_share"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/write_share.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/write_share.dir/build: write_share

.PHONY : CMakeFiles/write_share.dir/build

CMakeFiles/write_share.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/write_share.dir/cmake_clean.cmake
.PHONY : CMakeFiles/write_share.dir/clean

CMakeFiles/write_share.dir/depend:
	cd /home/debian/Cprojects/write_share && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/debian/Cprojects/write_share /home/debian/Cprojects/write_share /home/debian/Cprojects/write_share /home/debian/Cprojects/write_share /home/debian/Cprojects/write_share/CMakeFiles/write_share.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/write_share.dir/depend

