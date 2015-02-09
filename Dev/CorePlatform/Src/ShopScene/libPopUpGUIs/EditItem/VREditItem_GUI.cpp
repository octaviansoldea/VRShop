#include <osgDB/ReadFile>

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VREditItem_GUI.h"

using namespace Ui;
using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

EditItem_GUI::EditItem_GUI(AbstractObject * apAbstractObject) :
EditItem_GUIBase(apAbstractObject)	{
	setupUi(this);

	Matrix mtrxTemp = Matrix::identity();
	m_pAbstractObject->setMatrix(mtrxTemp);

	m_pOSGQT_Widget->setSceneData(m_pAbstractObject);
	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);

	connect(m_pToolButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonApply, SIGNAL(clicked()), this, SLOT(accept()));

	connect(m_pToolButtonTexture, SIGNAL(pressed()), this, SLOT(slotBrowseDirectory()));

	connect(m_pLineEditColorR, SIGNAL(textEdited(const QString &)), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorG, SIGNAL(textEdited(const QString &)), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorB, SIGNAL(textEdited(const QString &)), this, SLOT(slotSetColor()));
	connect(m_pLineEditColorA, SIGNAL(textEdited(const QString &)), this, SLOT(slotSetColor()));

	m_pOSGQT_Widget->show();

	m_pLineEditColorR->setText("0");
	m_pLineEditColorG->setText("0");
	m_pLineEditColorB->setText("0");
	m_pLineEditColorA->setText("0");
}

//----------------------------------------------------------------------

void EditItem_GUI::previewTexture(QString & aqstrFileName)	{
	QImageReader image(aqstrFileName);
	QPixmap p(QPixmap::fromImageReader(&image));
	QPixmap p1(p.scaled ( m_pLabelTexture->width(),m_pLabelTexture->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelTexture->setPixmap(p1);
	m_pAbstractObject->setTexture(aqstrFileName.toStdString());
}

//----------------------------------------------------------------------

void EditItem_GUI::slotSetColor()	{
	m_pAbstractObject->setTexture("");
	vector<float> vecflColor;

	float flR = m_pLineEditColorR->text().toFloat();
	vecflColor.push_back((flR < 1) ? flR : flR/255);
	float flG = m_pLineEditColorG->text().toFloat();
	vecflColor.push_back((flG < 1) ? flG : flG/255);
	float flB = m_pLineEditColorB->text().toFloat();
	vecflColor.push_back((flB < 1) ? flB : flB/255);
	float flA = m_pLineEditColorA->text().toFloat();
	vecflColor.push_back((flA < 1) ? flA : flA/255);

	m_pAbstractObject->setColor(vecflColor);
}

//----------------------------------------------------------------------

vector<float> EditItem_GUI::getColor() const	{
	vector<float> vecflColor;

	if (stof(m_pLineEditColorA->text().toStdString()) < 0)	{
		return vector<float>(0);
	}

	vecflColor.push_back(stof(m_pLineEditColorR->text().toStdString()));
	vecflColor.push_back(stof(m_pLineEditColorG->text().toStdString()));
	vecflColor.push_back(stof(m_pLineEditColorB->text().toStdString()));
	vecflColor.push_back(stof(m_pLineEditColorA->text().toStdString()));

	return vecflColor;
}

//----------------------------------------------------------------------

string EditItem_GUI::getTexture()	{
	string strTexture = m_pAbstractObject->getTexture();
	return strTexture;
}