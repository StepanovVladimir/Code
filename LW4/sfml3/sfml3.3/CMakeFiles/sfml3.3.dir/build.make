# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = C:\CppDistro-32bit\CppDistro32\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\CppDistro-32bit\CppDistro32\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Code\LW4\sfml3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Code\LW4\sfml3

# Include any dependencies generated for this target.
include sfml3.3/CMakeFiles/sfml3.3.dir/depend.make

# Include the progress variables for this target.
include sfml3.3/CMakeFiles/sfml3.3.dir/progress.make

# Include the compile flags for this target's objects.
include sfml3.3/CMakeFiles/sfml3.3.dir/flags.make

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj: sfml3.3/CMakeFiles/sfml3.3.dir/flags.make
sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj: sfml3.3/CMakeFiles/sfml3.3.dir/includes_CXX.rsp
sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj: sfml3.3/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Code\LW4\sfml3\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj"
	cd /d C:\Code\LW4\sfml3\sfml3.3 && C:\CppDistro-32bit\CppDistro32\msys32\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\sfml3.3.dir\main.cpp.obj -c C:\Code\LW4\sfml3\sfml3.3\main.cpp

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml3.3.dir/main.cpp.i"
	cd /d C:\Code\LW4\sfml3\sfml3.3 && C:\CppDistro-32bit\CppDistro32\msys32\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Code\LW4\sfml3\sfml3.3\main.cpp > CMakeFiles\sfml3.3.dir\main.cpp.i

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml3.3.dir/main.cpp.s"
	cd /d C:\Code\LW4\sfml3\sfml3.3 && C:\CppDistro-32bit\CppDistro32\msys32\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Code\LW4\sfml3\sfml3.3\main.cpp -o CMakeFiles\sfml3.3.dir\main.cpp.s

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.requires:

.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.requires

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.provides: sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.requires
	$(MAKE) -f sfml3.3\CMakeFiles\sfml3.3.dir\build.make sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.provides.build
.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.provides

sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.provides.build: sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj


# Object files for target sfml3.3
sfml3_3_OBJECTS = \
"CMakeFiles/sfml3.3.dir/main.cpp.obj"

# External object files for target sfml3.3
sfml3_3_EXTERNAL_OBJECTS =

sfml3.3/sfml3.3.exe: sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj
sfml3.3/sfml3.3.exe: sfml3.3/CMakeFiles/sfml3.3.dir/build.make
sfml3.3/sfml3.3.exe: C:/CppDistro-32bit/CppDistro32/msys32/mingw32/lib/libsfml-window-s-d.a
sfml3.3/sfml3.3.exe: C:/CppDistro-32bit/CppDistro32/msys32/mingw32/lib/libsfml-graphics-s-d.a
sfml3.3/sfml3.3.exe: C:/CppDistro-32bit/CppDistro32/msys32/mingw32/lib/libsfml-system-s-d.a
sfml3.3/sfml3.3.exe: C:/CppDistro-32bit/CppDistro32/msys32/mingw32/lib/libfreetype.dll.a
sfml3.3/sfml3.3.exe: C:/CppDistro-32bit/CppDistro32/msys32/mingw32/lib/libjpeg.dll.a
sfml3.3/sfml3.3.exe: sfml3.3/CMakeFiles/sfml3.3.dir/linklibs.rsp
sfml3.3/sfml3.3.exe: sfml3.3/CMakeFiles/sfml3.3.dir/objects1.rsp
sfml3.3/sfml3.3.exe: sfml3.3/CMakeFiles/sfml3.3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Code\LW4\sfml3\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sfml3.3.exe"
	cd /d C:\Code\LW4\sfml3\sfml3.3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sfml3.3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sfml3.3/CMakeFiles/sfml3.3.dir/build: sfml3.3/sfml3.3.exe

.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/build

sfml3.3/CMakeFiles/sfml3.3.dir/requires: sfml3.3/CMakeFiles/sfml3.3.dir/main.cpp.obj.requires

.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/requires

sfml3.3/CMakeFiles/sfml3.3.dir/clean:
	cd /d C:\Code\LW4\sfml3\sfml3.3 && $(CMAKE_COMMAND) -P CMakeFiles\sfml3.3.dir\cmake_clean.cmake
.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/clean

sfml3.3/CMakeFiles/sfml3.3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Code\LW4\sfml3 C:\Code\LW4\sfml3\sfml3.3 C:\Code\LW4\sfml3 C:\Code\LW4\sfml3\sfml3.3 C:\Code\LW4\sfml3\sfml3.3\CMakeFiles\sfml3.3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : sfml3.3/CMakeFiles/sfml3.3.dir/depend

