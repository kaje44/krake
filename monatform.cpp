/*********************************************************************
**  KaJe 2012                                                       **
**                                                                  **
**  Vytvořen: po 31.12.2012 08:37:53                                **
**                                                                  **
**  Posledni upravy: Út 05.úno.2013 08:37:05                        **
*********************************************************************/

#include <QtGui>

#include "sqlengine.h"
#include "dayitem.h"
#include "monatform.h"
#include "kjguilib.h" 

const QStringList monats = QStringList() << "Leden" 
										 << QObject::trUtf8("Únor") 
										 << QObject::trUtf8("Březen") 
										 << "Duben" 
										 << QObject::trUtf8("Květen") 
										 << QObject::trUtf8("Červen") 
										 << QObject::trUtf8("Červenec") 
										 << "Srpen" 
										 << QObject::trUtf8("Září") 
										 << QObject::trUtf8("Říjen") 
										 << "Listopad" 
										 << "Prosinec";


const QStringList days = QStringList()  << QObject::trUtf8("Pondělí") 
										<< QObject::trUtf8("Úterý")
										<< QObject::trUtf8("Středa")
										<< QObject::trUtf8("Čtvrtek")
										<< QObject::trUtf8("Pátek")
										<< "Sobota"
										<< QObject::trUtf8("Neděle");



MonatForm::MonatForm(QWidget * parent, Qt::WindowFlags f):QWidget(parent,f) {
	setupUi(this);
	m_change  = true;
	m_today   = QDate::currentDate();
	m_year    = m_today.year();
	m_month   = m_today.month();


	comboBox->addItems(monats);
	setDateTitle();

	createActions();
	toolButton->setDefaultAction(actGoPrev);
	toolButton_2->setDefaultAction(actGoNext);
	toolButton_3->setDefaultAction(actRefresh);

	QGridLayout *gridLayout = new QGridLayout(frame_2);
	gridLayout->setSpacing(2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	int i = 0;
	
	for(int col = 0; col < 7;col++) {
		gridLayout->addWidget(new QLabel(days[col]) , 0, col+1);
	};//for

	for(int row = 0; row < 6;row++) {
		for(int col = 0; col < 7;col++) {
			m_dia[i] = new DayItem(frame_2);
			gridLayout->addWidget(m_dia[i], row+2, col+1);
			i++;
		};//for
	};//for
	m_change  = false;
	connect(sqle, SIGNAL(addItem(int, DayData*)), this ,SLOT(addItem(int, DayData*)));
}

//------------------------------------------------------------------------------------------------- 
 
void MonatForm::updateTable() {	
	//vymzat
	for(int i = 0; i < 42;i++) {
		m_dia[i]->clear();	
	}	
	QDate dt = QDate(m_year,m_month,1);
	bool thisM = ((m_month == m_today.month()) && (m_year == m_today.year()));
	int first = dt.dayOfWeek();	
	first--;
	int count = dt.daysInMonth(); 

	int prevCount = 0;
	QDate prevDate;

	//předchozí
	if (first > 0) {
		QDate prevDt = dt.addMonths(-1);			
		int prevLast = prevDt.daysInMonth();
		prevDt = prevDt.addDays(prevLast - first);
		prevDate = prevDt;
		for(int i = 0; i < first;i++) {
			m_dia[i]->setDate(prevDt, false);	
			prevDt = prevDt.addDays(1);
			prevCount++;
		};//for
	};
	
	//stávající měsíc	
	for(int i = 0; i < count;i++) {
		m_dia[first+i]->setDate(dt);	
		dt = dt.addDays(1);
	};//for
	
	//následující
	QDate lastDt = dt;
	int lastStart = first+count;
	int lastCount = 0;
	for(int i = lastStart; i < 42;i++) {
		m_dia[i]->setDate(lastDt, false);	
		lastDt = lastDt.addDays(1);			
		lastCount++;
	};//for

	if (first>0) {
		sqle->initMonat( 0, (prevDate.day()*(-1)), prevDate, prevCount );
	}	

	sqle->initMonat( first, m_month, m_year );	 

	if (lastCount>0)
		sqle->initMonat( lastStart, -1, dt, lastCount );

}

//------------------------------------------------------------------------------------------------- 
 
void MonatForm::createActions() {
	actGoPrev  = new QAction(QIcon(":img/go-previous.png"), "&Zpět", this);
	actGoPrev->setStatusTip("Zpět");
	connect(actGoPrev, SIGNAL(triggered()), this, SLOT(meActGoPrev()));

	actGoNext  = new QAction(QIcon(":img/go-next.png"), "&Další", this);
	actGoNext->setStatusTip("Další");
	connect(actGoNext, SIGNAL(triggered()), this, SLOT(meActGoNext()));
	
	actRefresh  = new QAction(QIcon(":img/view-refresh.png"), "&Obnovit", this);
	actRefresh->setStatusTip("Obnovit");
	connect(actRefresh, SIGNAL(triggered()), this, SLOT(meActRefresh()));
}

//------------------------------------------------------------------------------------------------- 

void MonatForm::meActGoPrev() {
	m_change = true;	
	m_month--;	
	if (m_month < 1) {
		m_month = 12;	
		m_year--;	
	}	
	setDateTitle();
	updateTable();	
	m_change = false;	
}

//------------------------------------------------------------------------------------------------- 
 
void MonatForm::meActGoNext() {
	m_change = true;	
	m_month++;
	if (m_month > 12) {
		m_month = 1;	
		m_year++; 	
	};
	setDateTitle();
	updateTable();
	m_change = false;
}

//------------------------------------------------------------------------------------------------- 

void MonatForm::setDateTitle() {
	comboBox->setCurrentIndex(m_month-1);
	spinBox->setValue(m_year);
}

//------------------------------------------------------------------------------------------------- 
 
void MonatForm::addItem(int p_idx, DayData* p_data) {
	m_dia[p_idx]->receiveInputData( p_data, false );
}

//------------------------------------------------------------------------------------------------- 

void MonatForm::meActRefresh() {
	setCursor(Qt::BusyCursor);
	updateTable();
	setCursor(Qt::ArrowCursor);	
}

