/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 13:34:49                                **
**                                                                  **
**  Posledni upravy: Út 05.bře.2013 09:22:01                        **
*********************************************************************/


#ifndef DAYDATA_H
#define DAYDATA_H


#include <QStandardItem>


class DayData : public QStandardItem {

public:
	DayData();
	DayData(QDate p_date);
	void setDayData ( const QString p_augabe, const QString p_ziel, 
					  const QDate p_date, const QTime p_time, 
					  const int p_odd, const QString p_sicon, 
					  const QString p_nachricht, const int p_id = -1);   
	void setDayData ( const DayData* p_data );   
	void setId( int p_id );
	int getId() const;
	QDate getDate() const;
	QTime getZeit() const;
	int getOdd() const;    
	QString getSicon() const;  
	QString getAufgabe() const; 
	QString getNachricht() const;
	QString getZiel() const;
};

#endif

