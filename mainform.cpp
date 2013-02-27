/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: po 31.12.2012 08:28:05                                **
**                                                                  **
**  Posledni upravy: St 06.úno.2013 15:04:37                        **
*********************************************************************/

#include <QtGui>

#include "monatform.h"
#include "kjsyslog.h"
#include "sqlengine.h"
#include "kjguilib.h" 

#include "mainform.h"

SqlEngine *sqle;

MainForm::MainForm() : KjMainWindow() {
	setupUi(this);
	if ( schliesser() ) {
		createInfo("$build v1.1.7$", ":img/kalendar.jpg");
		m_rootDir = QCoreApplication::applicationDirPath()+"/";
		syslog.open(m_rootDir + "kalendar.log");		
//		sqle = new SqlEngine("KalODBC","servercon","QODBC");
// pri sqlite udelat zmeny i v .pro
		sqle = new SqlEngine("kalendar.db","servercon","QSQLITE");
		if (sqle->isOpen()) {
			MonatForm* mf = new MonatForm(this);
			mf->updateTable();
			setCentralWidget(mf);
		};//if
	} else {
		error("Chyba","Chyba spuštění");	
	};
}

//------------------------------------------------------------------------------------------------- 

MainForm::~MainForm() {
}

//------------------------------------------------------------------------------------------------- 
 
