#include <osgDB/ReadFile>

#include "BasicStringDefinitions.h"

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VRPrism.h"

#include "VREditItemPrism_GUI.h"

using namespace Ui;
using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

EditItemPrism_GUI::EditItemPrism_GUI(AbstractObject * apAbstractObject) :
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

	Prism * pPrism = static_cast<Prism*>(m_pAbstractObject.get());
	int nRes = pPrism->getResolution();
	m_pSpinBoxResolution->setValue(nRes);
	connect(m_pSpinBoxResolution, SIGNAL(valueChanged(int)), this, SLOT(slotSetResolution()));


	m_pOSGQT_Widget->show();

	vector<float> vecColor = pPrism->getColor();

	m_pLineEditColorR->setText(tostr(vecColor[0]*255).c_str());
	m_pLineEditColorG->setText(tostr(vecColor[1]*255).c_str());
	m_pLineEditColorB->setText(tostr(vecColor[2]*255).c_str());
	m_pLineEditColorA->setText(tostr(vecColor[3]*255).c_str());
}

//----------------------------------------------------------------------

void EditItemPrism_GUI::previewTexture(QString & aqstrFileName)	{
	QImageReader image(aqstrFileName);
	QPixmap p(QPixmap::fromImageReader(&image));
//	QPixmap p1(p.scaled ( m_pLabelTexture->width(),m_pLabelTexture->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	QPixmap p1(p.scaled ( m_pLabelTexture->width(),m_pLabelTexture->height(),Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation ));
	m_pLabelTexture->setPixmap(p1);
	m_pAbstractObject->setTexture(aqstrFileName.toStdString());
}

//----------------------------------------------------------------------

void EditItemPrism_GUI::slotSetColor()	{
	string strTexture = m_pAbstractObject->getTexture();

	if ((strTexture != "") && (strTexture != " "))	{
		m_pAbstractObject->setTexture("");
	}
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

void EditItemPrism_GUI::slotSetResolution()	{
	Prism * pPrism = dynamic_cast<Prism*>(m_pAbstractObject.get());
	int nResolution = this->m_pSpinBoxResolution->value();
	pPrism->setResolution(nResolution);
}

//----------------------------------------------------------------------

vector<float> EditItemPrism_GUI::getColor() const	{
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

string EditItemPrism_GUI::getTexture()	{
	string strTexture = m_pAbstractObject->getTexture();
	return strTexture;
}
