# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build

# Include any dependencies generated for this target.
include CMakeFiles/lb_flood.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lb_flood.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lb_flood.dir/flags.make

CMakeFiles/lb_flood.dir/src/Flood.cpp.o: CMakeFiles/lb_flood.dir/flags.make
CMakeFiles/lb_flood.dir/src/Flood.cpp.o: ../src/Flood.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lb_flood.dir/src/Flood.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lb_flood.dir/src/Flood.cpp.o -c /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/src/Flood.cpp

CMakeFiles/lb_flood.dir/src/Flood.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lb_flood.dir/src/Flood.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/src/Flood.cpp > CMakeFiles/lb_flood.dir/src/Flood.cpp.i

CMakeFiles/lb_flood.dir/src/Flood.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lb_flood.dir/src/Flood.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/src/Flood.cpp -o CMakeFiles/lb_flood.dir/src/Flood.cpp.s

# Object files for target lb_flood
lb_flood_OBJECTS = \
"CMakeFiles/lb_flood.dir/src/Flood.cpp.o"

# External object files for target lb_flood
lb_flood_EXTERNAL_OBJECTS =

liblb_flood.a: CMakeFiles/lb_flood.dir/src/Flood.cpp.o
liblb_flood.a: CMakeFiles/lb_flood.dir/build.make
liblb_flood.a: CMakeFiles/lb_flood.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblb_flood.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lb_flood.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lb_flood.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lb_flood.dir/build: liblb_flood.a

.PHONY : CMakeFiles/lb_flood.dir/build

CMakeFiles/lb_flood.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lb_flood.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lb_flood.dir/clean

CMakeFiles/lb_flood.dir/depend:
	cd /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build /home/alecs/github/Topicos-3---Processamento-de-Imagens/Flood/build/CMakeFiles/lb_flood.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lb_flood.dir/depend

