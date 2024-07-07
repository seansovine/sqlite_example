# SQLite Example Project

This is a simple project that has its own local copy
of the SQLite repo that is included as a git submodule, and a CMake build
system that builds that SQLite source as an external project and uses it in a
basic C++ demo application. We need to use CMake's `ExternalProject_Add` for
this because SQLite itself comes with an Autotools build system.

The motivation for this is to learn how to use SQLite in
applications that build cross-platform, where the source comes with its
own specific version of SQLite, so the project can have more self-contained
dependencies.

You can clone, build, and run it with commands:

```shell
git clone git@github.com:seansovine/sqlite_example.git
git submodule update --init --recursive
mkdir build && cd build
cmake -G "Ninja" ..
ninja
./example
```

## Example Program

We found a simple example program for using sqlite in C++
[here](https://gist.github.com/enile8/2424514),
and modified it a bit to match our personal C++ habits.
We have CMake build this program as an executable and link in the static
library built by `ExternalProject_Add`. This step is currently Linux specific as 
it's implemented in the CMake file. See the [BuildNotes](BuildNotes.md)
file for comments on making things more portable.

## To Do:

We want to have CMake generate an include file with the project root directory 
as a static variable. Then we can use that to have the example program manage 
where it puts the database file it creates and to clean up after running by 
deleting the file before exiting. (We could use a simple RAII class for this.)
