cmake_minimum_required(VERSION 3.21)

# Set required C++ version.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SQLiteExample
        VERSION 0.1.0
        DESCRIPTION "A simple SQLite example project."
        LANGUAGES CXX)

# Add external project command to run autotools build for sqlite.

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sqlite-build)

include(ExternalProject)
find_program(MAKE_EXECUTABLE NAMES make REQUIRED)

ExternalProject_Add(sqlite
		SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/sqlite
		BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/sqlite-build
		CONFIGURE_COMMAND <SOURCE_DIR>/configure
		BUILD_COMMAND ${MAKE_EXECUTABLE}
		INSTALL_COMMAND ${MAKE_EXECUTABLE} DESDIR=<BINARY_DIR> prefix=<BINARY_DIR> TCLLIBDIR=<BINARY_DIR>/usr/share/tcltk/tcl8.6/sqlite3 install
		TEST_COMMAND cmake -E echo "Skipping test step."
		# "Need to specify main libraries that are built so ninja knows to look for them."
		# Not sure if this is necessary or not.
		BUILD_BYPRODUCTS <BINARY_DIR>/lib/libsqlite3.a <BINARY_DIR>/lib/libsqlite3.so
)

include_directories(src sqlite-build)

# Now write a simple test program to use our sqlite library,
# and find all the correct CMake config for includes and linking.

add_executable(example src/example.cpp)
target_link_libraries(example PRIVATE ${CMAKE_CURRENT_LIST_DIR}/sqlite-build/lib/libsqlite3.a)
