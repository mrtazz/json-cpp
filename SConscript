# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os
import sys

env = Environment(ENV=os.environ)

if 'win32' == sys.platform:
    env.Tool('mingw')
    env.Replace(CCFLAGS=[])

env.Append(CCFLAGS='-Wall')

includes = Dir('#/include')
sources = Dir('#/src/lib_json/')

libjsonenv = env.Clone()
libjsonenv.Append(CPPPATH=[includes])
libjsonenv.Repository(sources)
libjson = libjsonenv.SharedLibrary(
    'json', [
        File('src/lib_json/json_reader.cpp'),
        File('src/lib_json/json_value.cpp'),
        File('src/lib_json/json_writer.cpp'),])

install_prefix = ARGUMENTS.get('install_prefix', '')

if sys.platform == "linux2":
    if install_prefix == '': install_prefix = '/usr'
    lib_dir = install_prefix + "/lib"
    include_dir = install_prefix + "/include"
elif sys.platform == "darwin":
    framework_dir = install_prefix + '/Library/Frameworks/MakerBot.framework'
    lib_dir = framework_dir + "/Libraries"
    include_dir = framework_dir + "/Includes"
elif sys.platform == "win32":
    if install_prefix == '':
        if os.path.exists('c:/Program Files (x86)'):
            install_prefix = 'c:/Program Files (x86)/'
        else:
            install_prefix = 'c:/Program Files/MakerBot'
        install_prefix += '/SDK'

    lib_dir = install_prefix + "/mingw/lib"
    include_dir = install_prefix + "/mingw/include"


install_list = map(lambda x: env.Install(json_lib, x), libjson)
install_list += map(lambda x: env.Install(json_include, x), [str(includes) + '/json'])
env.Alias('install', install_list)

