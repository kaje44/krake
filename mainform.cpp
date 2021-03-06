/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 08:16:49                               **
**                                                                  **
**  Posledni upravy: Pá 15.bře.2013 13:03:32                        **
**********************************************************************/

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
		createInfo("$build v1.0.6$", ":img/story-editor.png");
		m_rootDir = QCoreApplication::applicationDirPath()+"/";
		syslog.open(m_rootDir + "infowork.log");		
//		sqle = new SqlEngine("InfODBC","servercon","QODBC");
// pri sqlite udelat zmeny i v .pro
		sqle = new SqlEngine("infowork.db","servercon","QSQLITE");
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

void MainForm::setColor() {

}

//------------------------------------------------------------------------------------------------- 
 

