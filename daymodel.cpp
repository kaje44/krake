/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: Po 31.pro.2012 08:56:03                               **
**                                                                  **
**  Posledni upravy: Čt 14.bře.2013 08:33:15                        **
**********************************************************************/

#include <QtGui>

#include "daydata.h"
#include "sqlengine.h"

#include "daymodel.h"


DayModel::DayModel(QObject * parent):QStandardItemModel(parent) {
}

//------------------------------------------------------------------------------------------------- 
 
void DayModel::setDate(const QDate p_date) {
	m_date = p_date;
}

//------------------------------------------------------------------------------------------------- 

QVariant DayModel::data ( const QModelIndex & index, int role ) const {
    if (!index.isValid())
        return QVariant();

	int row      = index.row();
	DayData *dd  =	(DayData *) item(row);

	//Pozadi
    if (role == Qt::BackgroundRole) {						
		if ((dd->getZiel() & ZE) == ZE) 
			return QColor(0xA0, 0x09, 0x09);	

		if (dd->getOdd() == 0) 
			return QColor(Qt::cyan);	
		if (dd->getOdd() == 1) 
			return QColor(0xF0, 0xF0, 0xF0);	
		if (dd->getOdd() == 2) 
			return QColor(0x09, 0xA0, 0x09);	
		if (dd->getOdd() == 3) 
			return QColor(0x0A, 0x0A, 0xF0);	
	};
		
	//Popredi
    if (role == Qt::ForegroundRole) {			
		if (dd->getOdd() == 0) 
			return QColor(Qt::black);	
		if (dd->getOdd() == 1) 
			return QColor(Qt::black);	
		if (dd->getOdd() == 2) 
			return QColor(Qt::white);	
		if (dd->getOdd() == 3) 
			return QColor(Qt::white);	
    };

	//Text
	if (role == Qt::DisplayRole) {			
		QString zada = 	dd->getZada();
		if (zada.length() > 4) {
			zada = dd->getZada().left(4); 
		};//if	
		return QString("%1 %2 - %3").arg(zada).arg(dd->getAufgabe()).arg(zielStr(dd->getZiel()));	
	};//if

	QVariant var = QStandardItemModel::data(index ,role);
    return var;
}

//------------------------------------------------------------------------------------------------- 
 
QString DayModel::zielStr(const int p_ziel) const {
	QString ret;	
	ret += ((p_ziel & ZR) == ZR) ? "R" : "";
	ret += ((p_ziel & ZO) == ZO) ? "O" : "";
	ret += ((p_ziel & ZN) == ZN) ? "N" : "";
	ret += ((p_ziel & ZE) == ZE) ? "!": "";
	return ret;
}

//------------------------------------------------------------------------------------------------- 
 
bool DayModel::dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) {

	QString aufgabe, zada, nachricht;       
	QDate   date;    
	int farbe ,id, ziel;
		
    if (action == Qt::IgnoreAction)
         return true;

    if (!(data->hasFormat(MIME_TYPE))) {	 
        return false;
	};	 

	int beginRow;
	
	if (row != -1)
		beginRow = row;
	else if (parent.isValid())
			beginRow = parent.row();
		 else
         	beginRow = rowCount(QModelIndex());
			
		if (data->hasFormat(MIME_TYPE)) {
	 		QByteArray encodedData = data->data(MIME_TYPE);
     		QDataStream stream(&encodedData, QIODevice::ReadOnly);
			stream >> id >> aufgabe >> ziel >> date >> zada >> farbe >> nachricht;
			if ( date == m_date ) {
				return false;	
			}
			DayData *dd = new DayData;
			dd->setDayData ( aufgabe ,ziel, m_date ,zada, farbe , nachricht ,id);
			addDayData(dd,true);
			emit resort();
			return true;
     	}
    return true;
}

//------------------------------------------------------------------------------------------------- 
  
QStringList DayModel::mimeTypes() const {
     QStringList types;     
	 types << MIME_TYPE;
     return types;
}
 
//------------------------------------------------------------------------------------------------- 

Qt::ItemFlags DayModel::flags(const QModelIndex &index) const {
     Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;
}

//------------------------------------------------------------------------------------------------- 
 
QMimeData *DayModel::mimeData(const QModelIndexList &indexes) const {

	QMimeData *mimeData = new QMimeData();

	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach (QModelIndex mi, indexes) {
		if (mi.isValid()) {
			DayData* si   	  = (DayData*) itemFromIndex(mi);
			int id		  	  = si->getId();
			QString aufgabe   = si->getAufgabe();
			int ziel  	  	  = si->getZiel(); 
			QDate   date  	  = si->getDate();
			QString zada  	  = si->getZada();
			int 	odd	  	  = si->getOdd();
			QString nachricht = si->getNachricht();
			stream << id << aufgabe << ziel << date << zada << odd << nachricht;
		}	
	}
	mimeData->setData(MIME_TYPE, encodedData);			
	return mimeData;
}

//------------------------------------------------------------------------------------------------- 

DayData* DayModel::getDay(const int p_index) const {
	return (DayData*) item(p_index);	
}

//------------------------------------------------------------------------------------------------- 
 
QString DayModel::getIcon(int p_odd) const {
	QString sicon;	
	switch ( p_odd ) {
		case 1 : sicon = ":img/jedna.png"; break;
		case 2 : sicon = ":img/dva.png";break;
		case 3 : sicon = ":img/tri.png";break;
		default: sicon = ":img/nula.png";break;
	};//swicth
	return sicon;
}

//------------------------------------------------------------------------------------------------- 
 
void DayModel::addDayData(DayData *p_data, bool p_storedb) {
	QString sicon = getIcon(p_data->getOdd());
	p_data->setIcon(QIcon(sicon));
	if (p_storedb)
		sqle->insertDay(p_data);
	appendRow(p_data);	
}

//------------------------------------------------------------------------------------------------- 

void DayModel::updateDayData(int p_index,DayData* p_data) {
	DayData* dd = (DayData*) item(p_index);
	QString sicon = getIcon(p_data->getOdd());
	dd->setIcon(QIcon(sicon));
	dd->setDayData(p_data);
	sqle->updateDay(p_data);
}

//------------------------------------------------------------------------------------------------- 

void DayModel::deleteDayData(int p_index) {
	DayData* dd = (DayData*) item(p_index);
	sqle->deleteDay(dd);
	takeRow(p_index);	
}

/*************************************************************************************************** 
 *                                         SortFilterProxyModel                                    * 
 ***************************************************************************************************/ 
 
SortProxyModel::SortProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {
}

//------------------------------------------------------------------------------------------------- 
 
bool SortProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    return (true);
}

//------------------------------------------------------------------------------------------------- 
 
bool SortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    DayData *ldt = (DayData *) ((DayModel *) sourceModel())->itemFromIndex(left); 
	DayData *rdt = (DayData *) ((DayModel *) sourceModel())->itemFromIndex(right);

	int lo = ldt->getOdd();
	int ro = rdt->getOdd();
	if ( lo < ro ) {
		return true;				
	} else {
		return false;	
	};
	return false;
}

