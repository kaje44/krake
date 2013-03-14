/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: čt 14.03.2013 08:16:58                                **
**                                                                  **
**  Posledni upravy: Čt 14.bře.2013 08:31:04                        **
*********************************************************************/

#include <QDialog>

#include "printdlg.h"


PrintDlg::PrintDlg(QWidget * parent, Qt::WindowFlags f):QDialog(parent,f) {
	setupUi(this);
	setWindowTitle("Export");
	radioButton_4->setChecked(true);
}

