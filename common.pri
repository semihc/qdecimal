# Following are defaults for decnumber library.
# These defines must be defined when library clients are compiled.
# We don't recommend enabling them unless it's specifically required.
#DEFINES += DECNUMDIGITS=34  # default is 34 
#DEFINES += DECSUBSET=0      # default is 0
#DEFINES += DECEXTFLAG=1     # default is 1
#DEFINES += DECLITEND=0     # default is 1

CONFIG += debug


if(win32) {
 INCLUDEPATH += .
} # end win32
else {
 MOC_DIR = moc
 OBJECTS_DIR = obj
}

