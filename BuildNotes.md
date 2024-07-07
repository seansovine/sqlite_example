# Notes on Build System

We build SQLite using CMakes `ExternalProject_Add` command. We
followed some of the advice [here](https://www.tutorialspoint.com/change-the-install-directory-with-make-install)
to help get the install directory locations straightened out.

We had to set the Make variable `TCLLIBDIR` to tell make where to put the
TCL plugin it builds. Without this, at the end of the build process we
get an error when this command runs:

```shell
usr/bin/install -c -d /usr/share/tcltk/tcl8.6/sqlite3
```

This seems to run because the Makefile builds and installs a TCL plugin
for SQLite.
To fix the error, we are telling Make to put the TCL plugin library it
builds inside the
SQLite build directory. The way we've done this
is more of a hack to silence the error and
may not even port to a different Linux distribution (much less Windows).
So a better solution would be to look into the Makefile that
their autotools script generates and try to see if building the plugin
can be disabled by setting a certain variable.

If disabling the plugin by a Makefile variable is not possible,
we add that ourselves and submit it as a pull request
to the SQLite project.

The `BUILD_BYPRODUCTS` argument to `ExternalProject_Add` is specific to
Linux as we have it. The best way to handle this if we were to also support
building on Windows is probably to make a variable for the library paths
and set it dependent on the operating system the build is running on.

__Cross-platform Build:__

We've made a couple comments above on building cross-platform, and there is
probably more to think about toward making the build work on Windows or Mac.
The build procedure for SQLite itself may be substantially different on Windows
than it is on Linux. For now we will aim for building on different Linux 
distributions.
