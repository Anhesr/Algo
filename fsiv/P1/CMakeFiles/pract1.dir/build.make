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
CMAKE_SOURCE_DIR = /home/bixde/Escritorio/algo/P1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bixde/Escritorio/algo/P1

# Include any dependencies generated for this target.
include CMakeFiles/pract1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pract1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pract1.dir/flags.make

CMakeFiles/pract1.dir/esqueleto.cc.o: CMakeFiles/pract1.dir/flags.make
CMakeFiles/pract1.dir/esqueleto.cc.o: esqueleto.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bixde/Escritorio/algo/P1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pract1.dir/esqueleto.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pract1.dir/esqueleto.cc.o -c /home/bixde/Escritorio/algo/P1/esqueleto.cc

CMakeFiles/pract1.dir/esqueleto.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pract1.dir/esqueleto.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bixde/Escritorio/algo/P1/esqueleto.cc > CMakeFiles/pract1.dir/esqueleto.cc.i

CMakeFiles/pract1.dir/esqueleto.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pract1.dir/esqueleto.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bixde/Escritorio/algo/P1/esqueleto.cc -o CMakeFiles/pract1.dir/esqueleto.cc.s

CMakeFiles/pract1.dir/esqueleto.cc.o.requires:

.PHONY : CMakeFiles/pract1.dir/esqueleto.cc.o.requires

CMakeFiles/pract1.dir/esqueleto.cc.o.provides: CMakeFiles/pract1.dir/esqueleto.cc.o.requires
	$(MAKE) -f CMakeFiles/pract1.dir/build.make CMakeFiles/pract1.dir/esqueleto.cc.o.provides.build
.PHONY : CMakeFiles/pract1.dir/esqueleto.cc.o.provides

CMakeFiles/pract1.dir/esqueleto.cc.o.provides.build: CMakeFiles/pract1.dir/esqueleto.cc.o


# Object files for target pract1
pract1_OBJECTS = \
"CMakeFiles/pract1.dir/esqueleto.cc.o"

# External object files for target pract1
pract1_EXTERNAL_OBJECTS =

pract1: CMakeFiles/pract1.dir/esqueleto.cc.o
pract1: CMakeFiles/pract1.dir/build.make
pract1: /usr/local/lib/libopencv_dnn.so.4.2.0
pract1: /usr/local/lib/libopencv_gapi.so.4.2.0
pract1: /usr/local/lib/libopencv_highgui.so.4.2.0
pract1: /usr/local/lib/libopencv_ml.so.4.2.0
pract1: /usr/local/lib/libopencv_objdetect.so.4.2.0
pract1: /usr/local/lib/libopencv_photo.so.4.2.0
pract1: /usr/local/lib/libopencv_stitching.so.4.2.0
pract1: /usr/local/lib/libopencv_video.so.4.2.0
pract1: /usr/local/lib/libopencv_videoio.so.4.2.0
pract1: /usr/local/lib/libopencv_imgcodecs.so.4.2.0
pract1: /usr/local/lib/libopencv_calib3d.so.4.2.0
pract1: /usr/local/lib/libopencv_features2d.so.4.2.0
pract1: /usr/local/lib/libopencv_flann.so.4.2.0
pract1: /usr/local/lib/libopencv_imgproc.so.4.2.0
pract1: /usr/local/lib/libopencv_core.so.4.2.0
pract1: CMakeFiles/pract1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bixde/Escritorio/algo/P1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pract1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pract1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pract1.dir/build: pract1

.PHONY : CMakeFiles/pract1.dir/build

CMakeFiles/pract1.dir/requires: CMakeFiles/pract1.dir/esqueleto.cc.o.requires

.PHONY : CMakeFiles/pract1.dir/requires

CMakeFiles/pract1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pract1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pract1.dir/clean

CMakeFiles/pract1.dir/depend:
	cd /home/bixde/Escritorio/algo/P1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bixde/Escritorio/algo/P1 /home/bixde/Escritorio/algo/P1 /home/bixde/Escritorio/algo/P1 /home/bixde/Escritorio/algo/P1 /home/bixde/Escritorio/algo/P1/CMakeFiles/pract1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pract1.dir/depend

