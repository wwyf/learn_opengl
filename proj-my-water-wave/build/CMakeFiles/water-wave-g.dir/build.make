# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\msys64\mingw32\bin\cmake.exe

# The command to remove a file.
RM = D:\msys64\mingw32\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\0code\learn_opengl\proj-my-water-wave

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\0code\learn_opengl\proj-my-water-wave\build

# Include any dependencies generated for this target.
include CMakeFiles/water-wave-g.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/water-wave-g.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/water-wave-g.dir/flags.make

CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj: CMakeFiles/water-wave-g.dir/flags.make
CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj: CMakeFiles/water-wave-g.dir/includes_CXX.rsp
CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj: ../source/gerstner-water.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\0code\learn_opengl\proj-my-water-wave\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj"
	D:\msys64\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\water-wave-g.dir\source\gerstner-water.cpp.obj -c E:\0code\learn_opengl\proj-my-water-wave\source\gerstner-water.cpp

CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.i"
	D:\msys64\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\0code\learn_opengl\proj-my-water-wave\source\gerstner-water.cpp > CMakeFiles\water-wave-g.dir\source\gerstner-water.cpp.i

CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.s"
	D:\msys64\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\0code\learn_opengl\proj-my-water-wave\source\gerstner-water.cpp -o CMakeFiles\water-wave-g.dir\source\gerstner-water.cpp.s

CMakeFiles/water-wave-g.dir/source/util.cpp.obj: CMakeFiles/water-wave-g.dir/flags.make
CMakeFiles/water-wave-g.dir/source/util.cpp.obj: CMakeFiles/water-wave-g.dir/includes_CXX.rsp
CMakeFiles/water-wave-g.dir/source/util.cpp.obj: ../source/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\0code\learn_opengl\proj-my-water-wave\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/water-wave-g.dir/source/util.cpp.obj"
	D:\msys64\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\water-wave-g.dir\source\util.cpp.obj -c E:\0code\learn_opengl\proj-my-water-wave\source\util.cpp

CMakeFiles/water-wave-g.dir/source/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/water-wave-g.dir/source/util.cpp.i"
	D:\msys64\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\0code\learn_opengl\proj-my-water-wave\source\util.cpp > CMakeFiles\water-wave-g.dir\source\util.cpp.i

CMakeFiles/water-wave-g.dir/source/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/water-wave-g.dir/source/util.cpp.s"
	D:\msys64\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\0code\learn_opengl\proj-my-water-wave\source\util.cpp -o CMakeFiles\water-wave-g.dir\source\util.cpp.s

# Object files for target water-wave-g
water__wave__g_OBJECTS = \
"CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj" \
"CMakeFiles/water-wave-g.dir/source/util.cpp.obj"

# External object files for target water-wave-g
water__wave__g_EXTERNAL_OBJECTS =

water-wave-g.exe: CMakeFiles/water-wave-g.dir/source/gerstner-water.cpp.obj
water-wave-g.exe: CMakeFiles/water-wave-g.dir/source/util.cpp.obj
water-wave-g.exe: CMakeFiles/water-wave-g.dir/build.make
water-wave-g.exe: CMakeFiles/water-wave-g.dir/linklibs.rsp
water-wave-g.exe: CMakeFiles/water-wave-g.dir/objects1.rsp
water-wave-g.exe: CMakeFiles/water-wave-g.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\0code\learn_opengl\proj-my-water-wave\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable water-wave-g.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\water-wave-g.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/water-wave-g.dir/build: water-wave-g.exe

.PHONY : CMakeFiles/water-wave-g.dir/build

CMakeFiles/water-wave-g.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\water-wave-g.dir\cmake_clean.cmake
.PHONY : CMakeFiles/water-wave-g.dir/clean

CMakeFiles/water-wave-g.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\0code\learn_opengl\proj-my-water-wave E:\0code\learn_opengl\proj-my-water-wave E:\0code\learn_opengl\proj-my-water-wave\build E:\0code\learn_opengl\proj-my-water-wave\build E:\0code\learn_opengl\proj-my-water-wave\build\CMakeFiles\water-wave-g.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/water-wave-g.dir/depend

