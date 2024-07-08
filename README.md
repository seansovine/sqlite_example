# SQLite Example Project

This simple project has its own local copy
of the SQLite source as a git submodule, and a CMake build
system that builds that source as an external project. It has a simple C++
demo program that uses the local SQLite library. We use CMake's `ExternalProject_Add`
because SQLite has an Autotools build system.

The motivation for this is to learn how to use SQLite in
applications that build cross-platform, where the source comes with its
own specific version of SQLite, so the project can have more self-contained
dependencies. That being said, so far we've only implemented support
for building on some versions of Linux.

You can clone the repo, build the project, and run the example with commands:

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
We have CMake build this program as an executable and link in the static SQLite
library built by `ExternalProject_Add`. This step is Linux specific as
it's currently implemented in the CMake file. See the [BuildNotes](BuildNotes.md)
file for comments on making things more portable.

## To Do:

We want to have CMake generate an include file with the project root directory
as a static variable. Then we can use that to have the example program manage
where it puts the database file it creates and clean up after running by
deleting the file before exiting. (We could use a simple RAII class for this.)

We plan to use this in another project that has a libary to parse the CLZ Books
collection data XML file and load its records into a SQL database, to provide an
API for querying the collection data in other applications.
