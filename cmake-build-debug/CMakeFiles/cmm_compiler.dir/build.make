# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Luck\Desktop\GItHub\cmm-compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cmm_compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmm_compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmm_compiler.dir/flags.make

CMakeFiles/cmm_compiler.dir/lexico.c.obj: CMakeFiles/cmm_compiler.dir/flags.make
CMakeFiles/cmm_compiler.dir/lexico.c.obj: ../lexico.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmm_compiler.dir/lexico.c.obj"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cmm_compiler.dir\lexico.c.obj   -c C:\Users\Luck\Desktop\GItHub\cmm-compiler\lexico.c

CMakeFiles/cmm_compiler.dir/lexico.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cmm_compiler.dir/lexico.c.i"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Luck\Desktop\GItHub\cmm-compiler\lexico.c > CMakeFiles\cmm_compiler.dir\lexico.c.i

CMakeFiles/cmm_compiler.dir/lexico.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cmm_compiler.dir/lexico.c.s"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Luck\Desktop\GItHub\cmm-compiler\lexico.c -o CMakeFiles\cmm_compiler.dir\lexico.c.s

CMakeFiles/cmm_compiler.dir/lexico.c.obj.requires:

.PHONY : CMakeFiles/cmm_compiler.dir/lexico.c.obj.requires

CMakeFiles/cmm_compiler.dir/lexico.c.obj.provides: CMakeFiles/cmm_compiler.dir/lexico.c.obj.requires
	$(MAKE) -f CMakeFiles\cmm_compiler.dir\build.make CMakeFiles/cmm_compiler.dir/lexico.c.obj.provides.build
.PHONY : CMakeFiles/cmm_compiler.dir/lexico.c.obj.provides

CMakeFiles/cmm_compiler.dir/lexico.c.obj.provides.build: CMakeFiles/cmm_compiler.dir/lexico.c.obj


CMakeFiles/cmm_compiler.dir/main.c.obj: CMakeFiles/cmm_compiler.dir/flags.make
CMakeFiles/cmm_compiler.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cmm_compiler.dir/main.c.obj"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cmm_compiler.dir\main.c.obj   -c C:\Users\Luck\Desktop\GItHub\cmm-compiler\main.c

CMakeFiles/cmm_compiler.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cmm_compiler.dir/main.c.i"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Luck\Desktop\GItHub\cmm-compiler\main.c > CMakeFiles\cmm_compiler.dir\main.c.i

CMakeFiles/cmm_compiler.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cmm_compiler.dir/main.c.s"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Luck\Desktop\GItHub\cmm-compiler\main.c -o CMakeFiles\cmm_compiler.dir\main.c.s

CMakeFiles/cmm_compiler.dir/main.c.obj.requires:

.PHONY : CMakeFiles/cmm_compiler.dir/main.c.obj.requires

CMakeFiles/cmm_compiler.dir/main.c.obj.provides: CMakeFiles/cmm_compiler.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\cmm_compiler.dir\build.make CMakeFiles/cmm_compiler.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/cmm_compiler.dir/main.c.obj.provides

CMakeFiles/cmm_compiler.dir/main.c.obj.provides.build: CMakeFiles/cmm_compiler.dir/main.c.obj


CMakeFiles/cmm_compiler.dir/sintatico.c.obj: CMakeFiles/cmm_compiler.dir/flags.make
CMakeFiles/cmm_compiler.dir/sintatico.c.obj: ../sintatico.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cmm_compiler.dir/sintatico.c.obj"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\cmm_compiler.dir\sintatico.c.obj   -c C:\Users\Luck\Desktop\GItHub\cmm-compiler\sintatico.c

CMakeFiles/cmm_compiler.dir/sintatico.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cmm_compiler.dir/sintatico.c.i"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Luck\Desktop\GItHub\cmm-compiler\sintatico.c > CMakeFiles\cmm_compiler.dir\sintatico.c.i

CMakeFiles/cmm_compiler.dir/sintatico.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cmm_compiler.dir/sintatico.c.s"
	C:\PROGRA~2\CODEBL~1\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Luck\Desktop\GItHub\cmm-compiler\sintatico.c -o CMakeFiles\cmm_compiler.dir\sintatico.c.s

CMakeFiles/cmm_compiler.dir/sintatico.c.obj.requires:

.PHONY : CMakeFiles/cmm_compiler.dir/sintatico.c.obj.requires

CMakeFiles/cmm_compiler.dir/sintatico.c.obj.provides: CMakeFiles/cmm_compiler.dir/sintatico.c.obj.requires
	$(MAKE) -f CMakeFiles\cmm_compiler.dir\build.make CMakeFiles/cmm_compiler.dir/sintatico.c.obj.provides.build
.PHONY : CMakeFiles/cmm_compiler.dir/sintatico.c.obj.provides

CMakeFiles/cmm_compiler.dir/sintatico.c.obj.provides.build: CMakeFiles/cmm_compiler.dir/sintatico.c.obj


# Object files for target cmm_compiler
cmm_compiler_OBJECTS = \
"CMakeFiles/cmm_compiler.dir/lexico.c.obj" \
"CMakeFiles/cmm_compiler.dir/main.c.obj" \
"CMakeFiles/cmm_compiler.dir/sintatico.c.obj"

# External object files for target cmm_compiler
cmm_compiler_EXTERNAL_OBJECTS =

cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/lexico.c.obj
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/main.c.obj
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/sintatico.c.obj
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/build.make
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/linklibs.rsp
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/objects1.rsp
cmm_compiler.exe: CMakeFiles/cmm_compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable cmm_compiler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cmm_compiler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmm_compiler.dir/build: cmm_compiler.exe

.PHONY : CMakeFiles/cmm_compiler.dir/build

CMakeFiles/cmm_compiler.dir/requires: CMakeFiles/cmm_compiler.dir/lexico.c.obj.requires
CMakeFiles/cmm_compiler.dir/requires: CMakeFiles/cmm_compiler.dir/main.c.obj.requires
CMakeFiles/cmm_compiler.dir/requires: CMakeFiles/cmm_compiler.dir/sintatico.c.obj.requires

.PHONY : CMakeFiles/cmm_compiler.dir/requires

CMakeFiles/cmm_compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cmm_compiler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cmm_compiler.dir/clean

CMakeFiles/cmm_compiler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Luck\Desktop\GItHub\cmm-compiler C:\Users\Luck\Desktop\GItHub\cmm-compiler C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug C:\Users\Luck\Desktop\GItHub\cmm-compiler\cmake-build-debug\CMakeFiles\cmm_compiler.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmm_compiler.dir/depend

