# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug"

# Include any dependencies generated for this target.
include RTC_lib/CMakeFiles/RTC_lib.dir/depend.make

# Include the progress variables for this target.
include RTC_lib/CMakeFiles/RTC_lib.dir/progress.make

# Include the compile flags for this target's objects.
include RTC_lib/CMakeFiles/RTC_lib.dir/flags.make

RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.o: RTC_lib/CMakeFiles/RTC_lib.dir/flags.make
RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.o: ../RTC_lib/Tuple.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.o"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RTC_lib.dir/Tuple.cpp.o -c "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Tuple.cpp"

RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTC_lib.dir/Tuple.cpp.i"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Tuple.cpp" > CMakeFiles/RTC_lib.dir/Tuple.cpp.i

RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTC_lib.dir/Tuple.cpp.s"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Tuple.cpp" -o CMakeFiles/RTC_lib.dir/Tuple.cpp.s

RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.o: RTC_lib/CMakeFiles/RTC_lib.dir/flags.make
RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.o: ../RTC_lib/Canvas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.o"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RTC_lib.dir/Canvas.cpp.o -c "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Canvas.cpp"

RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTC_lib.dir/Canvas.cpp.i"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Canvas.cpp" > CMakeFiles/RTC_lib.dir/Canvas.cpp.i

RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTC_lib.dir/Canvas.cpp.s"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib/Canvas.cpp" -o CMakeFiles/RTC_lib.dir/Canvas.cpp.s

# Object files for target RTC_lib
RTC_lib_OBJECTS = \
"CMakeFiles/RTC_lib.dir/Tuple.cpp.o" \
"CMakeFiles/RTC_lib.dir/Canvas.cpp.o"

# External object files for target RTC_lib
RTC_lib_EXTERNAL_OBJECTS =

RTC_lib/libRTC_lib.a: RTC_lib/CMakeFiles/RTC_lib.dir/Tuple.cpp.o
RTC_lib/libRTC_lib.a: RTC_lib/CMakeFiles/RTC_lib.dir/Canvas.cpp.o
RTC_lib/libRTC_lib.a: RTC_lib/CMakeFiles/RTC_lib.dir/build.make
RTC_lib/libRTC_lib.a: RTC_lib/CMakeFiles/RTC_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libRTC_lib.a"
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && $(CMAKE_COMMAND) -P CMakeFiles/RTC_lib.dir/cmake_clean_target.cmake
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RTC_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
RTC_lib/CMakeFiles/RTC_lib.dir/build: RTC_lib/libRTC_lib.a

.PHONY : RTC_lib/CMakeFiles/RTC_lib.dir/build

RTC_lib/CMakeFiles/RTC_lib.dir/clean:
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" && $(CMAKE_COMMAND) -P CMakeFiles/RTC_lib.dir/cmake_clean.cmake
.PHONY : RTC_lib/CMakeFiles/RTC_lib.dir/clean

RTC_lib/CMakeFiles/RTC_lib.dir/depend:
	cd "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC" "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/RTC_lib" "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug" "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib" "/Users/davidp/Desktop/CODE/OSSU/Raytracer challenge/RTC/cmake-build-debug/RTC_lib/CMakeFiles/RTC_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : RTC_lib/CMakeFiles/RTC_lib.dir/depend

