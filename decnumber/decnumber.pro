#
#
#

QT -= gui
TEMPLATE = lib
CONFIG += static
DEPENDPATH += .
TARGET = decnumber
DESTDIR = ../lib
if(win32) {
 INCLUDEPATH += .
 # Remove Qt's defaults
 QMAKE_CXXFLAGS -= -Zc:wchar_t-
 # Add our defaults
 QMAKE_CXXFLAGS += /Zc:forScope /Zc:wchar_t
 DEFINES *= _CRT_SECURE_NO_WARNINGS
 # Are we in debug mode?
 debug {
   # Use iterator debugging
   DEFINES *= _SECURE_SCL=1
   DEFINES *= _SECURE_SCL_THROWS=1
   # Use Run-time checks for stack corruption and uninitialized var use
   QMAKE_CXXFLAGS += /RTC1
 }

} # end win32
else {
 OBJECTS_DIR = obj
}



# Input
HEADERS += decContext.h \
           decDouble.h \
           decDPD.h \
           decimal128.h \
           decimal32.h \
           decimal64.h \
           decNumber.h \
           decNumberLocal.h \
           decPacked.h \
           decQuad.h \
           decSingle.h \
           decCommon.c \
           decBasic.c \
           Port_stdint.h \
           VCpp_stdint.h

SOURCES += decBasic.c \
           decCommon.c \
           decContext.c \
           decDouble.c \
           decimal128.c \
           decimal32.c \
           decimal64.c \
           decNumber.c \
           decPacked.c \
           decQuad.c \
           decSingle.c 
