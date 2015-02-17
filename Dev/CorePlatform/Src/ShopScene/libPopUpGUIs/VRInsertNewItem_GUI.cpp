#include "VRBasicQTOperations.h"

#include "VRInsertNewItem_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

InsertNewItem_GUI::InsertNewItem_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, &QToolButton::clicked, this, &InsertNewItem_GUI::close);
	connect(m_pPushButtonCancel, &QPushButton::clicked, this, &InsertNewItem_GUI::close);
	connect(m_pPushButtonInsert, &QPushButton::clicked, this, &InsertNewItem_GUI::accept);
	connect(m_pPushButtonReadFile, &QPushButton::clicked, this, &InsertNewItem_GUI::slotInsertfromFile);
	connect(m_pListWidgetGroup, &QListWidget::itemClicked, this, &InsertNewItem_GUI::slotDisplayWidgetItems);
	connect(m_pListWidgetItem, &QListWidget::itemDoubleClicked, this, &InsertNewItem_GUI::accept);
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
	m_qstrFileName = BasicQtOperations::openSaveDialog("*.db \n *.obj\n*.osg *.osgt", this).c_str();

	if (m_qstrFileName=="")	{
		InsertNewItem_GUI::reject();
	} else {
		InsertNewItem_GUI::accept();
	}
}