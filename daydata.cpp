/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 09:12:29                               **
**                                                                  **
**  Posledni upravy: St 13.bře.2013 13:49:55                        **
**********************************************************************/

#include <QDate>

#include "daydata.h"

#define DAY_ID      Qt::UserRole +  1
#define DAY_AUFGABE Qt::UserRole +  2
#define DAY_DATE    Qt::UserRole +  3
#define DAY_ZADA    Qt::UserRole +  4
#define DAY_NACHR   Qt::UserRole +  5
#define DAY_ZIEL    Qt::UserRole +  6
#define DAY_ODD	    Qt::UserRole +  7



/***************************************************************************************************
 *                                     DayData                                                     *
 **************************************************************************************************/ 

DayData::DayData(): QStandardItem() {
}

//------------------------------------------------------------------------------------------------- 
 
DayData::DayData(QDate p_date):QStandardItem() {
	setDayData ( "", 0,p_date, "",0, "");
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const QString p_aufgabe, const int p_ziel, const QDate p_date, const QString p_zada, 
						   const int p_odd, const QString p_nachricht, const int p_id ) {
 	setText(p_aufgabe);
	setData(p_id 	,DAY_ID    );
	setData(p_aufgabe	,DAY_AUFGABE );
	setData(p_nachricht	,DAY_NACHR );
	setData(p_ziel 	,DAY_ZIEL  ); 
	setData(p_date 	,DAY_DATE  );                 
	setData(p_zada	,DAY_ZADA  ); 
	setData(p_odd   ,DAY_ODD   );                 

	QString txt = QString("Úkol: %1\nPro : %2\nCíl : %3\n%4").arg(p_aufgabe).arg(p_zada).arg(p_ziel).arg(p_nachricht);

	setToolTip(txt);
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const DayData* p_data ) {
	setDayData ( p_data->getAufgabe(), 
				 p_data->getZiel(),
				 p_data->getDate(),
				 p_data->getZada(),
				 p_data->getOdd(),
				 p_data->getNachricht(),
				 p_data->getId());
}

//------------------------------------------------------------------------------------------------- 
 
QDate DayData::getDate() const {
	return this->data(DAY_DATE).toDate();	
}

//------------------------------------------------------------------------------------------------- 
 
QString DayData::getZada() const {
	return this->data(DAY_ZADA).toString();	
}


//------------------------------------------------------------------------------------------------- 
 
void DayData::setId( int p_id ) {
	setData(p_id 	,DAY_ID    );
}

//------------------------------------------------------------------------------------------------- 
 
int DayData::getId() const {
	return this->data(DAY_ID).toInt();
}

//------------------------------------------------------------------------------------------------- 
 
int DayData::getOdd() const {
	return this->data(DAY_ODD).toInt();
}

//------------------------------------------------------------------------------------------------- 
 
QString DayData::getAufgabe() const {
	return this->data(DAY_AUFGABE).toString();
}

//------------------------------------------------------------------------------------------------- 

QString DayData::getNachricht() const {
	return this->data(DAY_NACHR).toString();
}

//------------------------------------------------------------------------------------------------- 

int DayData::getZiel() const {
	return this->data(DAY_ZIEL).toInt();
}

//------------------------------------------------------------------------------------------------- 

