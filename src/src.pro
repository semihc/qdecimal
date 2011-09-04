#
#
#

QT -= gui
TEMPLATE = lib
CONFIG += static
TARGET = qdecimal
DEPENDPATH += .
# To include decnumber headers
INCLUDEPATH += ../decnumber
DESTDIR = ../lib

if(win32) {
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
HEADERS += QDecContext.hh \
           QDecDouble.hh  \
           QDecPacked.hh  \
           QDecNumber.hh  \
           QDecSingle.hh  \
           QDecQuad.hh 

SOURCES += QDecContext.cc \
           QDecDouble.cc  \
           QDecPacked.cc  \
           QDecNumber.cc  \
           QDecSingle.cc  \
           QDecQuad.cc 
