#include "VRInsertNewItem_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

InsertNewItem_GUI::InsertNewItem_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonInsert, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_pPushButtonReadFile, SIGNAL(clicked()), this, SLOT(slotInsertfromFile()));
	connect(m_pListWidgetGroup, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotDisplayWidgetItems(QListWidgetItem *)));
	connect(m_pListWidgetItem, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(accept()));
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::slotDisplayWidgetItems(QListWidgetItem * item)	{
	if (!item->isSelected())
		return;

	QString qstrGroup = item->text();
	m_pListWidgetItem->clear();

	QList < QString > qlststrItems;
	if (qstrGroup == "Geometric Shape")	{
		qlststrItems << "Cylinder" << "Plate3D" << "Prism" << "Sphere";
	}

	else if (qstrGroup == "Equipment")	{
		qlststrItems << "Cupboard" << "Container";
	}

	else if (qstrGroup == "Product")	{
		qlststrItems << "Product";
	}

	m_pListWidgetItem->addItems(qlststrItems);
}

//----------------------------------------------------------------------

void InsertNewItem_GUI::slotInsertfromFile()	{
}