# vim:ai:et:ff=unix:fileencoding=utf-8:sw=4:syntax=python:ts=4:

import os

env = Environment(ENV=os.environ, tools=['default', 'mb_install'])

env.MBWindowsSetAPIExport('JSON_DLL_BUILD')

env.MBAddIncludePaths([Dir('include/jsoncpp/')])

env.MBSetLibSymName('jsoncpp')
libjson = env.MBSharedLibrary(
    'jsoncpp', [
        File('src/lib_json/json_reader.cpp'),
        File('src/lib_json/json_value.cpp'),
        File('src/lib_json/json_writer.cpp')])
env.Clean(libjson, '#/obj')

# Add an explicit dependency on all the header files
#
# This is needed because some header files like json.h aren't actually
# used by the source code so they aren't picked up by the dependency
# scanner and copied into the variant directory. This is fine for
# building json-cpp, but other projects built using development-mode
# includes will fail to find those headers.
env.Depends(libjson, env.MBRecursiveFileGlob('include', '*.h'))

env.MBInstallLib(libjson, 'jsoncpp')
env.MBInstallHeaders(env.MBGlob('#/include/jsoncpp/*'), 'jsoncpp')

env.MBCreateInstallTarget()

