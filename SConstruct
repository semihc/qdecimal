#!python
# -*-python-*-
import os
import sys

# Get the mode flag from command line
# Default is the release
mode = ARGUMENTS.get('mode','debug')

allowed_modes = ['debug', 'release']
if not (mode in allowed_modes):
    print "Error: Expected %s, found %s: " % (allowed_modes, mode)
    Exit(1)

print "Will build for %s mode..." % mode

use_plat = ARGUMENTS.get('use_plat',0)

bld_root  = 'build'
platform  = sys.platform
if use_plat:
    print "Using platform '%s' in build output..." % platform
    bld_plat  = '%s/%s' % (bld_root, platform)
else:
    bld_plat = bld_root
bld_dir   = '%s/%s' % (bld_plat, mode[:3])

dump = ARGUMENTS.get('dump',0)

AddOption('--prefix',
          dest='prefix',
          type='string',
          default=bld_root,
          nargs=1,
          action='store',
          metavar='DIR',
          help='installation prefix')

env = Environment(
    PREFIX = GetOption('prefix'),
    MSVC_VERSION='11.0', # MSVC 2012
    TARGET_ARCH='x86'    # 32 bit
)

env.Decider('timestamp-newer')
env.SetOption('implicit_cache', 1)


env.AppendUnique(
    PRJ_BLD_ROOT = Dir(bld_root),
    PRJ_BLD      = Dir(bld_dir),
    PRJ_BLD_BIN  = Dir('%s/bin' % bld_dir),
    PRJ_BLD_LIB  = Dir('%s/lib' % bld_dir),
    PRJ_EXES     = {},
    PRJ_LIBS     = {}
)

env.AppendUnique(
    PRJ_INST_ROOT = Dir(env['PREFIX']),
    PRJ_INST_BIN  = Dir('%s/bin' % env['PREFIX']),
    PRJ_INST_LIB  = Dir('%s/lib' % env['PREFIX'])
)




def detectLatestQtDir():
    return "Q:/Qt/5.5.1"

# Detect Qt version
qtdir = detectLatestQtDir()

# Create base environment
#baseEnv = Environment(MSVC_VERSION='11.0', TARGET_ARCH='x86')
#...further customization of base env

# Clone Qt environment
qtEnv = env.Clone()
# Set QT5DIR
qtEnv['QT5DIR'] = qtdir
# Add qt5 tool
qtEnv.Tool('qt5')
#...further customization of qt env


# Your other stuff...
# ...including the call to your SConscripts
qtEnv.AppendUnique(CPPPATH = ['#', '.'])
qtEnv.AppendUnique(CCFLAGS = [ '-MT', '-EHsc', '-Zc:wchar_t', '-Zc:forScope' ])
qtEnv.AppendUnique(CPPDEFINES = ['UNICODE', 'WIN32', '_CRT_SECURE_NO_WARNINGS'])
#qtEnv.AppendUnique(LINKFLAGS = ['-verbose:lib', '-machine:X86'])

#qtEnv['CCFLAGS'].remove('/nologo')
#qtEnv['LINKFLAGS'].remove('/nologo')
#qtEnv['ARFLAGS'].remove('/nologo')


# Normally in SConscript files
qtEnv.EnableQt5Modules([
    'QtCore',
    'QtTest'
])
# Add your CCFLAGS and CPPPATHs to env here...


src_dirs = Split('decnumber src test')

for sd in src_dirs:
    qtEnv.SConscript(
        '%s/SConscript' % sd,
        variant_dir='%s/%s' % (bld_dir, sd),
        duplicate=0,
        exports='qtEnv'
    )


qtEnv.Alias('install', qtEnv['PREFIX'])
    

for lib in qtEnv['PRJ_LIBS'].values():
    qtEnv.Install("$PRJ_INST_LIB", lib)

for exe in qtEnv['PRJ_EXES'].values():
    qtEnv.Install("$PRJ_INST_BIN", exe)    

# Create a "test" target for all the unit tests 
for exe in qtEnv['PRJ_EXES'].values():
    ta = qtEnv.Alias('test', exe, exe[0].abspath)
    qtEnv.AlwaysBuild(ta)

    
    
Help("""
Type: 'scons' to build everything,
      'scons mode=<mode>' where mode can be debug or release.
      'scons dump=1' to dump construction environment values.
""")

if dump:
    print env.Dump()

