#
#
#
include(../common.pri)

QT -= gui
TEMPLATE = app
CONFIG  += qtestlib 

TARGET = qdecimal_test
DESTDIR = ../bin
DEPENDPATH += .
INCLUDEPATH += ../decnumber ../src
LIBS += -L../lib -ldecnumber -lqdecimal

# Input
HEADERS += QDecNumberTests.hh
SOURCES += QDecNumberTests.cc Main.cc
