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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/http_server_proxy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/http_server_proxy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/http_server_proxy.dir/flags.make

CMakeFiles/http_server_proxy.dir/main.cpp.o: CMakeFiles/http_server_proxy.dir/flags.make
CMakeFiles/http_server_proxy.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/http_server_proxy.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http_server_proxy.dir/main.cpp.o -c /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/main.cpp

CMakeFiles/http_server_proxy.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http_server_proxy.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/main.cpp > CMakeFiles/http_server_proxy.dir/main.cpp.i

CMakeFiles/http_server_proxy.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http_server_proxy.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/main.cpp -o CMakeFiles/http_server_proxy.dir/main.cpp.s

# Object files for target http_server_proxy
http_server_proxy_OBJECTS = \
"CMakeFiles/http_server_proxy.dir/main.cpp.o"

# External object files for target http_server_proxy
http_server_proxy_EXTERNAL_OBJECTS =

http_server_proxy: CMakeFiles/http_server_proxy.dir/main.cpp.o
http_server_proxy: CMakeFiles/http_server_proxy.dir/build.make
http_server_proxy: /usr/local/opt/qt/lib/QtWidgets.framework/QtWidgets
http_server_proxy: /usr/local/opt/qt/lib/QtGui.framework/QtGui
http_server_proxy: /usr/local/opt/qt/lib/QtCore.framework/QtCore
http_server_proxy: CMakeFiles/http_server_proxy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable http_server_proxy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http_server_proxy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/http_server_proxy.dir/build: http_server_proxy

.PHONY : CMakeFiles/http_server_proxy.dir/build

CMakeFiles/http_server_proxy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/http_server_proxy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/http_server_proxy.dir/clean

CMakeFiles/http_server_proxy.dir/depend:
	cd /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug /Users/rodrigodmpa/CLionProjects/http_server_proxy/projeto/cmake-build-debug/CMakeFiles/http_server_proxy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/http_server_proxy.dir/depend

