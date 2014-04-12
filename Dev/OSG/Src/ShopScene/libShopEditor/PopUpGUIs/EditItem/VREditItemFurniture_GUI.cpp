#include <osgDB/ReadFile>

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VREditItemFurniture_GUI.h"

using namespace Ui;
using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

EditItemFurniture_GUI::EditItemFurniture_GUI(AbstractObject * apAbstractObject) :
EditItem_GUIBase(apAbstractObject)	{
	setupUi(this);
	
	m_pOSGQT_Widget->setSceneData(m_pAbstractObject);
	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);

	connect(m_pToolButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonApply, SIGNAL(clicked()), this, SLOT(accept()));

	connect(m_pToolButtonTexture, SIGNAL(pressed()), this, SLOT(slotBrowseDirectory()));

	connect(m_pLineEditColorR, SIGNAL(returnPressed()), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorG, SIGNAL(returnPressed()), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorB, SIGNAL(returnPressed()), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorA, SIGNAL(returnPressed()), this, SLOT(slotSetColor()));

	m_pOSGQT_Widget->show();

	m_pLineEditColorR->setText("0");
	m_pLineEditColorG->setText("0");
	m_pLineEditColorB->setText("0");
	m_pLineEditColorA->setText("0");
}

//----------------------------------------------------------------------

EditItemFurniture_GUI::~EditItemFurniture_GUI()	{
	if (m_pOSGQT_Widget)
		delete m_pOSGQT_Widget;
}


//----------------------------------------------------------------------

void EditItemFurniture_GUI::previewTexture(QString & aqstrFileName)	{
	QImageReader image(aqstrFileName);
	QPixmap p(QPixmap::fromImageReader(&image));
	QPixmap p1(p.scaled ( m_pLabelTexture->width(),m_pLabelTexture->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelTexture->setPixmap(p1);
}

//----------------------------------------------------------------------

void EditItemFurniture_GUI::slotSetColor()	{
	m_pAbstractObject->setTexture("");
	vector<float> vecflColor;
	vecflColor.push_back(m_pLineEditColorR->text().toFloat());
	vecflColor.push_back(m_pLineEditColorG->text().toFloat());
	vecflColor.push_back(m_pLineEditColorB->text().toFloat());
	vecflColor.push_back(m_pLineEditColorA->text().toFloat());
	m_pAbstractObject->setColor(vecflColor);
}

