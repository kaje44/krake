/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 13:34:49                                **
**                                                                  **
**  Posledni upravy: St 16.led.2013 17:57:55                        **
*********************************************************************/

#include <QDate>

#include "daydata.h"

#define DAY_DATE   Qt::UserRole +  1
#define DAY_TIME   Qt::UserRole +  2
#define DAY_ID     Qt::UserRole +  3
#define DAY_FARBE  Qt::UserRole +  4
#define DAY_SICON  Qt::UserRole +  5

/***************************************************************************************************
 *                                     DayData                                                     *
 **************************************************************************************************/ 


DayData::DayData(): QStandardItem() {
}

//------------------------------------------------------------------------------------------------- 
 
DayData::DayData(QDate p_date):QStandardItem() {
	setDayData ( "", p_date, QTime(8,0),0, "---");
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const QString & p_text, const QDate p_date, const QTime p_time,
		 				   const int p_farbe, const QString p_sicon, const int p_id) {
 	setText(p_text);
	setData(p_id 	,DAY_ID    );
	setData(p_date 	,DAY_DATE  );                 
	setData(p_time 	,DAY_TIME  ); 
	setData(p_farbe ,DAY_FARBE );                 
	setData(p_sicon ,DAY_SICON );                 
}

//------------------------------------------------------------------------------------------------- 
 
void DayData::setDayData ( const DayData* p_data ) {
	setDayData ( p_data->getNachricht(), 
				 p_data->getDate(),
				 p_data->getZeit(),
				 p_data->getFarbe(), 
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
 
int DayData::getFarbe() const {
	return this->data(DAY_FARBE).toInt();
}

//------------------------------------------------------------------------------------------------- 
 
QString DayData::getSicon() const {
	return this->data(DAY_SICON).toString();
}

//------------------------------------------------------------------------------------------------- 

QString DayData::getNachricht() const {
	return this->text();
}

//------------------------------------------------------------------------------------------------- 

