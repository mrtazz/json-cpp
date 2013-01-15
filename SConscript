# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os
import sys

env = Environment(ENV=os.environ)

if 'win32' == sys.platform:
    env.Tool('mingw')
    env.Replace(CCFLAGS=[])
else:
    env.Append(CCFLAGS='-fPIC')

env.Tool('default')
env.Tool('mb_install', toolpath=[Dir('submodules/mw-scons-tools')])

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

env.MBInstallLib(libjson)
env.MBInstallHeaders(includes)

env.MBCreateInstallTarget()

