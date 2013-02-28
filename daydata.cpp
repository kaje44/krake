/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 09:12:29                               **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 10:16:06                        **
**********************************************************************/

#include <QDate>

#include "daydata.h"


#define DAY_ID     Qt::UserRole +  1
#define DAY_DATE   Qt::UserRole +  2
#define DAY_TIME   Qt::UserRole +  3
#define DAY_NACHR  Qt::UserRole +  4
#define DAY_ZIEL   Qt::UserRole +  5
#define DAY_ODD	   Qt::UserRole +  6
#define DAY_SICON  Qt::UserRole +  7

/***************************************************************************************************
 *                                     DayData                                                     *
 **************************************************************************************************/ 


DayData::DayData(): QStandardItem() {
}

//------------------------------------------------------------------------------------------------- 
 
DayData::DayData(QDate p_date):QStandardItem() {
	setDayData ( "", "",p_date, QTime(8,0),0, "---");
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const QString p_text, const QString p_ziel, const QDate p_date, const QTime p_time,
		 				   const int p_odd, const QString p_sicon, const int p_id) {
 	setText(p_text);
	setData(p_id 	,DAY_ID    );
	setData(p_text 	,DAY_NACHR );                 
	setData(p_ziel 	,DAY_ZIEL  ); 
	setData(p_date 	,DAY_DATE  );                 
	setData(p_time 	,DAY_TIME  ); 
	setData(p_odd   ,DAY_ODD   );                 
	setData(p_sicon ,DAY_SICON );                 
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const DayData* p_data ) {
	setDayData ( p_data->getNachricht(), 
				 p_data->getZiel(),
				 p_data->getDate(),
				 p_data->getZeit(),
				 p_data->getOdd(), 
				 p_data->getSicon(), 
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

QString DayData::getNachricht() const {
	return this->data(DAY_NACHR).toString();
}

//------------------------------------------------------------------------------------------------- 

QString DayData::getZiel() const {
	return this->data(DAY_ZIEL).toString();
}

//------------------------------------------------------------------------------------------------- 

