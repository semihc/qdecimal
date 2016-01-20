#!python
# -*-python-*-
import os
import sys
import SConsLib



# Construct variables object by merging command-line settings and
# configuration file.
vars = SConsLib.constructVariables('SConsCfg.py')

# Instantiate Scons environment
env = Environment(
    variables = vars,
    MSVC_VERSION='11.0', # VMSVC 2012 choose any version you prefer
    TARGET_ARCH='x86',   # x86 -> 32bit or x86_64 => 64bit
    PREFIX = GetOption('prefix')
)

# Check for unrecognized variables and warn
SConsLib.checkUnknownVariables(vars)

# Setup Scons environment to be used during build
SConsLib.setupEnvironment(env)

# Further refinements to the environment
Help(vars.GenerateHelpText(env))
env.Decider('timestamp-newer')
env.SetOption('implicit_cache', 1)

# Identify Qt location
if sys.platform.startswith('win'):
    qtdir = SConsLib.findQtDir('Q:/Qt/5.5.1')
elif sys.platform.startswith('linux'):
    qtdir = SConsLib.findQtDir('/home/semih/Qt/5.5.1')

# Set QT5DIR
env['QT5DIR'] = qtdir
env['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
# Add qt5 tool
env.Tool('qt5')
# Normally in SConscript files
env.EnableQt5Modules([
    'QtCore',
    'QtTest'
]) 
#...further customization of Qt env
if sys.platform == 'win32':
    if 'cl' in env['CC']:
        env.AppendUnique(CPPPATH = ['#', '.'])
        env.AppendUnique(CCFLAGS = [ '-EHsc', '-Zc:wchar_t', '-Zc:forScope' ])
        env.AppendUnique(CPPDEFINES = ['UNICODE', 'WIN32', '_CRT_SECURE_NO_WARNINGS'])
elif 'linux' in sys.platform:
    pass


# Source directories that we expect to find SConscript files:
src_dirs = Split('decnumber src test')

# Read and process SConscript files
SConsLib.readSConscriptFiles(env, src_dirs)

# Use progress indicator to get feedback from SCons
SConsLib.useProgress()

