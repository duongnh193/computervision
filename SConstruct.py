#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")
env.Append(CXXFLAGS=['-fexceptions'])
# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/godot"])
sources = Glob("src/godot/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/testgde.{}.{}.framework/testgde.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/bin/testgde{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )
opencv_include = os.popen("pkg-config --cflags opencv4").read().split()
opencv_libs = os.popen("pkg-config --libs opencv4").read().split()

env.Append(CPPPATH=[p[2:] for p in opencv_include])
env.Append(LIBPATH=[opencv_libs[0][2:]])
env.Append(LIBS=[p[2:] for p in opencv_libs[1:]])

tensorflow_include = os.popen("pkg-config --cflags tensorflowlite").read().split()
tensorflow_libs = os.popen("pkg-config --libs tensorflowlite").read().split()


env.Append(CPPPATH=[p[2:] for p in tensorflow_include])
env.Append(LIBPATH=[tensorflow_libs[0][2:]])
env.Append(LIBS=[p[2:] for p in tensorflow_libs[1:]])
Default(library)
