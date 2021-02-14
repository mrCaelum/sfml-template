#!/usr/bin/env python3

import os
import sys

PROJECT_NAME = 'superBonobros2'

def clear():
    return os.system('rm -rf ./build' if os.name == 'posix' else 'rd /s /q .\\build\\')

def cmake():
    return os.system('cmake -B ./build' if os.name == 'posix' else 'cmake -B .\\build')

def make():
    if os.system('make -C ./build' if os.name == 'posix' else 'msbuild .\\build\\' + PROJECT_NAME + '.sln /p:Configuration=Release') != 0:
        return 1
    if os.name == 'nt':
        if os.system('copy .\\lib\\SFML-2.5.1\\bin\\*.dll .\\build\\Release\\') != 0:
            return 1
    return os.system('cp ./assets ./build/assets -r' if os.name == 'posix' else 'xcopy /Y .\\assets .\\build\\Release\\assets\\')

def run():
    return os.system('./build/' + PROJECT_NAME if os.name == 'posix' else '.\\build\\Release\\' + PROJECT_NAME + '.exe')

def full():
    if cmake() != 0:
        return 1
    return make()

def re():
    if clear() != 0:
        return 1
    return full()

process = {
    're': re,
    'all': full,
    'full': full,
    'clear': clear,
    'cmake': cmake,
    'make': make,
    'run': run
}

def build(options):
    if not len(options):
        if full() != 0:
            print('ERROR: process failed !')
    for option in options:
        if process[option]() != 0:
            print('ERROR: process \'' + option + '\' failed !')
            return

def usage(binary_name):
    print("Usage:")
    print("\t" + binary_name + " <option>")
    print("Options:")
    print("\tcmake:\t\tbuild the project with cmake")
    print("\tmake:\t\tcompile using the UNIX makefiles. In Windows, it will open the Explorer in the build directory, where the Visual Studio project is located (.sln)")
    print("\tall:\t\tinstall the dependencies, build an compile the project in only one command")
    print("\tclear:\t\tclear the build/compilation/binary files")
    print("\tre:\t\tErase the build directory and then build & compile from scratch")
    print("\trun:\t\tLaunch the binary")

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] in ['-h','--help']:
        usage(sys.argv[0])
    elif os.name == 'posix' or os.name == 'nt':
        build(sys.argv[1:])
    else:
        print('ERROR: Invalid operating system !')