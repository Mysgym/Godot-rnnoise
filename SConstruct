#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
env.Append(CPPPATH=["-Iinc","-Ilib/inc"])
sources = Glob("src/*.cpp")


if env["platform"] != "linux":
    print("ERROR : This project only supports linux, yet.")
else:
    env.Append(LIBPATH=['lib/bin/linux']);
    env.Append(LIBS=['librnnoise']);
    #env.Append(INCLUDE=['inc']);
    library = env.SharedLibrary(
        "addons/Godot-rnnoise/libgodotrnnoise{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
