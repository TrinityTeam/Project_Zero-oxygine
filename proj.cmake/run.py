import sys
import os
import subprocess

oxygineRoot = os.getenv('OXYGINE_ROOT')
buildDir = os.path.abspath("build")
dataDir = os.path.abspath("../data")
cmakeOptions = ""
makeOptions = ""

current = iter(sys.argv)
next(current)
try:
    arg = next(current)
    if arg == "-c" or arg == "--cmake-options":
        cmakeOptions = next(current)

    elif arg == "-m" or arg == "--make-options":
        makeOpions = next(current)

    elif arg == "-r" or arg == "--oxygine-root":
        oxygineRoot = os.path.abspath(next(current))

    elif arg == "-b" or arg == "--build-dir":
        buildDir = os.path.abspath(next(current))

    elif arg == "-d" or arg == "--data-dir":
        dataDir = os.path.abspath(next(current))

    elif arg == "-h" or arg == "--help":
        print("Options:\n-c --cmake-options\tSet CMake build options\n-m --make-options\tSet Make build options\n-r --oxygine-root\tSet Oxygine root directory\n-b --build-dir\tSet build directory\n-d --data-dir\t Set data dir\n")

except StopIteration:
    pass

if not oxygineRoot:
    print("Error: Oxygine has not been found; Please specify OXYGINE_ROOT(set environment variable or specify with -r|--oxygine-root argument) to the proper path to the Oxygine")
    exit(1)

try:
    os.mkdir(buildDir)

except FileExistsError:
    pass

os.chdir(buildDir)

result = subprocess.run(["cmake", "-DOXYGINE_ROOT="+oxygineRoot, cmakeOptions, ".."])
if result.returncode != 0:
    exit(1)

result = subprocess.run(["make"]+ list(makeOptions))
if result.returncode != 0:
    exit(1)

print("Building complete")

os.chdir(dataDir)
result = subprocess.run([buildDir+"/Project_Zero"])
if result.returncode != 0:
    exit(1)
