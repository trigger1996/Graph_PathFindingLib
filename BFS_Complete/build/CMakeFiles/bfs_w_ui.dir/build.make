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
CMAKE_SOURCE_DIR = /home/ghost/src/workspace/xmu/path_planning/BFS_Complete

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build

# Include any dependencies generated for this target.
include CMakeFiles/bfs_w_ui.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bfs_w_ui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bfs_w_ui.dir/flags.make

CMakeFiles/bfs_w_ui.dir/main.cpp.o: CMakeFiles/bfs_w_ui.dir/flags.make
CMakeFiles/bfs_w_ui.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bfs_w_ui.dir/main.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bfs_w_ui.dir/main.cpp.o -c /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/main.cpp

CMakeFiles/bfs_w_ui.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bfs_w_ui.dir/main.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/main.cpp > CMakeFiles/bfs_w_ui.dir/main.cpp.i

CMakeFiles/bfs_w_ui.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bfs_w_ui.dir/main.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/main.cpp -o CMakeFiles/bfs_w_ui.dir/main.cpp.s

CMakeFiles/bfs_w_ui.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/bfs_w_ui.dir/main.cpp.o.requires

CMakeFiles/bfs_w_ui.dir/main.cpp.o.provides: CMakeFiles/bfs_w_ui.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/bfs_w_ui.dir/build.make CMakeFiles/bfs_w_ui.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/bfs_w_ui.dir/main.cpp.o.provides

CMakeFiles/bfs_w_ui.dir/main.cpp.o.provides.build: CMakeFiles/bfs_w_ui.dir/main.cpp.o


CMakeFiles/bfs_w_ui.dir/node.cpp.o: CMakeFiles/bfs_w_ui.dir/flags.make
CMakeFiles/bfs_w_ui.dir/node.cpp.o: ../node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bfs_w_ui.dir/node.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bfs_w_ui.dir/node.cpp.o -c /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/node.cpp

CMakeFiles/bfs_w_ui.dir/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bfs_w_ui.dir/node.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/node.cpp > CMakeFiles/bfs_w_ui.dir/node.cpp.i

CMakeFiles/bfs_w_ui.dir/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bfs_w_ui.dir/node.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/node.cpp -o CMakeFiles/bfs_w_ui.dir/node.cpp.s

CMakeFiles/bfs_w_ui.dir/node.cpp.o.requires:

.PHONY : CMakeFiles/bfs_w_ui.dir/node.cpp.o.requires

CMakeFiles/bfs_w_ui.dir/node.cpp.o.provides: CMakeFiles/bfs_w_ui.dir/node.cpp.o.requires
	$(MAKE) -f CMakeFiles/bfs_w_ui.dir/build.make CMakeFiles/bfs_w_ui.dir/node.cpp.o.provides.build
.PHONY : CMakeFiles/bfs_w_ui.dir/node.cpp.o.provides

CMakeFiles/bfs_w_ui.dir/node.cpp.o.provides.build: CMakeFiles/bfs_w_ui.dir/node.cpp.o


CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o: CMakeFiles/bfs_w_ui.dir/flags.make
CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o: ../graph_simple_w_bfs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o -c /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/graph_simple_w_bfs.cpp

CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/graph_simple_w_bfs.cpp > CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.i

CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/graph_simple_w_bfs.cpp -o CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.s

CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.requires:

.PHONY : CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.requires

CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.provides: CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.requires
	$(MAKE) -f CMakeFiles/bfs_w_ui.dir/build.make CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.provides.build
.PHONY : CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.provides

CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.provides.build: CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o


# Object files for target bfs_w_ui
bfs_w_ui_OBJECTS = \
"CMakeFiles/bfs_w_ui.dir/main.cpp.o" \
"CMakeFiles/bfs_w_ui.dir/node.cpp.o" \
"CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o"

# External object files for target bfs_w_ui
bfs_w_ui_EXTERNAL_OBJECTS =

bfs_w_ui: CMakeFiles/bfs_w_ui.dir/main.cpp.o
bfs_w_ui: CMakeFiles/bfs_w_ui.dir/node.cpp.o
bfs_w_ui: CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o
bfs_w_ui: CMakeFiles/bfs_w_ui.dir/build.make
bfs_w_ui: /usr/local/lib/libopencv_videostab.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_ts.a
bfs_w_ui: /usr/local/lib/libopencv_superres.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_stitching.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_contrib.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_nonfree.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_ocl.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_gpu.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_photo.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_objdetect.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_legacy.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_video.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_ml.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_calib3d.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_features2d.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_highgui.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_imgproc.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_flann.so.2.4.13
bfs_w_ui: /usr/local/lib/libopencv_core.so.2.4.13
bfs_w_ui: CMakeFiles/bfs_w_ui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bfs_w_ui"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bfs_w_ui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bfs_w_ui.dir/build: bfs_w_ui

.PHONY : CMakeFiles/bfs_w_ui.dir/build

CMakeFiles/bfs_w_ui.dir/requires: CMakeFiles/bfs_w_ui.dir/main.cpp.o.requires
CMakeFiles/bfs_w_ui.dir/requires: CMakeFiles/bfs_w_ui.dir/node.cpp.o.requires
CMakeFiles/bfs_w_ui.dir/requires: CMakeFiles/bfs_w_ui.dir/graph_simple_w_bfs.cpp.o.requires

.PHONY : CMakeFiles/bfs_w_ui.dir/requires

CMakeFiles/bfs_w_ui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bfs_w_ui.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bfs_w_ui.dir/clean

CMakeFiles/bfs_w_ui.dir/depend:
	cd /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ghost/src/workspace/xmu/path_planning/BFS_Complete /home/ghost/src/workspace/xmu/path_planning/BFS_Complete /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build /home/ghost/src/workspace/xmu/path_planning/BFS_Complete/build/CMakeFiles/bfs_w_ui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bfs_w_ui.dir/depend

