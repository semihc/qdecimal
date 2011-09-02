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
!win32:OBJECTS_DIR = obj

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
