#include "VRInsertNewItem_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

InsertNewItem_GUI::InsertNewItem_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonInsert, SIGNAL(clicked()), this, SLOT(slotInsertNewItem()));
	connect(m_pListWidgetGroup, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotDisplayWidgetItems(QListWidgetItem *)));
	connect(m_pListWidgetItem, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(slotInsertNewItem()));
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::slotDisplayWidgetItems(QListWidgetItem * item)	{
	if (!item->isSelected())
		return;

	QString qstrGroup = item->text();
	m_pListWidgetItem->clear();

	QList < QString > qlststrItems;
	if (qstrGroup == "Geometric Shape")	{
		qlststrItems << "Cylinder" << "Plate3D" << "Polygon" << "Sphere";
	}

	if (qstrGroup == "Equipment")	{
		qlststrItems << "Cupboard" << "Container";
	}

	if (qstrGroup == "Product")	{
		qlststrItems << "Product";
	}

	m_pListWidgetItem->addItems(qlststrItems);
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::slotInsertNewItem()	{
	if(!m_pListWidgetItem->currentItem())
		return;

	QString qstrSelectedItem = m_pListWidgetItem->currentItem()->text();
	
	emit signalNewItemRequested(qstrSelectedItem);
}