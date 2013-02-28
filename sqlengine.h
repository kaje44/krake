/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: pá 21.12.2012 14:55:14                                **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 10:23:33                        **
*********************************************************************/
#ifndef SQLENGINE_H
#define SQLENGINE_H

#include <QDate>
#include <QSqlDatabase>

#include "asqlengine.h"
#include "kjsqllib.h"
#include "daydata.h"

class QStandardItemModel;
class DayData;



class SqlEngine : public  ASqlEngine {
	Q_OBJECT	
private:
	void copyInto(KjSqlQuery &p_sql1, QString p_table1, KjSqlQuery &p_sql2, QString p_table2) throw (KjSqlException &);

public:
	SqlEngine(QString pDatabase, QString pModulName, QString pType);
	void deleteDay( const DayData* p_data ) const;
	//a DayData přiřadí id
	void insertDay( DayData* p_data ) const;	
	void updateDay( const DayData* p_data ) const;
	
	void initMonat( const int p_first, const int p_monat, const int p_jahr);
	void initMonat( const int p_first, const int p_dif, const QDate p_date, const int p_count);

	void update();
signals:
	void addItem(int p_idx, DayData* p_data);
};

extern SqlEngine *sqle;

#endif
