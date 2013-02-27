/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: pá 21.12.2012 14:55:14                                **
**                                                                  **
**  Posledni upravy: Út 05.úno.2013 08:27:11                        **
*********************************************************************/

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
	insertDelDay( p_data );
	runCmd(QString("DELETE FROM kalendar WHERE id = '%1';").arg(p_data->getId()));
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::insertDay( DayData* p_data ) const {
	try {	
		KjSqlQuery sql;
		sql.clear();
		sql.prepare("INSERT INTO kalendar ( date, zeit, nachricht, farbe, sicon ) VALUES ( :date, :zeit, :nachricht, :farbe, :sicon );");
		sql.bindValue(":date"     , p_data->getDate().toString("yyyy-MM-dd"));
		sql.bindValue(":zeit"     , p_data->getZeit().toString("HH:mm:ss"));
		sql.bindValue(":nachricht", p_data->getNachricht());
		sql.bindValue(":farbe" 	  , p_data->getFarbe());
		sql.bindValue(":sicon" 	  , p_data->getSicon());
		sql.run();
	   	p_data->setId(sql.lastInsertId().toInt());
	} catch (KjSqlException ex) {
		saveError("insertDay",QString(ex.what()));
	};//try
	deleteDelDay(p_data);
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::insertDelDay( const DayData* p_data ) const {
	try {	
		KjSqlQuery sql;
		sql.clear();
		sql.prepare("INSERT INTO dekalendar ( date, zeit, nachricht, farbe, sicon ) VALUES ( :date, :zeit, :nachricht, :farbe, :sicon );");
		sql.bindValue(":date"     , p_data->getDate().toString("yyyy-MM-dd"));
		sql.bindValue(":zeit"     , p_data->getZeit().toString("HH:mm:ss"));
		sql.bindValue(":nachricht", p_data->getNachricht());
		sql.bindValue(":farbe" 	  , p_data->getFarbe());
		sql.bindValue(":sicon" 	  , p_data->getSicon());
		sql.run();		
	} catch (KjSqlException ex) {
		saveError("insertDelDay",QString(ex.what()));
	};//try
};

//------------------------------------------------------------------------------------------------- 
 
void SqlEngine::deleteDelDay( const DayData* p_data ) const {
	runCmd(QString("DELETE FROM dekalendar WHERE ( (date = '%1') AND (zeit = '%2') AND ( nachricht = '%3'));")
				  .arg( p_data->getDate().toString("yyyy-MM-dd"))
				  .arg(	p_data->getZeit().toString("HH:mm:ss"))
				  .arg( p_data->getNachricht() ));
};

//------------------------------------------------------------------------------------------------- 

void SqlEngine::updateDay( const DayData* p_data ) const {
	try {	
		KjSqlQuery sql;
		sql.clear();
		sql.prepare(QString("UPDATE kalendar SET date = :date, zeit = :zeit, nachricht = :nachricht, farbe = :farbe, sicon = :sicon WHERE ( id = '%1' )").arg(p_data->getId()));
		sql.bindValue(":date"     , p_data->getDate().toString("yyyy-MM-dd"));
		sql.bindValue(":zeit"     , p_data->getZeit().toString("HH:mm:ss"));
		sql.bindValue(":nachricht", p_data->getNachricht());
		sql.bindValue(":farbe" 	  , p_data->getFarbe());
		sql.bindValue(":sicon" 	  , p_data->getSicon());
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
		sql << QString("SELECT * FROM kalendar WHERE date BETWEEN '%1' AND '%2' ORDER BY date,zeit;")
						.arg(vonD.toString("yyyy-MM-dd"))
						.arg(bisD.toString("yyyy-MM-dd;"));
		while (sql.next()) {

			DayData	*dd = new DayData;
			int id            = sql.value(0).toInt();
			QDate   date      = sql.value(1).toDate();
			QTime   zeit      = sql.value(2).toTime();
			QString nachricht = sql.value(3).toString();
			int farbe         = sql.value(4).toInt();
			QString sicon     = sql.value(5).toString();
			
			dd->setDayData(nachricht,date,zeit,farbe,sicon,id);
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
		sql << QString("SELECT * FROM kalendar WHERE date BETWEEN '%1' AND '%2' ORDER BY date,zeit;")
						.arg(vonD.toString("yyyy-MM-dd"))
						.arg(bisD.toString("yyyy-MM-dd;"));

		while (sql.next()) {
			DayData	*dd = new DayData;
			int id            = sql.value(0).toInt();
			QDate   date      = sql.value(1).toDate();
			QTime   zeit      = sql.value(2).toTime();
			QString nachricht = sql.value(3).toString();
			int farbe         = sql.value(4).toInt();
			QString sicon     = sql.value(5).toString();
		
			dd->setDayData(nachricht,date,zeit,farbe,sicon,id);

			emit addItem(p_first+p_dif+date.day(),dd);
		};//while
	} catch (KjSqlException ex) {
		saveError("initMonat",QString(ex.what()));
	};//try
}

//------------------------------------------------------------------------------------------------- 
 
void SqlEngine::update() {
		/*
	try {
		KjSqlQuery usql1(m_db);
		KjSqlQuery usql2(m_db2);

		//dekalendar
		usql2 << "DELETE FROM dekalendar2;";	
		usql2 << "INSERT INTO dekalendar2 SELECT * FROM dekalendar;";
		copyInto( usql1, "dekalendar", usql2, "dekalendar2" );
		usql2 << "DELETE FROM dekalendar;";
		usql2 << "INSERT INTO dekalendar (date, zeit, nachricht, farbe, sicon) SELECT date, zeit, nachricht, farbe, sicon FROM dekalendar2 GROUP BY date, zeit, nachricht, farbe, sicon;";

		//kalendar
		usql2 << "DELETE FROM kalendar2;";
		usql2 << "INSERT INTO kalendar2 SELECT * FROM kalendar;";
		copyInto( usql1, "kalendar", usql2, "kalendar2" );
		usql2 << "DELETE FROM kalendar;";	
		usql2 << "INSERT INTO kalendar (date, zeit, nachricht, farbe, sicon) SELECT date, zeit, nachricht, farbe, sicon FROM kalendar2 GROUP BY date, zeit, nachricht, farbe, sicon;";

		//pročistit kalendář
		usql2 << QString("SELECT * FROM dekalendar;");
		while (usql2.next()) {
			QDate   date      = usql2.value(1).toDate();
			QTime   zeit      = usql2.value(2).toTime();
			QString nachricht = usql2.value(3).toString();
			int farbe         = usql2.value(4).toInt();
			QString sicon     = usql2.value(5).toString();		

			usql2 << QString("DELETE FROM kalendar WHERE ( (date = '%1') AND (zeit = '%2') AND ( nachricht = '%3'));")
				   .arg( date.toString("yyyy-MM-dd"))
				   .arg( zeit.toString("HH:mm:ss"))
				   .arg( nachricht);
		};//while
		
		usql2 << "DELETE FROM dekalendar;";
		copyInto( usql1, "dekalendar", usql2, "dekalendar" );	
		usql1 << "DELETE FROM dekalendar;";
		
		usql1 << "DELETE FROM kalendar;";
		copyInto( usql2, "kalendar", usql1, "kalendar" );
	
	} catch (KjSqlException ex) {
		qDebug() << "update - " << QString(ex.what());
	};//try
*/
}

//------------------------------------------------------------------------------------------------- 

void SqlEngine::copyInto(KjSqlQuery &p_sql1, QString p_table1, KjSqlQuery &p_sql2, QString p_table2) throw (KjSqlException &) {
	p_sql1 << QString("SELECT * FROM %1;").arg(p_table1);

	while (p_sql1.next()) {
		QDate   date      = p_sql1.value(1).toDate();
		QTime   zeit      = p_sql1.value(2).toTime();
		QString nachricht = p_sql1.value(3).toString();
		int farbe         = p_sql1.value(4).toInt();
		QString sicon     = p_sql1.value(5).toString();

		p_sql2.prepare(QString("INSERT INTO %1 ( date, zeit, nachricht, farbe, sicon ) VALUES ( :date, :zeit, :nachricht, :farbe, :sicon );").arg(p_table2));
		p_sql2.bindValue(":date"     , date.toString("yyyy-MM-dd"));
		p_sql2.bindValue(":zeit"     , zeit.toString("HH:mm:ss"));
		p_sql2.bindValue(":nachricht", nachricht);
		p_sql2.bindValue(":farbe" 	 , farbe);
		p_sql2.bindValue(":sicon" 	 , sicon);
		p_sql2.run();		
	};//while
}




