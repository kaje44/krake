/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:12:07                                **
**                                                                  **
**  Posledni upravy: Út 05.úno.2013 08:57:29                        **
*********************************************************************/


#ifndef INPUTDLG_H
#define INPUTDLG_H


#include "obj/ui_inputdlg.h"

#include <QWidget>

#include "daydata.h"

class ColorModel;
class PictureModel;

class InputDlg : public QDialog, private Ui_InputDlg {
	Q_OBJECT	
private:
	QDate m_date;
	int m_id;
	ColorModel *m_colorM;
	PictureModel *m_pictureM;

public:
	InputDlg(QWidget * parent = 0, Qt::WindowFlags f = 0);
	//Nastaví data
	void setData( const DayData* p_data, bool p_insert = true );
	//Zašle data
//	void sendData(int &p_count, DayData* p_dd);
	void sendData(DayData* p_dd);

	void setFarbe(const int p_farbe);
	int getFarbe() const;

signals:
	void sendInputData(DayData p_data);	
};

#endif

