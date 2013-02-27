/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: Po 31.pro.2012 08:55:13                               **
**                                                                  **
**  Posledni upravy: Ne 03.úno.2013 10:10:16                        **
**********************************************************************/

#ifndef DAYMODEL_H
#define DAYMODEL_H


#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QDate>

#include "commonmodel.h"

class DayData;


class DayModel : public QStandardItemModel {
	Q_OBJECT
private:	
	QDate m_date;
public:
	DayModel( QObject * parent = 0 );
	void addDayData(DayData* p_data, bool p_storedb);
	QVariant data ( const QModelIndex & index, int role ) const;
	void deleteDayData(int p_index);
	//vraci data dle indexu
	DayData* getDay(const int p_index) const;
	//Drag&Drop
	bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent);
	Qt::ItemFlags flags(const QModelIndex &index) const;    
	QMimeData* mimeData(const QModelIndexList &indexes) const;
	QStringList mimeTypes() const;
	void setDate(const QDate p_date);
	void updateDayData(int p_index,DayData* p_data);
signals:
	void resort();
};


/**************************************************************************************************** 
 * *                                        SortProxyModel                                          * 
 * **************************************************************************************************/ 

class SortProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    SortProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

#define MIME_TYPE "kalendar/dayitem"

#endif //DAYMODEL_H

