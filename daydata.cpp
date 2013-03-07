/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 09:12:29                               **
**                                                                  **
**  Posledni upravy: Čt 07.bře.2013 09:45:08                        **
**********************************************************************/

#include <QDate>

#include "daydata.h"

#define DAY_ID      Qt::UserRole +  1
#define DAY_AUFGABE Qt::UserRole +  2
#define DAY_DATE    Qt::UserRole +  3
#define DAY_TIME    Qt::UserRole +  4
#define DAY_NACHR   Qt::UserRole +  5
#define DAY_ZIEL    Qt::UserRole +  6
#define DAY_ODD	    Qt::UserRole +  7
#define DAY_SICON   Qt::UserRole +  8

/***************************************************************************************************
 *                                     DayData                                                     *
 **************************************************************************************************/ 

DayData::DayData(): QStandardItem() {
}

//------------------------------------------------------------------------------------------------- 
 
DayData::DayData(QDate p_date):QStandardItem() {
	setDayData ( "", "",p_date, QTime(8,0),0, "---", "");
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const QString p_aufgabe, const QString p_ziel, const QDate p_date, const QTime p_time, 
						   const int p_odd, const QString p_sicon, const QString p_nachricht, const int p_id ) {
 	setText(p_aufgabe);
	setData(p_id 	,DAY_ID    );
	setData(p_aufgabe	,DAY_AUFGABE );
	setData(p_nachricht	,DAY_NACHR );
	setData(p_ziel 	,DAY_ZIEL  ); 
	setData(p_date 	,DAY_DATE  );                 
	setData(p_time 	,DAY_TIME  ); 
	setData(p_odd   ,DAY_ODD   );                 
	setData(p_sicon ,DAY_SICON ); 

	QString txt = QString("Úkol: %1\nCíl : %2\n%3").arg(p_aufgabe).arg(p_ziel).arg(p_nachricht);

	setToolTip(txt);
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const DayData* p_data ) {
	setDayData ( 
				 p_data->getAufgabe(), 
				 p_data->getZiel(),
				 p_data->getDate(),
				 p_data->getZeit(),
				 p_data->getOdd(),
				 p_data->getSicon(),
				 p_data->getNachricht(),
				 p_data->getId());
}

//------------------------------------------------------------------------------------------------- 
 
QDate DayData::getDate() const {
	return this->data(DAY_DATE).toDate();	
}

//------------------------------------------------------------------------------------------------- 
 
QTime DayData::getZeit() const {
	return this->data(DAY_TIME).toTime();	
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
 
QString DayData::getSicon() const {
	return this->data(DAY_SICON).toString();
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

QString DayData::getZiel() const {
	return this->data(DAY_ZIEL).toString();
}

//------------------------------------------------------------------------------------------------- 

