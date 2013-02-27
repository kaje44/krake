/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:16:54                                **
**                                                                  **
**  Posledni upravy: St 16.led.2013 16:52:23                        **
*********************************************************************/

#include <QStandardItemModel>
#include "commonmodel.h"

/*------------------------------------------------------------------------------------------------- 
-------------------------------------------------------------------------------------------------*/

PictureModel::PictureModel(): QStandardItemModel() {
	addPictureItem("---"					  ,"---");
	addPictureItem("",":img/call-start.png");
	addPictureItem("",":img/chronometer.png");
	addPictureItem("",":img/daemon.png");
	addPictureItem("",":img/emblem-favorite.png");
	addPictureItem("",":img/emblem-important.png");
	addPictureItem("",":img/emblem-new.png");
	addPictureItem("",":img/mail-mark-unread.png");
	addPictureItem("",":img/meeting-participant-reply.png");
	addPictureItem("",":img/meeting-participant.png");
	addPictureItem("",":img/preferences-desktop-notification.png");
	addPictureItem("",":img/quickopen.png");
	addPictureItem("",":img/rating.png");
	addPictureItem("",":img/face-angel.png");
	addPictureItem("",":img/face-embarrassed.png");
	addPictureItem("",":img/face-kiss.png");
	addPictureItem("",":img/face-laugh.png");
	addPictureItem("",":img/face-plain.png");
	addPictureItem("",":img/face-raspberry.png");
	addPictureItem("",":img/face-sad.png");
	addPictureItem("",":img/face-smile-big.png");
	addPictureItem("",":img/face-smile.png");
	addPictureItem("",":img/face-surprise.png");
	addPictureItem("",":img/face-uncertain.png");
	addPictureItem("",":img/face-wink.png");
}

//------------------------------------------------------------------------------------------------- 

void PictureModel::addPictureItem(QString p_title, QString p_sicon) { 
	QStandardItem *si = new QStandardItem(QIcon(p_sicon),p_title); 
	si->setData(p_sicon);
	appendRow(si);
}

//------------------------------------------------------------------------------------------------- 

int PictureModel::getIndex(const QString p_sicon) const {
	int res = -1;
	for(int i = 0; i < rowCount();i++) {
		if (item(i)->data().toString() == p_sicon) {
			res = i;
			break;
		};//if
	};//for
	return res;
}

//------------------------------------------------------------------------------------------------- 
 
