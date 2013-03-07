/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 08:17:29                               **
**                                                                  **
**  Posledni upravy: Čt 07.bře.2013 09:47:25                        **
**********************************************************************/

#ifndef MONATFORM_H
#define MONATFORM_H


#include "obj/ui_monatform.h"

#include <QWidget>
#include <QDate>

class DayItem;
class DayData;

class MonatForm : public QWidget, private Ui_MonatForm {
	Q_OBJECT
private:
	int m_year ,m_month;
	QAction	*actGoPrev, *actGoNext, *actRefresh, *actExport;
	QDate m_today;
	DayItem *m_dia[42];
	bool m_change;

	void createActions();
	void setDateTitle();

private slots:
	void meActGoPrev();
	void meActGoNext();
	void meActExport();
	void meActRefresh();
	void addItem(int p_idx, DayData* p_data);

public:
	MonatForm(QWidget * parent = 0, Qt::WindowFlags f = 0);
	void updateTable();

};

#endif

