#include <iostream>
#include "VRInsertNewItem_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

InsertNewItem_GUI::InsertNewItem_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonInsert, SIGNAL(clicked()), this, SLOT(insertNewItem()));
	connect(m_pListWidgetGroup, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(displayWidgetItems(QListWidgetItem *)));
	connect(m_pListWidgetItem, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(insertNewItem()));
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::displayWidgetItems(QListWidgetItem * item)	{
	if (!item->isSelected())
		return;

	QString qstrGroup = item->text();
	m_pListWidgetItem->clear();

	QList < QString > qlststrItems;
	if (qstrGroup == "Geometric Shape")	{
		qlststrItems << "New Cylinder" << "New Parallelepiped" << "New Polygon" << "New Sphere";
	}

	if (qstrGroup == "Equipment")	{
		qlststrItems << "New Cupboard" << "New Container";
	}

	if (qstrGroup == "Product")	{
		qlststrItems << "New Product";
	}

	m_pListWidgetItem->addItems(qlststrItems);
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::insertNewItem()	{
	if(!m_pListWidgetItem->currentItem())
		return;

	QString & qstrSelectedItem = m_pListWidgetItem->currentItem()->text();

	std::string text = qstrSelectedItem.toStdString();

	std::cout << "Insert new item clicked: " << text << std::endl;	
}