#############################################################################
# Makefile for building: ReallySimpleReader
# Generated by qmake (2.01a) (Qt 4.5.0) on: Fri Jun 5 19:49:38 2009
# Project:  ReallySimpleReader.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/lib/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ReallySimpleReader.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT_LIB -DQT_TESTLIB_LIB -DQT_SQL_LIB -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/lib/qt4/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtNetwork -I/usr/include/QtGui -I/usr/include/QtXml -I/usr/include/QtSql -I/usr/include/QtTest -I/usr/include/QtWebKit -I/usr/include -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)   -lQtWebKit -lQtTest -lQtSql -lQtXml -lQtGui -lQtNetwork -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = rsrmainwindow.cpp \
		item.cpp \
		channel.cpp \
		reallysimplereader.cpp \
		dbmanager.cpp \
		httpdownloader.cpp \
		xmlparser.cpp \
		HttpDownloaderTest.cpp \
		HttpXMLTest.cpp \
		dbconnector.cpp \
		dbconnectortest.cpp moc_rsrmainwindow.cpp \
		moc_reallysimplereader.cpp \
		moc_dbmanager.cpp \
		moc_httpdownloader.cpp \
		moc_xmlparser.cpp \
		moc_HttpDownloaderTest.cpp \
		moc_HttpXMLTest.cpp \
		moc_dbconnector.cpp
OBJECTS       = rsrmainwindow.o \
		item.o \
		channel.o \
		reallysimplereader.o \
		dbmanager.o \
		httpdownloader.o \
		xmlparser.o \
		HttpDownloaderTest.o \
		HttpXMLTest.o \
		dbconnector.o \
		dbconnectortest.o \
		moc_rsrmainwindow.o \
		moc_reallysimplereader.o \
		moc_dbmanager.o \
		moc_httpdownloader.o \
		moc_xmlparser.o \
		moc_HttpDownloaderTest.o \
		moc_HttpXMLTest.o \
		moc_dbconnector.o
DIST          = /usr/lib/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/debug.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/qtestlib.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf \
		ReallySimpleReader.pro
QMAKE_TARGET  = ReallySimpleReader
DESTDIR       = 
TARGET        = ReallySimpleReader

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_rsrmainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ReallySimpleReader.pro  /usr/lib/qt4/mkspecs/linux-g++/qmake.conf /usr/lib/qt4/mkspecs/common/g++-multilib.conf \
		/usr/lib/qt4/mkspecs/common/unix.conf \
		/usr/lib/qt4/mkspecs/common/linux.conf \
		/usr/lib/qt4/mkspecs/qconfig.pri \
		/usr/lib/qt4/mkspecs/features/qt_functions.prf \
		/usr/lib/qt4/mkspecs/features/qt_config.prf \
		/usr/lib/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/lib/qt4/mkspecs/features/default_pre.prf \
		/usr/lib/qt4/mkspecs/features/debug.prf \
		/usr/lib/qt4/mkspecs/features/default_post.prf \
		/usr/lib/qt4/mkspecs/features/qtestlib.prf \
		/usr/lib/qt4/mkspecs/features/warn_on.prf \
		/usr/lib/qt4/mkspecs/features/qt.prf \
		/usr/lib/qt4/mkspecs/features/unix/thread.prf \
		/usr/lib/qt4/mkspecs/features/moc.prf \
		/usr/lib/qt4/mkspecs/features/resources.prf \
		/usr/lib/qt4/mkspecs/features/uic.prf \
		/usr/lib/qt4/mkspecs/features/yacc.prf \
		/usr/lib/qt4/mkspecs/features/lex.prf
	$(QMAKE) -spec /usr/lib/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ReallySimpleReader.pro
/usr/lib/qt4/mkspecs/common/g++-multilib.conf:
/usr/lib/qt4/mkspecs/common/unix.conf:
/usr/lib/qt4/mkspecs/common/linux.conf:
/usr/lib/qt4/mkspecs/qconfig.pri:
/usr/lib/qt4/mkspecs/features/qt_functions.prf:
/usr/lib/qt4/mkspecs/features/qt_config.prf:
/usr/lib/qt4/mkspecs/features/exclusive_builds.prf:
/usr/lib/qt4/mkspecs/features/default_pre.prf:
/usr/lib/qt4/mkspecs/features/debug.prf:
/usr/lib/qt4/mkspecs/features/default_post.prf:
/usr/lib/qt4/mkspecs/features/qtestlib.prf:
/usr/lib/qt4/mkspecs/features/warn_on.prf:
/usr/lib/qt4/mkspecs/features/qt.prf:
/usr/lib/qt4/mkspecs/features/unix/thread.prf:
/usr/lib/qt4/mkspecs/features/moc.prf:
/usr/lib/qt4/mkspecs/features/resources.prf:
/usr/lib/qt4/mkspecs/features/uic.prf:
/usr/lib/qt4/mkspecs/features/yacc.prf:
/usr/lib/qt4/mkspecs/features/lex.prf:
qmake:  FORCE
	@$(QMAKE) -spec /usr/lib/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile ReallySimpleReader.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/ReallySimpleReader1.0.0 || $(MKDIR) .tmp/ReallySimpleReader1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/ReallySimpleReader1.0.0/ && $(COPY_FILE) --parents rsrmainwindow.h item.h channel.h reallysimplereader.h dbmanager.h httpdownloader.h xmlparser.h HttpDownloaderTest.h HttpXMLTest.h dbconnector.h dbconnectortest.h .tmp/ReallySimpleReader1.0.0/ && $(COPY_FILE) --parents rsrmainwindow.cpp item.cpp channel.cpp reallysimplereader.cpp dbmanager.cpp httpdownloader.cpp xmlparser.cpp HttpDownloaderTest.cpp HttpXMLTest.cpp dbconnector.cpp dbconnectortest.cpp .tmp/ReallySimpleReader1.0.0/ && $(COPY_FILE) --parents rsrmainwindow.ui .tmp/ReallySimpleReader1.0.0/ && (cd `dirname .tmp/ReallySimpleReader1.0.0` && $(TAR) ReallySimpleReader1.0.0.tar ReallySimpleReader1.0.0 && $(COMPRESS) ReallySimpleReader1.0.0.tar) && $(MOVE) `dirname .tmp/ReallySimpleReader1.0.0`/ReallySimpleReader1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/ReallySimpleReader1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_rsrmainwindow.cpp moc_reallysimplereader.cpp moc_dbmanager.cpp moc_httpdownloader.cpp moc_xmlparser.cpp moc_HttpDownloaderTest.cpp moc_HttpXMLTest.cpp moc_dbconnector.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_rsrmainwindow.cpp moc_reallysimplereader.cpp moc_dbmanager.cpp moc_httpdownloader.cpp moc_xmlparser.cpp moc_HttpDownloaderTest.cpp moc_HttpXMLTest.cpp moc_dbconnector.cpp
