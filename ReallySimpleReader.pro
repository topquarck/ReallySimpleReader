# -------------------------------------------------
# Project created by QtCreator 2009-05-31T03:49:00
# -------------------------------------------------
QT += network \
    sql \
    webkit \
    xml \
    testlib
TARGET = ReallySimpleReader
CONFIG += qtestlib
TEMPLATE = app
SOURCES += rsrmainwindow.cpp \
    item.cpp \
    channel.cpp \
    reallysimplereader.cpp \
    dbmanager.cpp \
    httpdownloader.cpp \
    xmlparser.cpp \
    HttpDownloaderTest.cpp \
    HttpXMLTest.cpp \
    dbconnector.cpp \
    dbconnectortest.cpp
HEADERS += rsrmainwindow.h \
    item.h \
    channel.h \
    reallysimplereader.h \
    dbmanager.h \
    httpdownloader.h \
    xmlparser.h \
    HttpDownloaderTest.h \
    HttpXMLTest.h \
    dbconnector.h \
    dbconnectortest.h
FORMS += rsrmainwindow.ui
OTHER_FILES += README.txt
