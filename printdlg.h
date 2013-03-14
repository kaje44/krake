/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: čt 14.03.2013 08:16:58                                **
**                                                                  **
**  Posledni upravy: Čt 14.bře.2013 08:19:21                        **
*********************************************************************/


#ifndef PRINTDLG_H
#define PRINTDLG_H


#include "obj/ui_printdlg.h"

#include <QDialog>


class PrintDlg : public QDialog, private Ui_PrintDlg {
 public:
	PrintDlg(QWidget * parent = 0, Qt::WindowFlags f = 0);
};

#endif

