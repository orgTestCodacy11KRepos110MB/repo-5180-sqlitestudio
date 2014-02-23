#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T16:14:12
#
#-------------------------------------------------

include($$PWD/../SQLiteStudio3/plugins.pri)
include($$PWD/../SQLiteStudio3/utils.pri)

QT       -= gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = SqlFormatterSimple
TEMPLATE = lib

DEFINES += SQLFORMATTERSIMPLE_LIBRARY

SOURCES += sqlformattersimpleplugin.cpp

HEADERS += sqlformattersimpleplugin.h\
        sqlformattersimple_global.h

FORMS += \
    SqlFormatterSimple.ui

copy_file(SqlFormatterSimple.ui, $$DESTDIR/SqlFormatterSimple.ui)
