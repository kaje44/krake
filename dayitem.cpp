/*********************************************************************
**  KaJe 2013                                                       **
**                                                                  **
**  Vytvořen: st 02.01.2013 13:26:04                                **
**                                                                  **
**  Posledni upravy: Ne 03.úno.2013 10:12:42                        **
*********************************************************************/

#include <QtGui>

#include "daydata.h"
#include "daymodel.h"
#include "inputdlg.h"
#include "kjguilib.h"

#include "dayitem.h"

DayItem::DayItem(QWidget * parent): QFrame(parent) {
	setMaximumSize(QSize(150, 150));
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);

    
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(2, 2, 2, 2);
    m_lday = new QLabel(this);
    verticalLayout->addWidget(m_lday);

	m_msgList = new QListView(this);
	m_msgList->setMinimumSize(QSize(50, 50));
	m_msgList->setFrameShape(QFrame::NoFrame);
	m_msgList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_msgList->setDragDropMode(QAbstractItemView::DragDrop);
	verticalLayout->addWidget(m_msgList);

	setAcceptDrops(true);

	m_model = new DayModel();
	connect(m_model, SIGNAL(resort()), this, SLOT(resort()));
	m_proxyModel = new SortProxyModel(this);
	m_proxyModel->setDynamicSortFilter(true);
	m_proxyModel->setSourceModel(m_model);		
	m_msgList->setModel(m_proxyModel); 

	actAddItem  = new QAction(QIcon(":img/list-add.png"), "&Přidat", this);
	connect(actAddItem, SIGNAL(triggered()), this, SLOT(meActAddItem()));

	actDelItem  = new QAction(QIcon(":img/list-remove.png"), "&Smazat", this);
	connect(actDelItem, SIGNAL(triggered()), this, SLOT(meActDelItem()));

	actUpdItem  = new QAction(QIcon(":img/system-switch-user.png"), "&Upravit", this);
	connect(actUpdItem, SIGNAL(triggered()), this, SLOT(meActUpdItem()));

	QAction *sep = new QAction(this);
	sep->setSeparator(true);
	addAction(actAddItem);	
	addAction(actUpdItem);	
	addAction(sep); 
	addAction(actDelItem);
	setContextMenuPolicy(Qt::ActionsContextMenu);
}


//------------------------------------------------------------------------------------------------- 
 
void DayItem::setDate(QDate p_day, bool p_thisM ) {
	m_day = p_day;	
	bool today = ( m_day == QDate::currentDate());
	m_lday->setText(QString(" %1.").arg(m_day.day()));
	m_model->setDate(m_day);
	if (today) {
		setNowColor();	
	} else {
		if ( p_thisM )	
			setActiveColor();
		else
			setOtherColor();
	};//if
	setFrameShape(QFrame::StyledPanel);
}	

//------------------------------------------------------------------------------------------------- 
 
void DayItem::clear() {
	m_lday->setText("");
	m_model->clear();
	setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);
}

//------------------------------------------------------------------------------------------------- 

void DayItem::setActiveColor() {
    QPalette palette;
	QColor colBase(0xD6,0xD6,0x96);
	QColor colTitle(0xE0,0xE0,0xA0);
	
	palette.setColor(QPalette::Background,colTitle);
	palette.setColor(QPalette::Foreground,Qt::black);
	palette.setColor(QPalette::Base,colBase);
	setPalette(palette);                      	
	setAutoFillBackground( true );
}

//------------------------------------------------------------------------------------------------- 

void DayItem::setOtherColor() {
	QPalette palette;
	QColor colBase(0xB6,0xB6,0x76);
	QColor colTitle(0xC0,0xC0,0x90);
	palette.setColor(QPalette::Background,colTitle);
	palette.setColor(QPalette::Foreground,Qt::black);
	palette.setColor(QPalette::Base,colBase);
	setPalette(palette);                      	
	setAutoFillBackground( true );
}

//------------------------------------------------------------------------------------------------- 
 
void DayItem::setNowColor() {
	QPalette palette;
	QColor colBase(0xD6,0xD6,0x96);
	QColor colTitle(0xA0,0xA0,0xE0);
	palette.setColor(QPalette::Background,colTitle);
	palette.setColor(QPalette::Foreground,Qt::black);
	palette.setColor(QPalette::Base,colBase);
	setPalette(palette);                      	
	setAutoFillBackground( true );
}

//------------------------------------------------------------------------------------------------- 
// přídá položku

void DayItem::meActAddItem() {
	InputDlg dlg(this);
	dlg.setData(new DayData(m_day));
	if (dlg.exec()) {
		DayData* dd = new DayData;
		dlg.sendData(dd);	
		receiveInputData(dd);
		m_msgList->clearSelection();
		m_proxyModel->sort(0);
	};//if
}

//------------------------------------------------------------------------------------------------- 
// ubere položku

void DayItem::meActDelItem() {
	if ( m_msgList->selectionModel()->hasSelection() ) {
		int idx = m_msgList->selectionModel()->currentIndex().row();
		DayData* dd =  m_model->getDay(idx);
		if (quest("Kalendář", QString("Opravdu smazat položku: '%1' ?").arg(dd->getNachricht()))) {
			m_model->deleteDayData(idx);
			m_msgList->clearSelection();
		};
	};
}

//------------------------------------------------------------------------------------------------- 
//zedituje položku

void DayItem::meActUpdItem() {
	if ( m_msgList->selectionModel()->hasSelection() ) {
		int idx = m_msgList->selectionModel()->currentIndex().row();
		DayData* dd =  m_model->getDay(idx);
		InputDlg dlg(this);
		dlg.setData(dd,false);
		if (dlg.exec()) {
			DayData* dd = new DayData;
			dlg.sendData(dd);	
			m_model->updateDayData(idx,dd);
			m_msgList->clearSelection();
			m_proxyModel->sort(0);
		};//if
	};
}

//------------------------------------------------------------------------------------------------- 
 
void DayItem::receiveInputData( DayData* p_data, bool p_store) {
	m_model->addDayData(p_data, p_store);	
	m_msgList->clearSelection();
}

//------------------------------------------------------------------------------------------------- 
void DayItem::resort() {
	m_proxyModel->sort(0);
}
