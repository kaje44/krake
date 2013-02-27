/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: po 31.12.2012 08:28:05                                **
**                                                                  **
**  Posledni upravy: St 06.úno.2013 14:45:30                        **
*********************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include "kjmainwindow.h"
	
#include "obj/ui_mainform.h"
	
	
class MainForm : public KjMainWindow, private Ui_MainWindow {
	Q_OBJECT

public:
	MainForm();
	~MainForm();
	
};
	
#endif
	
