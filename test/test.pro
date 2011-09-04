#
#
#

QT -= gui
TEMPLATE = app
CONFIG  += qtestlib 

if(win32) {
 CONFIG += console
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
}
else {
 MOC_DIR = moc
 OBJECTS_DIR = obj
}

TARGET = qdecimal_test
DESTDIR = ../bin
DEPENDPATH += .
INCLUDEPATH += ../decnumber ../src
LIBS += -L../lib -ldecnumber -lqdecimal

# Input
HEADERS += QDecNumberTests.hh
SOURCES += QDecNumberTests.cc Main.cc
