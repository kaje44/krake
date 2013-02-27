/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:16:54                                **
**                                                                  **
**  Posledni upravy: St 16.led.2013 16:51:39                        **
*********************************************************************/


#ifndef COMMONMODEL_H
#define COMMONMODEL_H

#include <QStandardItemModel>

/********************************************************************/

class PictureModel : public  QStandardItemModel {

private:
	void addPictureItem(QString p_title, QString p_sicon);

public:
	PictureModel();	
	//vrací index ikony
	int getIndex(const QString p_sicon) const;
};


#endif

