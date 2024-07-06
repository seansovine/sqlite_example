cmake_minimum_required(VERSION 3.21)

# Set required C++ version.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SQLiteExample
        VERSION 0.1.0
        DESCRIPTION "A simple SQLite example project."
        LANGUAGES CXX)

# Add external project command here to run autotools build for sqlite.
#  - Should make a build directory first it's not present.
#  - Could check to see if the submodule has been initialized, but if not config will fails.
