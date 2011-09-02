#
#
#

QT -= gui
TEMPLATE = app
CONFIG  += qtestlib 

if(win32) {
 CONFIG += console
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
