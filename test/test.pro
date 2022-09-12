#
#
#
include(../common.pri)

QT -= gui
TEMPLATE = app
QT += testlib 
QT += core5compat

TARGET = qdecimal_test
DESTDIR = ../bin
DEPENDPATH += .
INCLUDEPATH += ../decnumber ../src
LIBS += -L../lib -lqdecimal -ldecnumber

# Input
HEADERS += QDecNumberTests.hh
SOURCES += QDecNumberTests.cc Main.cc
