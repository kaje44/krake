/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: Po 31.pro.2012 08:56:03                               **
**                                                                  **
**  Posledni upravy: Čt 28.úno.2013 08:37:21                        **
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
		if (dd->getOdd() == 0) 
			return QColor(Qt::cyan);	
		if (dd->getOdd() == 1) 
			return QColor(Qt::white);	
		if (dd->getOdd() == 2) 
			return QColor(Qt::darkRed);	
		if (dd->getOdd() == 3) 
			return QColor(Qt::darkBlue);	
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
			
		return QString("%1 %2 %3").arg(dd->getZeit().toString("HH:mm")).arg(strBau(dd->getNachricht(),8)).arg(strBau(dd->getZiel(),4));	
	};//if

	QVariant var = QStandardItemModel::data(index ,role);
    return var;
}

//------------------------------------------------------------------------------------------------- 
 
QString DayModel::strBau(QString p_str, int p_len) const {
	QString str = QString("%1").arg(p_str,(-1) * p_len,'_');
	str = str.left(p_len);
	qDebug() << "debug - " << str; 
	return str;
}

//------------------------------------------------------------------------------------------------- 
 
bool DayModel::dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent) {

	QString text, ziel;       
	QDate   date;    
	QTime   zeit;
	QString icon;
	int farbe ,id;
		
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
			stream >> id >> text >> ziel >> date >> zeit >> farbe >> icon;
			if ( date == m_date ) {
				return false;	
			}
			DayData *dd = new DayData;
			dd->setDayData ( text ,ziel, m_date ,zeit, farbe , icon ,id);
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
			DayData* si   = (DayData*) itemFromIndex(mi);
			int id		  = si->getId();
			QString text  = si->getNachricht(); 
			QString ziel  = si->getZiel(); 
			QDate   date  = si->getDate();
			QTime   zeit  = si->getZeit();
			int 	odd	  = si->getOdd();
			QString icon  = si->getSicon(); 
			stream << id << text << ziel << date << zeit << odd << icon ;
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
 
void DayModel::addDayData(DayData *p_data, bool p_storedb) {
	QString sicon = p_data->getSicon();
	if (sicon != "")
		p_data->setIcon(QIcon(sicon));
	if (p_storedb)
		sqle->insertDay(p_data);
	appendRow(p_data);	
}

//------------------------------------------------------------------------------------------------- 

void DayModel::updateDayData(int p_index,DayData* p_data) {
	DayData* dd = (DayData*) item(p_index);
	QString sicon = p_data->getSicon();
	if (sicon != "")
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
/*
	if ( lo == ro ) {
	    return ldt->getZeit() < rdt->getZeit();
	} else {
*/			
		return lo < ro;	
//	};//if
}

