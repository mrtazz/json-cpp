# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os
import sys

env = Environment(ENV=os.environ)

env.Append(CCFLAGS='-Wall')

includes = Dir('#include/jsoncpp/')
sources = Dir('#/src/lib_json/')

libjsonenv = env.Clone()
libjsonenv.Append(CPPPATH=[includes])
libjsonenv.Repository(sources)

libjsonenv.Tool('mb_install', toolpath=[Dir('submodules/mw-scons-tools')])

libjsonenv.MBSetLibSymName('jsoncpp')
libjson = libjsonenv.MBSharedLibrary(
    'jsoncpp', [
        File('src/lib_json/json_reader.cpp'),
        File('src/lib_json/json_value.cpp'),
        File('src/lib_json/json_writer.cpp'),])
Default(libjson)
libjsonenv.Clean(libjson, '#/obj')

libjsonenv.MBInstallLib(libjson, 'jsoncpp')
libjsonenv.MBInstallHeaders(libjsonenv.MBGlob('#/include/jsoncpp/*'),
                            'jsoncpp')

libjsonenv.MBCreateInstallTarget()

