/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 08:17:07                               **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 08:17:16                        **
**********************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include "kjmainwindow.h"
	
#include "obj/ui_mainform.h"
	
	
class MainForm : public KjMainWindow, private Ui_MainWindow {
	Q_OBJECT

public:
	MainForm();
	~MainForm();
	void setColor();
	
};
	
#endif
	
