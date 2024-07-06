# SQLite Example Project

Our goal for this is to make a simple project that has its own local copy
of the SQLite repo that is included as a git submodule, and a CMake build
system that builds that SQLite as an external project and uses it in a
basic C++ demo application. The motivation is to learn how to use SQLite in
applications that build cross-platform, where the source comes with its
own specific version of SQLite.
