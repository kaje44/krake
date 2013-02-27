/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: po 31.12.2012 08:37:53                                **
**                                                                  **
**  Posledni upravy: So 02.úno.2013 09:16:46                        **
*********************************************************************/


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
	QAction	*actGoPrev, *actGoNext, *actRefresh;
	QDate m_today;
	DayItem *m_dia[42];
	bool m_change;

	void createActions();
	void setDateTitle();

private slots:
	void meActGoPrev();
	void meActGoNext();
	void meActRefresh();
	void addItem(int p_idx, DayData* p_data);

public:
	MonatForm(QWidget * parent = 0, Qt::WindowFlags f = 0);
	void updateTable();

};

#endif

