######################################################################
#  KaJe 2012                                                         #
#                                                                    #
#  Vytvořen: po 31.12.2012 08:28:05                                  #
#                                                                    #
#  Posledni upravy: St 06.úno.2013 15:01:06                        **
######################################################################
TEMPLATE	= app
DESTDIR	= dist
TARGET	= kalendar
CONFIG	+= qt debug
INCLUDEPATH	+= ./bibliothek
DEPENDPATH	+= ./bibliothek

win32 { 
	RC_FILE = lochness.rc
	LIBS += "C:\Qt\sqlite\sqlite3.lib"
} else {
	LIBS += -lsqlite3
}

DEFINES += DBF=ODBC

# Input
RESOURCES += lochness.qrc

HEADERS +=  mainform.h \
			daydata.h \
			commonmodel.h \
			inputdlg.h \
			dayitem.h \
			monatform.h \
			asqlengine.h \
			daymodel.h \
			sqlengine.h \
			kjguilib.h \
			kjsqllib.h \
			kjsyslog.h \
			kjmainwindow.h \
			qprogressindicator.h

SOURCES +=  mainform.cpp \
			daydata.cpp \
			commonmodel.cpp \
			inputdlg.cpp \
			dayitem.cpp \
			monatform.cpp \
			kjguilib.cpp \
			kjsqllib.cpp \
			kjsyslog.cpp \
			kjmainwindow.cpp \
			qprogressindicator.cpp \
			asqlengine.cpp \
			daymodel.cpp \
			sqlengine.cpp \
			main.cpp

FORMS +=    ui/mainform.ui \
			ui/inputdlg.ui \
			ui/monatform.ui 

OBJECTS_DIR	= obj
MOC_DIR	= obj
UI_DIR	= obj
QT += sql
target.path=~/dist
