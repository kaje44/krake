######################################################################
##  KaJe 2013                                                       ##
##                                                                  ##
##  Vytvořen: St 27.úno.2013 08:10:59                               ##
##                                                                  ##
##  Posledni upravy: Čt 14.bře.2013 08:17:48                        ##
######################################################################
TEMPLATE	= app
DESTDIR	= dist
TARGET	= tasks
CONFIG	+= qt debug
INCLUDEPATH	+= ./bibliothek
DEPENDPATH	+= ./bibliothek
win32 { 
	RC_FILE = krake.rc
	LIBS += "C:\Qt\sqlite\sqlite3.lib"
} else {
	LIBS += -lsqlite3
}
DEFINES += DBF=ODBC
# Input
RESOURCES += krake.qrc
HEADERS +=  mainform.h \
			printdlg.h \
			daydata.h \
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
			printdlg.cpp \
			daydata.cpp \
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
			ui/printdlg.ui \
			ui/inputdlg.ui \
			ui/monatform.ui 

OBJECTS_DIR	= obj
MOC_DIR	= obj
UI_DIR	= obj
QT += sql
target.path=~/dist


