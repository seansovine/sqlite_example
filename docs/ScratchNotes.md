# Scratch Notes

We were having trouble building the project with the ninja CMake generator.
Which is to say using steps:

```shell
mkdir build_test && cd build_test
cmake -G "Ninja" ..
ninja
```

But then we realized the problem was that we need the option

```cmake
CONFIGURE_HANDLED_BY_BUILD true
```

in CMake's `ExternalProject_Add`. This was used
[here](https://www.scivision.dev/cmake-external-project-autotools/),
which also mentions `ninja`, but the build worked fine with just plain `make`.
