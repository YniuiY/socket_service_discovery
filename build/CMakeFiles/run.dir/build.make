# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yangdi/test/netwrok/socket_service_discovery

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangdi/test/netwrok/socket_service_discovery/build

# Include any dependencies generated for this target.
include CMakeFiles/run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/run.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run.dir/flags.make

CMakeFiles/run.dir/src/main.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/main.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/main.cpp
CMakeFiles/run.dir/src/main.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/main.cpp.o -MF CMakeFiles/run.dir/src/main.cpp.o.d -o CMakeFiles/run.dir/src/main.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/main.cpp

CMakeFiles/run.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/main.cpp > CMakeFiles/run.dir/src/main.cpp.i

CMakeFiles/run.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/main.cpp -o CMakeFiles/run.dir/src/main.cpp.s

CMakeFiles/run.dir/src/common/transfer.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/common/transfer.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/common/transfer.cpp
CMakeFiles/run.dir/src/common/transfer.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/run.dir/src/common/transfer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/common/transfer.cpp.o -MF CMakeFiles/run.dir/src/common/transfer.cpp.o.d -o CMakeFiles/run.dir/src/common/transfer.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/common/transfer.cpp

CMakeFiles/run.dir/src/common/transfer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/common/transfer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/common/transfer.cpp > CMakeFiles/run.dir/src/common/transfer.cpp.i

CMakeFiles/run.dir/src/common/transfer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/common/transfer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/common/transfer.cpp -o CMakeFiles/run.dir/src/common/transfer.cpp.s

CMakeFiles/run.dir/src/tcp/client.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/tcp/client.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/client.cpp
CMakeFiles/run.dir/src/tcp/client.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/run.dir/src/tcp/client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/tcp/client.cpp.o -MF CMakeFiles/run.dir/src/tcp/client.cpp.o.d -o CMakeFiles/run.dir/src/tcp/client.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/client.cpp

CMakeFiles/run.dir/src/tcp/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/tcp/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/client.cpp > CMakeFiles/run.dir/src/tcp/client.cpp.i

CMakeFiles/run.dir/src/tcp/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/tcp/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/client.cpp -o CMakeFiles/run.dir/src/tcp/client.cpp.s

CMakeFiles/run.dir/src/tcp/server.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/tcp/server.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/server.cpp
CMakeFiles/run.dir/src/tcp/server.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/run.dir/src/tcp/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/tcp/server.cpp.o -MF CMakeFiles/run.dir/src/tcp/server.cpp.o.d -o CMakeFiles/run.dir/src/tcp/server.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/server.cpp

CMakeFiles/run.dir/src/tcp/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/tcp/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/server.cpp > CMakeFiles/run.dir/src/tcp/server.cpp.i

CMakeFiles/run.dir/src/tcp/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/tcp/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/tcp/server.cpp -o CMakeFiles/run.dir/src/tcp/server.cpp.s

CMakeFiles/run.dir/src/udp/udp_client.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/udp/udp_client.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_client.cpp
CMakeFiles/run.dir/src/udp/udp_client.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/run.dir/src/udp/udp_client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/udp/udp_client.cpp.o -MF CMakeFiles/run.dir/src/udp/udp_client.cpp.o.d -o CMakeFiles/run.dir/src/udp/udp_client.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_client.cpp

CMakeFiles/run.dir/src/udp/udp_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/udp/udp_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_client.cpp > CMakeFiles/run.dir/src/udp/udp_client.cpp.i

CMakeFiles/run.dir/src/udp/udp_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/udp/udp_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_client.cpp -o CMakeFiles/run.dir/src/udp/udp_client.cpp.s

CMakeFiles/run.dir/src/udp/udp_server.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/udp/udp_server.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_server.cpp
CMakeFiles/run.dir/src/udp/udp_server.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/run.dir/src/udp/udp_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/udp/udp_server.cpp.o -MF CMakeFiles/run.dir/src/udp/udp_server.cpp.o.d -o CMakeFiles/run.dir/src/udp/udp_server.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_server.cpp

CMakeFiles/run.dir/src/udp/udp_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/udp/udp_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_server.cpp > CMakeFiles/run.dir/src/udp/udp_server.cpp.i

CMakeFiles/run.dir/src/udp/udp_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/udp/udp_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/udp/udp_server.cpp -o CMakeFiles/run.dir/src/udp/udp_server.cpp.s

CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/client.cpp
CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o -MF CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o.d -o CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/client.cpp

CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/client.cpp > CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.i

CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/client.cpp -o CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.s

CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/server.cpp
CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o -MF CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o.d -o CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/server.cpp

CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/server.cpp > CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.i

CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/unix_socket/stream/server.cpp -o CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.s

CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_discovery_master.cpp
CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o -MF CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o.d -o CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_discovery_master.cpp

CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_discovery_master.cpp > CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.i

CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_discovery_master.cpp -o CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.s

CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o: CMakeFiles/run.dir/flags.make
CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o: /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_sd.cpp
CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o: CMakeFiles/run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o -MF CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o.d -o CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o -c /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_sd.cpp

CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_sd.cpp > CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.i

CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yangdi/test/netwrok/socket_service_discovery/src/service_discovery/service_sd.cpp -o CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.s

# Object files for target run
run_OBJECTS = \
"CMakeFiles/run.dir/src/main.cpp.o" \
"CMakeFiles/run.dir/src/common/transfer.cpp.o" \
"CMakeFiles/run.dir/src/tcp/client.cpp.o" \
"CMakeFiles/run.dir/src/tcp/server.cpp.o" \
"CMakeFiles/run.dir/src/udp/udp_client.cpp.o" \
"CMakeFiles/run.dir/src/udp/udp_server.cpp.o" \
"CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o" \
"CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o" \
"CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o" \
"CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o"

# External object files for target run
run_EXTERNAL_OBJECTS =

bin/run: CMakeFiles/run.dir/src/main.cpp.o
bin/run: CMakeFiles/run.dir/src/common/transfer.cpp.o
bin/run: CMakeFiles/run.dir/src/tcp/client.cpp.o
bin/run: CMakeFiles/run.dir/src/tcp/server.cpp.o
bin/run: CMakeFiles/run.dir/src/udp/udp_client.cpp.o
bin/run: CMakeFiles/run.dir/src/udp/udp_server.cpp.o
bin/run: CMakeFiles/run.dir/src/unix_socket/stream/client.cpp.o
bin/run: CMakeFiles/run.dir/src/unix_socket/stream/server.cpp.o
bin/run: CMakeFiles/run.dir/src/service_discovery/service_discovery_master.cpp.o
bin/run: CMakeFiles/run.dir/src/service_discovery/service_sd.cpp.o
bin/run: CMakeFiles/run.dir/build.make
bin/run: CMakeFiles/run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable bin/run"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run.dir/build: bin/run
.PHONY : CMakeFiles/run.dir/build

CMakeFiles/run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run.dir/clean

CMakeFiles/run.dir/depend:
	cd /home/yangdi/test/netwrok/socket_service_discovery/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangdi/test/netwrok/socket_service_discovery /home/yangdi/test/netwrok/socket_service_discovery /home/yangdi/test/netwrok/socket_service_discovery/build /home/yangdi/test/netwrok/socket_service_discovery/build /home/yangdi/test/netwrok/socket_service_discovery/build/CMakeFiles/run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run.dir/depend
