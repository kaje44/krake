/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:12:07                                **
**                                                                  **
**  Posledni upravy: St 27.úno.2013 10:16:47                        **
*********************************************************************/



#include <QDebug>

#include "commonmodel.h"

#include "daydata.h"

#include "inputdlg.h"


InputDlg::InputDlg(QWidget * parent, Qt::WindowFlags f) : QDialog(parent,f) {
	setupUi(this);	
	m_id = -1;
	m_pictureM = new PictureModel;
	comboBox->setModel(m_pictureM);
	radioButton->setChecked(true);
	timeEdit->setTime(QTime(8,0));
}

//------------------------------------------------------------------------------------------------- 
 
void InputDlg::setData( const DayData* p_data, bool p_insert) {
	
	setWindowTitle( QString((p_insert) ? "Vložit nový údaj do " : "Úprava položky z ")+p_data->getDate().toString("dd.MM.yyyy"));

	m_id   = p_data->getId();	
	m_date = p_data->getDate();  
	timeEdit->setTime(p_data->getZeit());
	
	lineEdit->setText(p_data->getNachricht());
	comboBox->setCurrentIndex(m_pictureM->getIndex(p_data->getSicon()));
	setOdd(p_data->getOdd());
}

//------------------------------------------------------------------------------------------------- 

void InputDlg::sendData(DayData* p_dd) {
	QTime zeit = timeEdit->time();
	p_dd->setDayData ( lineEdit->text(), lineEdit_2->text(), m_date, zeit, getOdd(),
					   m_pictureM->item(comboBox->currentIndex())->data().toString(),m_id);
}

//------------------------------------------------------------------------------------------------- 

int InputDlg::getOdd() const {
	int ret = 0;
	if (radioButton->isChecked())
		ret = 1;	
	if (radioButton_2->isChecked())
		ret = 2;	
	if (radioButton_3->isChecked())
		ret = 3;	
	if (radioButton_4->isChecked())
		ret = 0;	
	return ret;	
}

//------------------------------------------------------------------------------------------------- 
 
void InputDlg::setOdd(const int p_odd) {
	
	radioButton->setChecked(false);
	radioButton_2->setChecked(false);
	radioButton_3->setChecked(false);
	radioButton_4->setChecked(false);

	switch(p_odd)	{
		case 1 : radioButton->setChecked(true);break;
		case 2 : radioButton_2->setChecked(true);break;
		case 3 : radioButton_3->setChecked(true);break;
		default: radioButton_4->setChecked(true);break;		
	};//switch
}

//------------------------------------------------------------------------------------------------- 
 
