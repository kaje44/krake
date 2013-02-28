/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 13:34:49                                **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 10:16:15                        **
*********************************************************************/


#ifndef DAYDATA_H
#define DAYDATA_H


#include <QStandardItem>


class DayData : public QStandardItem {

public:
	DayData();
	DayData(QDate p_date);
	void setDayData ( const QString p_text, const QString p_ziel, 
					  const QDate p_date, const QTime p_time, 
					  const int p_odd, const QString p_sicon, const int p_id = -1);   
	void setDayData ( const DayData* p_data );   
	void setId( int p_id );
	int getId() const;
	QDate getDate() const;
	QTime getZeit() const;
	int getOdd() const;    
	QString getSicon() const;  
	QString getText() const; 
	QString getNachricht() const;
	QString getZiel() const;
};

#endif

