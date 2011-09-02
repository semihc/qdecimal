#
#
#

QT -= gui
TEMPLATE = lib
CONFIG += static
DEPENDPATH += .
TARGET = decnumber
DESTDIR = ../lib
!win32:OBJECTS_DIR = obj

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
