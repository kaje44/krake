/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: st 02.01.2013 13:26:04                                **
**                                                                  **
**  Posledni upravy: Ne 03.úno.2013 10:11:40                        **
*********************************************************************/
#ifndef DAYITEM_H
#define DAYITEM_H

#include <QFrame>

#include <QDate>

#include "daydata.h"

class DayModel;
class SortProxyModel;
class QLabel;   
class QListView;

class DayItem : public QFrame {
	Q_OBJECT
private:		
	// //ubere položku
	QAction  * actDelItem, *actAddItem, *actUpdItem;
	QLabel   * m_lday;
	QListView* m_msgList;
	QDate	   m_day;	
	DayModel  *m_model;
	SortProxyModel *m_proxyModel;
	
	void setActiveColor();
	void setOtherColor();
	void setNowColor();

private slots:
	void meActAddItem();
	void meActDelItem();
	void meActUpdItem();
	void resort();

public:
    DayItem(QWidget * parent = 0);
	//vše smaže 
	void clear();
	//nastaví datum
	void setDate(QDate p_day, bool p_thisM = true);
	void init();
	//příjem dat
	// @p_store uložit do db či ne
	void receiveInputData(DayData* p_data, bool p_store = true);

signals:
	void sendInputData(DayData p_data);	

};
#endif
