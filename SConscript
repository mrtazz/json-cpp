# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os
import sys

env = Environment(ENV=os.environ)

if 'win32' == sys.platform:
    env.Tool('mb_mingw', toolpath=[Dir('submodules/mw-scons-tools')])
    env.Replace(CCFLAGS=[])

env.Append(CCFLAGS='-Wall')

includes = Dir('include')
sources = Dir('#/src/lib_json/')

libjsonenv = env.Clone()
libjsonenv.Append(CPPPATH=[includes])
libjsonenv.Repository(sources)

libjsonenv.Tool('mb_install', toolpath=[Dir('submodules/mw-scons-tools')])

libjsonenv.MBSetLibSymName('json')
libjson = libjsonenv.SharedLibrary(
    'json', [
        File('src/lib_json/json_reader.cpp'),
        File('src/lib_json/json_value.cpp'),
        File('src/lib_json/json_writer.cpp'),])
Default(libjson)
libjsonenv.Clean(libjson, '#/obj')

libjsonenv.MBInstallLib(libjson, 'json')
libjsonenv.MBInstallHeaders(libjsonenv.MBGlob('#/include/json/*'), 'json')

libjsonenv.MBCreateInstallTarget()

