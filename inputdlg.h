/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:12:07                                **
**                                                                  **
**  Posledni upravy: Pá 08.bře.2013 08:58:19                        **
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

public:
	InputDlg(QWidget * parent = 0, Qt::WindowFlags f = 0);
	//Nastaví data
	void setData( const DayData* p_data, bool p_insert = true );
	//Zašle data
//	void sendData(int &p_count, DayData* p_dd);
	void sendData(DayData* p_dd);

	void setOdd(const int p_odd);
	int getOdd() const;

signals:
	void sendInputData(DayData p_data);	
};

#endif

