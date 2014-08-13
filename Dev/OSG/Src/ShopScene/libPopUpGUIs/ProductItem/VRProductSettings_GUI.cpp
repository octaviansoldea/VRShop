#include <string>

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRAbstractObject.h"
#include "VRProductShopEditor.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "BasicStringDefinitions.h"

#include "VRProductSettings_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductSettings_GUI::ProductSettings_GUI() :
m_pProductShopEditor(0)	{
	setupUi(this);

	buildConnections();

	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQT_Widget->show();
}

//----------------------------------------------------------------------

ProductSettings_GUI::ProductSettings_GUI(ProductShopEditor * apProductShopEditor)	{
	setupUi(this);

	buildConnections();

	m_pProductShopEditor = apProductShopEditor;
	initGUI(m_pProductShopEditor);

	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQT_Widget->show();
}

//----------------------------------------------------------------------

ProductSettings_GUI::~ProductSettings_GUI()	{
}

//=====================================================================

void ProductSettings_GUI::buildConnections() {
	QDir directory("../../../Resources/Textures/Products/");
	QStringList files = directory.entryList(QDir::Files);
	m_pComboBoxImageSelect->insertItem(0,"Browse Image ...");
	m_pComboBoxImageSelect->addItems(files);

	connect(m_pPushButtonSave, SIGNAL(pressed()), this, SLOT(accept()));
	connect(m_pPushButtonCancel, SIGNAL(pressed()), this, SLOT(close()));
	connect(m_pToolButtonClose, SIGNAL(clicked(bool)), this, SLOT(close()));
	
	connect(m_pComboBoxFrame, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotCreateRepresentation(const QString & )));
	connect(m_pToolButtonSetTexture, SIGNAL(pressed()), this, SLOT(slotSetTexture()));
}

//----------------------------------------------------------------------

void ProductSettings_GUI::initGUI(ProductShopEditor * apProductShopEditor)	{
	ProductShopEditorParams prodParams;
	apProductShopEditor->getParams(prodParams);
	
	m_pLineEditQuantity->setText((tostr(prodParams.m_flQuantity)).c_str());

	m_pComboBoxProductCategory->setCurrentText(prodParams.m_strProductCategory.c_str());
	m_pLineEditProductName->setText(prodParams.m_strProductName.c_str());
	m_pLineEditProductCode->setText(tostr(prodParams.m_nProductCode).c_str());
	m_pTextEditProductDescription->setText(prodParams.m_strProductDescription.c_str());
	m_pLineEditShortDescription->setText(prodParams.m_strProductShortDescription.c_str());
	m_pLineEditProductURL->setText("NA");
	m_pComboBoxProducer->setCurrentText(prodParams.m_strManufacturerName.c_str());
	m_pTextEditProducerAddress->setText("NA");
	m_pComboBoxProducerURL->setCurrentText("NA");
	m_pComboBoxPlaceOfOrigin->setCurrentText(prodParams.m_strManufacturerOrigin.c_str());
	m_pComboBoxProductUnit->setCurrentText(prodParams.m_strProductUnit.c_str());
	m_pComboBoxUnitQuantity->setCurrentText("NA");
	m_pComboBoxTaxRate->setCurrentText(tostr(prodParams.m_flTaxRate).c_str() + QString("%"));
	m_pLineEditQuantity->setText(tostr(prodParams.m_flQuantity).c_str());
	m_pLineEditQuantLastChanged->setText("NA");
	m_pLineEditPrice->setText(tostr(prodParams.m_flPricePerUnit).c_str());
	m_pLineEditPriceLastChanged->setText("NA");

	m_pComboBoxFrame->setEditText(apProductShopEditor->className());

	if (apProductShopEditor->getRepresentation() != 0)
		slotCreateRepresentation(apProductShopEditor->getRepresentation()->className());
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotCreateRepresentation(const QString & aqstrFrameName)	{
	const std::string & strFrame = aqstrFrameName.toStdString();
	AbstractObjectParams aOP;
	aOP.m_flLenX = m_pDoubleSpinBoxSizeX->value();
	aOP.m_flLenY = m_pDoubleSpinBoxSizeY->value();
	aOP.m_flLenZ = m_pDoubleSpinBoxSizeZ->value();

	m_pProductShopEditor->createRepresentation(strFrame);

	if (m_qstrFileName !=0)
		m_pProductShopEditor->setTexture(m_qstrFileName.toStdString());

	m_pOSGQT_Widget->setSceneData(m_pProductShopEditor->getRepresentation());
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotSetTexture()	{
	m_qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		tr("."), "*.bmp");

	QImageReader image(m_qstrFileName);
	QPixmap p(QPixmap::fromImageReader(&image));
	QPixmap p1(p.scaled ( m_pLabelTexture->width(),m_pLabelTexture->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
	m_pLabelTexture->setPixmap(p1);

	if (m_pProductShopEditor->getRepresentation() !=0)
		m_pProductShopEditor->setTexture(m_qstrFileName.toStdString());
}

//----------------------------------------------------------------------

string ProductSettings_GUI::getTexture() const	{
	
	if (m_qstrFileName.isEmpty())	{
		return 0;
	} else {
		return m_qstrFileName.toStdString();
	}
}

//----------------------------------------------------------------------

void ProductSettings_GUI::accept()	{
	QDialog::accept();
}

//----------------------------------------------------------------------

void ProductSettings_GUI::close()	{
	QDialog::close();
}
