/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: pá 04.01.2013 08:12:07                                **
**                                                                  **
**  Posledni upravy: Čt 14.bře.2013 08:00:57                        **
*********************************************************************/

#include "daydata.h"

#include "sqlengine.h"

#include "inputdlg.h"


InputDlg::InputDlg(QWidget * parent, Qt::WindowFlags f) : QDialog(parent,f) {
	setupUi(this);	
	m_id = -1;
	m_zadaList = sqle->getZadaList();

	radioButton->setChecked(true);
	comboBox->addItems(m_zadaList);

	checkBox->setChecked(false);
	checkBox_2->setChecked(false);
	checkBox_3->setChecked(false);
	checkBox_4->setChecked(false);

	
}

//------------------------------------------------------------------------------------------------- 
 
void InputDlg::setData( const DayData* p_data, bool p_insert) {
	
	setWindowTitle( QString((p_insert) ? "Vložit nový údaj do " : "Úprava položky z ")+p_data->getDate().toString("dd.MM.yyyy"));

	m_id   = p_data->getId();	
	m_date = p_data->getDate();  
	comboBox->setCurrentIndex(m_zadaList.indexOf(p_data->getZada()));

	lineEdit->setText(p_data->getAufgabe());
	setZiel(p_data->getZiel());
	textEdit->setPlainText(p_data->getNachricht());
	setOdd(p_data->getOdd());
}

//------------------------------------------------------------------------------------------------- 

void InputDlg::sendData(DayData* p_dd) {
	p_dd->setDayData ( lineEdit->text(), getZiel(), m_date, comboBox->currentText(), getOdd(),
					   textEdit->toPlainText(),m_id);
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


int InputDlg::getZiel() const {
	int ret = 0;
	if (checkBox  ->checkState() == Qt::Checked) 
		ret |= ZR;	
	if (checkBox_2->checkState() == Qt::Checked)
		ret |= ZO;
	if (checkBox_3->checkState() == Qt::Checked)
		ret |= ZN;
	if (checkBox_4->checkState() == Qt::Checked)
		ret |= ZE;
	return ret;	
}

//------------------------------------------------------------------------------------------------- 
 
void InputDlg::setZiel(const int p_ziel) {
	checkBox  ->setCheckState( ((p_ziel & ZR) == ZR) ? Qt::Checked : Qt::Unchecked );
	checkBox_2->setCheckState( ((p_ziel & ZO) == ZO) ? Qt::Checked : Qt::Unchecked );
	checkBox_3->setCheckState( ((p_ziel & ZN) == ZN) ? Qt::Checked : Qt::Unchecked );
	checkBox_4->setCheckState( ((p_ziel & ZE) == ZE) ? Qt::Checked : Qt::Unchecked );
}

//------------------------------------------------------------------------------------------------- 
 
