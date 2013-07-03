# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os

env = Environment(ENV=os.environ, tools=['default', 'mb_install'], toolpath=[Dir('submodules/mw-scons-tools')])

env.Append(CCFLAGS='-Wall')

env.MBAddIncludePaths([Dir('#include/jsoncpp/')])

env.MBSetLibSymName('jsoncpp')
libjson = env.MBSharedLibrary(
    'jsoncpp', [
        File('src/lib_json/json_reader.cpp'),
        File('src/lib_json/json_value.cpp'),
        File('src/lib_json/json_writer.cpp')])
Default(libjson)
env.Clean(libjson, '#/obj')

env.MBInstallLib(libjson, 'jsoncpp')
env.MBInstallHeaders(env.MBGlob('#/include/jsoncpp/*'), 'jsoncpp')

env.MBCreateInstallTarget()

