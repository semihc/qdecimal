#!python
# -*-python-*-
#
# SCons extension library for large C/C++ projects.
# Author: Semih Cemiloglu <semih.cemiloglu@gmail.com>
# Initial: 2016-01-20
# This file and all associated files have 'BSD License' copyright terms
#

# Standard modules
import os
import sys
import atexit
import subprocess
# Scons modules
import SCons
from SCons.Script import *



def getVersion():
   return SCons.__version__

def printBuildFailures():
   for bf in GetBuildFailures():
      print "%s failed: %s" % (bf.node, bf.errstr)

def findQtDir(defDir=None):
   """ Detect Qt version on the platform. """
   qtdir = os.environ.get('QT5DIR',None)
   if qtdir:
      return qtdir
   qtdir = os.environ.get('QTDIR',None)
   if qtdir:
      return qtdir
   return defDir


def constructVariables(cfgFile=None):
   """
   Construct variables from command line arguments given to scons
   ARGUMENTS and ARGLIST 
   """
   vars = Variables(cfgFile)
   vars.Add('verbose','Set to non-zero for verbose output', 0)
   vars.Add(EnumVariable('build_mode', 'Build mode', 'dbg',
                    allowed_values=('dbg', 'rel'),
                    map={'debug':'dbg', 'release':'rel'}))
   vars.Add(BoolVariable('use_plat', 'Use platform as build variant', 0))
   vars.Add(BoolVariable('run_tests', 'Run tests at the end', 0))
   vars.Add(PathVariable('build_dir',
                         'Path to build directory',
                         'sbuild',
                         PathVariable.PathIsDirCreate))
   vars.Add(BoolVariable('dump', 'Dump contents of environment', 0))

   # Add --prefix option to be able to specify installation directory
   # outside of prect directory tree.
   AddOption('--prefix',
             dest='prefix',
             type='string',
             default=None,
             nargs=1,
             action='store',
             metavar='DIR',
             help='installation prefix')

   return vars


def checkUnknownVariables(vars):
   """
   Check if vars contains unknown variables for an environment.
   """
   unknown = vars.UnknownVariables()
   if unknown:
      print "Unknown variables:", unknown.keys()
      #This should be warning only
      #Exit(1)
   return 0



def setupEnvironment(env):
   """
   Prepare a scons construction environment for building.
   """
   # Directories that build output will be generated into
   platform  = sys.platform
   bld_mode  = env['build_mode'] 
   bld_dir   = env['build_dir']
   if env['use_plat']:
      bld_pdir = '%s/%s' % (bld_dir, platform)
   else:
      bld_pdir = bld_dir
   bld_vdir = '%s/%s' % (bld_pdir, bld_mode)

   
   # Store build directories and setup build output data structures
   env.AppendUnique(
      PRJ_BLD_DIR  = Dir(bld_dir),
      PRJ_BLD_VDIR = Dir(bld_vdir),
      PRJ_BLD_BIN  = Dir('%s/bin' % bld_vdir),
      PRJ_BLD_LIB  = Dir('%s/lib' % bld_vdir),
      PRJ_EXES     = {},
      PRJ_TSTS     = {},
      PRJ_LIBS     = {},
      PRJ_OBJS     = {}
   )

   # If project install location (prefix) is specified
   if env['PREFIX']:
      # Define installation locations
      env.AppendUnique(
         PRJ_INST_DIR = Dir(env['PREFIX']),
         PRJ_INST_BIN = Dir('%s/bin' % env['PREFIX']),
         PRJ_INST_LIB = Dir('%s/lib' % env['PREFIX'])
      )
   
   # Baseline compile/link flags
   if platform == 'win32':
      if 'cl' in env['CC']:
         if env['build_mode'] == 'dbg':
            env.MergeFlags('-MTd -W1 -D_DEBUG -RTCs -Zi')
         else:
            env.MergeFlags('-MT -O1 -DNDEBUG')
         if env['verbose']:
            env.AppendUnique(CCFLAGS='-Bt')
            env.AppendUnique(LINKFLAGS=['-verbose:lib', '-time'])
      else:
         print "Unrecognized compiler: %s" % env['CC']
   elif 'linux' in platform:
      # Replace LINKCOM to position LINKFLAGS at the very end of
      # link command line
      env.Replace(LINKCOM='$LINK -o $TARGET $__RPATH $SOURCES $_LIBDIRFLAGS $_LIBFLAGS $LINKFLAGS')
      env.AppendUnique(LINKFLAGS = ['-lm' ])
      env.AppendUnique(CCFLAGS = ['-fPIC','-DPIC'])
      if env['build_mode'] == 'dbg':
        env.MergeFlags('-g')
      else:
         env.MergeFlags('-O2 -w')
      if env['verbose']:
         env.AppendUnique(CCFLAGS='-v')
   else:
      # Warning only, rely on SCons to come up with meaningful defaults
      print "Unrecognized platform: %s" % platform

      
   # Inform user about the build mode
   print "Will build for %s mode..." % bld_mode
   # Help output to be shown to users
   Help("""
Type: 'scons' to build all libraries and executables.
   """)
   # At the abnormal exit show information about build failures
   atexit.register(printBuildFailures)
   return 0


def readSConscriptFiles(env, src_dirs):
   for sd in src_dirs:
      env.SConscript(
         '%s/SConscript' % sd,
         variant_dir='%s/%s' % (env['PRJ_BLD_VDIR'],sd),
         duplicate=0,
         exports='env'
      )

   # Firstly, install project outputs to variant directories
   for lib in env['PRJ_LIBS'].values():
      env.Install("$PRJ_BLD_LIB", lib)
   for exe in env['PRJ_EXES'].values():
      env.Install("$PRJ_BLD_BIN", exe)
   for exe in env['PRJ_TSTS'].values():
      env.Install("$PRJ_BLD_BIN", exe)

   # Add a 'install' target for project output files
   # This will support calls to scons with "install" target
   # scons --prefix=/path/to/gsl install
   if env['PREFIX']:
      env.Alias('install', env['PREFIX'])
      for lib in env['PRJ_LIBS'].values():
         env.Install("$PRJ_INST_LIB", lib)
      for exe in env['PRJ_EXES'].values():
         env.Install("$PRJ_INST_BIN", exe)
      # Note that we don't install test applications
      

   if env['dump']:
      print env.Dump()

   if env['run_tests']:
      runTests(env)
   
         

def useProgress(mode=None, interval=5):
   """
   use and show progress indicator when building
   """
   if mode == 'target':
      Progress('Evaluating $TARGET\r')
   else:
      Progress(['-\r', '\\\r', '|\r', '/\r'], interval)



def runTests(env):
   for exe in env['PRJ_TSTS'].values():
      cmd = exe[0].abspath
      print "Executing: %s" % cmd
      rv = subprocess.call(cmd)
      if rv == 0:
         print "PASS: %s" % os.path.basename(cmd)
      else:
         print "FAIL: %s" % os.path.basename(cmd)       




