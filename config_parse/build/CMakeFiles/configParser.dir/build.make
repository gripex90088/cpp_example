# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/xuxing/projects/cpp_example/config_parse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuxing/projects/cpp_example/config_parse/build

# Include any dependencies generated for this target.
include CMakeFiles/configParser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/configParser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/configParser.dir/flags.make

CMakeFiles/configParser.dir/src/main.cpp.o: CMakeFiles/configParser.dir/flags.make
CMakeFiles/configParser.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuxing/projects/cpp_example/config_parse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/configParser.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/configParser.dir/src/main.cpp.o -c /home/xuxing/projects/cpp_example/config_parse/src/main.cpp

CMakeFiles/configParser.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configParser.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuxing/projects/cpp_example/config_parse/src/main.cpp > CMakeFiles/configParser.dir/src/main.cpp.i

CMakeFiles/configParser.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configParser.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuxing/projects/cpp_example/config_parse/src/main.cpp -o CMakeFiles/configParser.dir/src/main.cpp.s

CMakeFiles/configParser.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/configParser.dir/src/main.cpp.o.requires

CMakeFiles/configParser.dir/src/main.cpp.o.provides: CMakeFiles/configParser.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/configParser.dir/build.make CMakeFiles/configParser.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/configParser.dir/src/main.cpp.o.provides

CMakeFiles/configParser.dir/src/main.cpp.o.provides.build: CMakeFiles/configParser.dir/src/main.cpp.o


CMakeFiles/configParser.dir/src/parse_conf.cpp.o: CMakeFiles/configParser.dir/flags.make
CMakeFiles/configParser.dir/src/parse_conf.cpp.o: ../src/parse_conf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuxing/projects/cpp_example/config_parse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/configParser.dir/src/parse_conf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/configParser.dir/src/parse_conf.cpp.o -c /home/xuxing/projects/cpp_example/config_parse/src/parse_conf.cpp

CMakeFiles/configParser.dir/src/parse_conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configParser.dir/src/parse_conf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuxing/projects/cpp_example/config_parse/src/parse_conf.cpp > CMakeFiles/configParser.dir/src/parse_conf.cpp.i

CMakeFiles/configParser.dir/src/parse_conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configParser.dir/src/parse_conf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuxing/projects/cpp_example/config_parse/src/parse_conf.cpp -o CMakeFiles/configParser.dir/src/parse_conf.cpp.s

CMakeFiles/configParser.dir/src/parse_conf.cpp.o.requires:

.PHONY : CMakeFiles/configParser.dir/src/parse_conf.cpp.o.requires

CMakeFiles/configParser.dir/src/parse_conf.cpp.o.provides: CMakeFiles/configParser.dir/src/parse_conf.cpp.o.requires
	$(MAKE) -f CMakeFiles/configParser.dir/build.make CMakeFiles/configParser.dir/src/parse_conf.cpp.o.provides.build
.PHONY : CMakeFiles/configParser.dir/src/parse_conf.cpp.o.provides

CMakeFiles/configParser.dir/src/parse_conf.cpp.o.provides.build: CMakeFiles/configParser.dir/src/parse_conf.cpp.o


CMakeFiles/configParser.dir/src/qstring.cpp.o: CMakeFiles/configParser.dir/flags.make
CMakeFiles/configParser.dir/src/qstring.cpp.o: ../src/qstring.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuxing/projects/cpp_example/config_parse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/configParser.dir/src/qstring.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/configParser.dir/src/qstring.cpp.o -c /home/xuxing/projects/cpp_example/config_parse/src/qstring.cpp

CMakeFiles/configParser.dir/src/qstring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/configParser.dir/src/qstring.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuxing/projects/cpp_example/config_parse/src/qstring.cpp > CMakeFiles/configParser.dir/src/qstring.cpp.i

CMakeFiles/configParser.dir/src/qstring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/configParser.dir/src/qstring.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuxing/projects/cpp_example/config_parse/src/qstring.cpp -o CMakeFiles/configParser.dir/src/qstring.cpp.s

CMakeFiles/configParser.dir/src/qstring.cpp.o.requires:

.PHONY : CMakeFiles/configParser.dir/src/qstring.cpp.o.requires

CMakeFiles/configParser.dir/src/qstring.cpp.o.provides: CMakeFiles/configParser.dir/src/qstring.cpp.o.requires
	$(MAKE) -f CMakeFiles/configParser.dir/build.make CMakeFiles/configParser.dir/src/qstring.cpp.o.provides.build
.PHONY : CMakeFiles/configParser.dir/src/qstring.cpp.o.provides

CMakeFiles/configParser.dir/src/qstring.cpp.o.provides.build: CMakeFiles/configParser.dir/src/qstring.cpp.o


# Object files for target configParser
configParser_OBJECTS = \
"CMakeFiles/configParser.dir/src/main.cpp.o" \
"CMakeFiles/configParser.dir/src/parse_conf.cpp.o" \
"CMakeFiles/configParser.dir/src/qstring.cpp.o"

# External object files for target configParser
configParser_EXTERNAL_OBJECTS =

configParser: CMakeFiles/configParser.dir/src/main.cpp.o
configParser: CMakeFiles/configParser.dir/src/parse_conf.cpp.o
configParser: CMakeFiles/configParser.dir/src/qstring.cpp.o
configParser: CMakeFiles/configParser.dir/build.make
configParser: CMakeFiles/configParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuxing/projects/cpp_example/config_parse/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable configParser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/configParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/configParser.dir/build: configParser

.PHONY : CMakeFiles/configParser.dir/build

CMakeFiles/configParser.dir/requires: CMakeFiles/configParser.dir/src/main.cpp.o.requires
CMakeFiles/configParser.dir/requires: CMakeFiles/configParser.dir/src/parse_conf.cpp.o.requires
CMakeFiles/configParser.dir/requires: CMakeFiles/configParser.dir/src/qstring.cpp.o.requires

.PHONY : CMakeFiles/configParser.dir/requires

CMakeFiles/configParser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/configParser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/configParser.dir/clean

CMakeFiles/configParser.dir/depend:
	cd /home/xuxing/projects/cpp_example/config_parse/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuxing/projects/cpp_example/config_parse /home/xuxing/projects/cpp_example/config_parse /home/xuxing/projects/cpp_example/config_parse/build /home/xuxing/projects/cpp_example/config_parse/build /home/xuxing/projects/cpp_example/config_parse/build/CMakeFiles/configParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/configParser.dir/depend

