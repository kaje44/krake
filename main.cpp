/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 08:12:10                               **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 08:13:57                        **
**********************************************************************/

#include <QtGui>
#include "mainform.h"
int main( int argc, char **argv ) {
	QApplication app( argc, argv );
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8:") );
	MainForm mf;
	mf.setColor();
	mf.show();
	return app.exec();
}
