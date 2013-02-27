/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: po 31.12.2012 08:28:05                                **
**                                                                  **
**  Posledni upravy: Po 31.pro.2012 08:45:13                        **
*********************************************************************/
#include <QtGui>
#include "mainform.h"
int main( int argc, char **argv ) {
	QApplication app( argc, argv );
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8:") );
	//QPixmap pixmap(":/img/projekt.jpg");
	//QSplashScreen splash(pixmap);
	//app.setWindowIcon(QIcon(":/img/projekt-ikon.png"));
	//splash.show();
	//splash.showMessage(QObject::tr("Startuji..."), Qt::AlignTop | Qt::AlignRight);
	MainForm mf;
//	mf.setColor();
	mf.show();
	//splash.finish(&mf);
	return app.exec();
}
