/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 13:34:49                                **
**                                                                  **
**  Posledni upravy: St 13.bře.2013 13:49:49                        **
*********************************************************************/


#ifndef DAYDATA_H
#define DAYDATA_H


#include <QStandardItem>


class DayData : public QStandardItem {

public:
	DayData();
	DayData(QDate p_date);
	void setDayData ( const QString p_augabe, const int p_ziel, 
					  const QDate p_date, const QString p_zada, 
					  const int p_odd, const QString p_nachricht, const int p_id = -1 );   
	void setDayData ( const DayData* p_data );   
	void setId( int p_id );
	int getId() const;
	QDate getDate() const;
	QString getZada() const;
	int getOdd() const;    
	QString getAufgabe() const; 
	QString getNachricht() const;
	int getZiel() const;
};

#define ZR 1
#define ZO 2
#define ZN 4
#define ZE 8


#endif

