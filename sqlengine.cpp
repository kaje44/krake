/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: St 27.úno.2013 08:17:58                               **
**                                                                  **
**  Posledni upravy: St 13.bře.2013 15:21:01                        **
**********************************************************************/

#include <QDate>
#include <QtSql>
#include <QStandardItemModel>

#include "asqlengine.h"
#include "daydata.h"
#include "kjsqllib.h"
#include "kjguilib.h" 

#include "sqlengine.h"

SqlEngine::SqlEngine(QString pDatabase, QString pModulName, QString pType)
		 :ASqlEngine(pDatabase, pModulName, pType ) {
};

//------------------------------------------------------------------------------------------------- 
 
void SqlEngine::deleteDay( const DayData* p_data ) const {
	runCmd(QString("DELETE FROM infotask WHERE id = '%1';").arg(p_data->getId()));
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::insertDay( DayData* p_data ) const {
	try {	
		KjSqlQuery sql;
		sql.clear();
		sql.prepare("INSERT INTO infotask ( date, ziel, aufgabe, zada, odd, nachricht ) VALUES ( :date, :ziel, :aufgabe, :zada, :odd, :nachricht );");
		sql.bindValue(":date"     , p_data->getDate().toString("yyyy-MM-dd"));
		sql.bindValue(":ziel"     , p_data->getZiel());
		sql.bindValue(":aufgabe"  , p_data->getAufgabe());
		sql.bindValue(":zada"	  , p_data->getZada());
		sql.bindValue(":odd" 	  , p_data->getOdd());
		sql.bindValue(":nachricht", p_data->getNachricht());
		sql.run();
	   	p_data->setId(sql.lastInsertId().toInt());
	} catch (KjSqlException ex) {
		saveError("insertDay",QString(ex.what()));
	};//try
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::updateDay( const DayData* p_data ) const {
	try {	
		KjSqlQuery sql;
		sql.clear();
		sql.prepare(QString("UPDATE infotask SET date = :date, ziel = :ziel, aufgabe = :aufgabe, zada = :zada, odd = :odd, nachricht = :nachricht WHERE ( id = '%1' )").arg(p_data->getId()));
		sql.bindValue(":date"     , p_data->getDate().toString("yyyy-MM-dd"));
		sql.bindValue(":ziel"     , p_data->getZiel());
		sql.bindValue(":aufgabe"  , p_data->getAufgabe());
		sql.bindValue(":zada"	  , p_data->getZada());
		sql.bindValue(":odd" 	  , p_data->getOdd());
		sql.bindValue(":nachricht", p_data->getNachricht());
		sql.run();
	} catch (KjSqlException ex) {
		saveError("updateDay",QString(ex.what()));
	};//try
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::initMonat( const int p_first, const int p_monat, const int p_jahr) {
	QDate vonD(p_jahr, p_monat, 1); 
	QDate bisD(p_jahr, p_monat, vonD.daysInMonth()); 
	try {	
		KjSqlQuery sql;
		sql << QString("SELECT * FROM infotask WHERE date BETWEEN '%1' AND '%2' ORDER BY date;")
						.arg(vonD.toString("yyyy-MM-dd"))
						.arg(bisD.toString("yyyy-MM-dd;"));
		while (sql.next()) {

			DayData	*dd = new DayData;
			int id            = sql.value(0).toInt();
			QDate   date      = sql.value(1).toDate();
			int ziel      = sql.value(2).toInt();
			QString aufgabe   = sql.value(3).toString();
			QString zada	  = sql.value(4).toString();
			int odd           = sql.value(5).toInt();
			QString nachricht = sql.value(7).toString();
			
			dd->setDayData(aufgabe,ziel,date,zada,odd,nachricht,id);
			emit addItem(p_first-1+date.day(),dd);
		};//while

	} catch (KjSqlException ex) {
		saveError("initMonat",QString(ex.what()));
	};//try
}

//------------------------------------------------------------------------------------------------- 
 
void SqlEngine::initMonat( const int p_first, const int p_dif, const QDate p_date, const int p_count) {
	QDate vonD = p_date; 
	QDate bisD = p_date.addDays(p_count-1);
	
	try {
		KjSqlQuery sql;
		sql << QString("SELECT * FROM infotask WHERE date BETWEEN '%1' AND '%2' ORDER BY date;")
						.arg(vonD.toString("yyyy-MM-dd"))
						.arg(bisD.toString("yyyy-MM-dd;"));

		while (sql.next()) {
			DayData	*dd = new DayData;
			int id            = sql.value(0).toInt();
			QDate   date      = sql.value(1).toDate();
			int		ziel      = sql.value(2).toInt();
			QString aufgabe   = sql.value(3).toString();
			QString zada	  = sql.value(4).toString();
			int odd           = sql.value(5).toInt();
			QString sicon     = sql.value(6).toString();
			QString nachricht = sql.value(7).toString();
		
			dd->setDayData(aufgabe,ziel,date,zada,odd,nachricht,id);

			emit addItem(p_first+p_dif+date.day(),dd);
		};//while
	} catch (KjSqlException ex) {
		saveError("initMonat",QString(ex.what()));
	};//try
}

//------------------------------------------------------------------------------------------------- 
 
void SqlEngine::copyInto(KjSqlQuery &p_sql1, QString p_table1, KjSqlQuery &p_sql2, QString p_table2) throw (KjSqlException &) {
	p_sql1 << QString("SELECT * FROM %1;").arg(p_table1);

	while (p_sql1.next()) {
		QDate   date      = p_sql1.value(1).toDate();
		int     ziel      = p_sql1.value(2).toInt();
		QString aufgabe   = p_sql1.value(3).toString();	
		QString zada	  = p_sql1.value(4).toString();
		int odd	          = p_sql1.value(5).toInt();
		QString sicon     = p_sql1.value(6).toString();
		QString nachricht = p_sql1.value(7).toString();

		p_sql2.prepare(QString("INSERT INTO %1 ( date, ziel, aufgabe, zada, odd, nachricht ) VALUES ( :date, :ziel, :aufgabe, :zada, :odd, :nachricht);").arg(p_table2));
		p_sql2.bindValue(":date"     , date.toString("yyyy-MM-dd"));
		p_sql2.bindValue(":ziel"     , ziel);
		p_sql2.bindValue(":aufgabe"  , aufgabe);	
		p_sql2.bindValue(":zada"	 , zada);
		p_sql2.bindValue(":odd" 	 , odd);
		p_sql2.bindValue(":nachricht", nachricht);
		p_sql2.run();		
	};//while
}

//------------------------------------------------------------------------------------------------- 
 
QStringList SqlEngine::getZadaList() {
	QStringList sl;	
	sl << "";
	try {
		KjSqlQuery sql;
		sql << QString("SELECT * FROM zada;");
		while (sql.next()) {
			QString str = sql.value(1).toString();
			sl << str;
		};//while
		return sl;
	} catch (KjSqlException ex) {
		saveError("getZadaList",QString(ex.what()));
	};//try		
	return sl;
}




