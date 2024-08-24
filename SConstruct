#!/usr/bin/env python
import os
import sys

try:
    Import("env")
except Exception:
    env = SConscript("godot-cpp/SConstruct")
    env["rootpath"]="."
    env["buildpath"] = ""

rootpath = env["rootpath"]
buildpath = env["buildpath"]

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=[rootpath+"/src/"])
env.Append(CCFLAGS=["-I"+rootpath+"/inc","-I"+rootpath+"lib/inc"])

sources = Glob("src/*.cpp")


if env["platform"] != "linux":
    print("ERROR : This project only supports linux, yet.")
else:
    env.Append(LIBPATH=[rootpath+"lib/bin/linux"])
    env.Append(LIBS=['librnnoise'])
    library = env.SharedLibrary(
        "addons/Godot-rnnoise/libgodotrnnoise{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

    if(buildpath != ""):
        os.system("cp addons/Godot-rnnoise " + buildpath + "/ -r")

Default(library)
