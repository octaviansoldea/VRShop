#include <string>

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRAbstractObject.h"
#include "VRProduct.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "BasicStringDefinitions.h"

#include "VRProductSettings_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ProductSettings_GUI::ProductSettings_GUI() :
m_pProduct(0)	{
	setupUi(this);

	buildConnections();
}

//----------------------------------------------------------------------

ProductSettings_GUI::ProductSettings_GUI(Product * apProduct)	{
	setupUi(this);

	buildConnections();

	m_pProduct = apProduct;
	initGUI(m_pProduct);
}

//----------------------------------------------------------------------

ProductSettings_GUI::~ProductSettings_GUI()	{
	if (m_pOSGQT_Widget)
		delete m_pOSGQT_Widget;
}

//=====================================================================

void ProductSettings_GUI::buildConnections() {
	connect(m_pPushButtonSave, SIGNAL(pressed()), this, SLOT(accept()));
	connect(m_pPushButtonCancel, SIGNAL(pressed()), this, SLOT(close()));
	connect(m_pToolButtonClose, SIGNAL(clicked(bool)), this, SLOT(close()));
	
	connect(m_pComboBoxFrame, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotCreateRepresentation(const QString & )));
	connect(m_pToolButtonSetTexture, SIGNAL(pressed()), this, SLOT(slotSetTexture()));
}

//----------------------------------------------------------------------

void ProductSettings_GUI::initGUI(Product * apProduct)	{
	ProductParams prodParams;
	apProduct->getParams(prodParams);
	
	m_pLineEditQuantity->setText((to_string(long double(prodParams.m_flQuantity)).c_str()));

	m_pComboBoxProductCategory->setCurrentText(prodParams.m_strProductCategory.c_str());
	m_pLineEditProductName->setText(prodParams.m_strProductName.c_str());
	m_pLineEditProductCode->setText(tostr((int)prodParams.m_nProductCode).c_str());
	m_pTextEditProductDescription->setText(prodParams.m_strProductDescription.c_str());
	m_pLineEditShortDescription->setText(prodParams.m_strProductShortDescription.c_str());
	m_pLineEditProductURL->setText("NA");
	m_pComboBoxProducer->setCurrentText(prodParams.m_strManufacturerName.c_str());
	m_pTextEditProducerAddress->setText("NA");
	m_pComboBoxProducerURL->setCurrentText("NA");
	m_pComboBoxPlaceOfOrigin->setCurrentText(prodParams.m_strManufacturerOrigin.c_str());
	m_pComboBoxProductUnit->setCurrentText(prodParams.m_strProductUnit.c_str());
	m_pComboBoxUnitQuantity->setCurrentText("NA");
	m_pComboBoxTaxRate->setCurrentText(to_string(long double(prodParams.m_flTaxRate)).c_str() + QString("%"));
	m_pLineEditQuantity->setText(to_string(long double(prodParams.m_flQuantity)).c_str());
	m_pLineEditQuantLastChanged->setText("NA");
	m_pLineEditPrice->setText(to_string(long double(prodParams.m_flPricePerUnit)).c_str());
	m_pLineEditPriceLastChanged->setText("NA");

	m_pComboBoxFrame->setEditText(apProduct->className());

	if (apProduct->getRepresentation() != 0)
		slotCreateRepresentation(apProduct->getRepresentation()->className());
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotCreateRepresentation(const QString & aqstrFrameName)	{
	const std::string & strFrame = aqstrFrameName.toStdString();
	AbstractObjectParams aOP;
	aOP.m_flLenX = m_pDoubleSpinBoxSizeX->value();
	aOP.m_flLenY = m_pDoubleSpinBoxSizeY->value();
	aOP.m_flLenZ = m_pDoubleSpinBoxSizeZ->value();

	m_pProduct->createRepresentation(strFrame);

	if (m_qstrFileName !=0)
		m_pProduct->setTexture(m_qstrFileName.toStdString());

	m_pOSGQT_Widget->setSceneData(m_pProduct->getRepresentation());
	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);

	m_pOSGQT_Widget->show();
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

	if (m_pProduct->getRepresentation() !=0)
		m_pProduct->setTexture(m_qstrFileName.toStdString());
}

//----------------------------------------------------------------------

void ProductSettings_GUI::accept()	{
	QDialog::accept();
}

//----------------------------------------------------------------------

void ProductSettings_GUI::close()	{
	QDialog::close();
}