moc_rsrmainwindow.cpp: rsrmainwindow.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) rsrmainwindow.h -o moc_rsrmainwindow.cpp

moc_reallysimplereader.cpp: reallysimplereader.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) reallysimplereader.h -o moc_reallysimplereader.cpp

moc_dbmanager.cpp: dbmanager.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) dbmanager.h -o moc_dbmanager.cpp

moc_httpdownloader.cpp: httpdownloader.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) httpdownloader.h -o moc_httpdownloader.cpp

moc_xmlparser.cpp: xmlparser.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) xmlparser.h -o moc_xmlparser.cpp

moc_HttpDownloaderTest.cpp: HttpDownloaderTest.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) HttpDownloaderTest.h -o moc_HttpDownloaderTest.cpp

moc_HttpXMLTest.cpp: HttpXMLTest.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) HttpXMLTest.h -o moc_HttpXMLTest.cpp

moc_dbconnector.cpp: dbconnector.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) dbconnector.h -o moc_dbconnector.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all: dbconnectortest.moc
compiler_moc_source_clean:
	-$(DEL_FILE) dbconnectortest.moc
dbconnectortest.moc: dbconnector.h \
		dbconnectortest.cpp
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) dbconnectortest.cpp -o dbconnectortest.moc

compiler_uic_make_all: ui_rsrmainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_rsrmainwindow.h
ui_rsrmainwindow.h: rsrmainwindow.ui
	/usr/lib/qt4/bin/uic rsrmainwindow.ui -o ui_rsrmainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_moc_source_clean compiler_uic_clean 

####### Compile

rsrmainwindow.o: rsrmainwindow.cpp rsrmainwindow.h \
		ui_rsrmainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rsrmainwindow.o rsrmainwindow.cpp

item.o: item.cpp item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o item.o item.cpp

channel.o: channel.cpp channel.h \
		item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o channel.o channel.cpp

reallysimplereader.o: reallysimplereader.cpp reallysimplereader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o reallysimplereader.o reallysimplereader.cpp

dbmanager.o: dbmanager.cpp dbmanager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dbmanager.o dbmanager.cpp

httpdownloader.o: httpdownloader.cpp httpdownloader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o httpdownloader.o httpdownloader.cpp

xmlparser.o: xmlparser.cpp xmlparser.h \
		channel.h \
		item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xmlparser.o xmlparser.cpp

HttpDownloaderTest.o: HttpDownloaderTest.cpp HttpDownloaderTest.h \
		httpdownloader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HttpDownloaderTest.o HttpDownloaderTest.cpp

HttpXMLTest.o: HttpXMLTest.cpp HttpXMLTest.h \
		httpdownloader.h \
		xmlparser.h \
		channel.h \
		item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HttpXMLTest.o HttpXMLTest.cpp

dbconnector.o: dbconnector.cpp dbconnector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dbconnector.o dbconnector.cpp

dbconnectortest.o: dbconnectortest.cpp dbconnector.h \
		dbconnectortest.moc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dbconnectortest.o dbconnectortest.cpp

moc_rsrmainwindow.o: moc_rsrmainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rsrmainwindow.o moc_rsrmainwindow.cpp

moc_reallysimplereader.o: moc_reallysimplereader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_reallysimplereader.o moc_reallysimplereader.cpp

moc_dbmanager.o: moc_dbmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dbmanager.o moc_dbmanager.cpp

moc_httpdownloader.o: moc_httpdownloader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_httpdownloader.o moc_httpdownloader.cpp

moc_xmlparser.o: moc_xmlparser.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_xmlparser.o moc_xmlparser.cpp

moc_HttpDownloaderTest.o: moc_HttpDownloaderTest.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_HttpDownloaderTest.o moc_HttpDownloaderTest.cpp

moc_HttpXMLTest.o: moc_HttpXMLTest.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_HttpXMLTest.o moc_HttpXMLTest.cpp

moc_dbconnector.o: moc_dbconnector.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dbconnector.o moc_dbconnector.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
