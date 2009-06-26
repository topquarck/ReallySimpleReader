# -------------------------------------------------
# Project created by QtCreator 2009-05-31T03:49:00
# -------------------------------------------------
QT += network \
    sql \
    webkit \
    xml
TARGET = ReallySimpleReader

# CONFIG += qtestlib
TEMPLATE = app
SOURCES += rsrmainwindow.cpp \
    item.cpp \
    channel.cpp \
    reallysimplereader.cpp \
    dbmanager.cpp \
    httpdownloader.cpp \
    xmlparser.cpp \
    dbconnector.cpp \
    main.cpp \
    feedmodel.cpp \
    feedstore.cpp \
    channellistmodel.cpp
HEADERS += rsrmainwindow.h \
    item.h \
    channel.h \
    reallysimplereader.h \
    dbmanager.h \
    httpdownloader.h \
    xmlparser.h \
    dbconnector.h \
    feedmodel.h \
    feedstore.h \
    channellistmodel.h
FORMS += rsrmainwindow.ui
OTHER_FILES += README.txt
