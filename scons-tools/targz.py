"""tarball

Tool-specific initialization for tarball.

"""

##
##to unpack on the fly...
##gunzip < FILE.tar.gz | tar xvf -
##to pack on the fly...
##tar cvf - FILE-LIST | gzip -c > FILE.tar.gz 

import os.path

import SCons.Builder
import SCons.Node.FS
import SCons.Util

try:
    import gzip
    import tarfile
    internal_targz = 1
except ImportError:
    internal_targz = 0

TARGZ_DEFAULT_COMPRESSION_LEVEL = 9

if internal_targz:
    def targz(target, source, env):
        def visit(tar, dirname, names):
            for name in names:
                path = os.path.join(dirname, name)
                if os.path.isfile(path):
                    tar.add(path)
        compression = env.get('TARGZ_COMPRESSION_LEVEL',TARGZ_DEFAULT_COMPRESSION_LEVEL)
        target_path = str(target[0])
        fileobj = gzip.GzipFile( target_path, 'wb', compression )
        tar = tarfile.TarFile(os.path.splitext(target_path)[0], 'w', fileobj)
        for s in source:
            if s.isdir():
                os.path.walk(str(s), visit, tar)
            else:
                tar.add(str(s))      # filename, arcname
        tar.close()

targzAction = SCons.Action.Action(targz, varlist=['TARGZ_COMPRESSION_LEVEL'])

TarGzBuilder = SCons.Builder.Builder(action = SCons.Action.Action('$TARGZ_COM', '$TARGZ_COMSTR'),
                                     source_factory = SCons.Node.FS.Entry,
                                     source_scanner = SCons.Defaults.DirScanner,
                                     suffix = '$TARGZ_SUFFIX',
                                     multi = 1)


def generate(env):
    """Add Builders and construction variables for zip to an Environment."""
    env['BUILDERS']['TarGz'] = TarGzBuilder
    env['TARGZ_COM'] = targzAction
    env['TARGZ_COMPRESSION_LEVEL'] = TARGZ_DEFAULT_COMPRESSION_LEVEL # range 0-9
    env['TARGZ_SUFFIX']  = '.tar.gz'

def exists(env):
    return internal_targz
