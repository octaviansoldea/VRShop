#include <string>
#include <iostream>
#include "BasicStringDefinitions.h"

#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>

#include "VRAbstractObject.h"
#include "VRProductShopEditor.h"
#include "VRProductManager.h"

#include "VRPickAndDragHandlerShopEditor.h"


#include "VRProductController.h"

using namespace VR;
using namespace std;
using namespace osg;

ProductController::ProductController(
QPushButton * apPushButton_ProductSettings_AddNewProduct,
QPushButton * apPushButton_ProductSettings_RemoveProduct,
QPushButton * apPushButton_ProductSettings_Apply,
QPushButton * apPushButton_ProductSettings_Cancel,
QPushButton * apPushButton_ProductSettings_MoreSettings,
QComboBox * apComboBox_ProductSettings_ProductName,
QLineEdit * apLineEdit_ProductSettings_NewPrice,
QLineEdit * apLineEdit_ProductSettings_NewQuantity,
QLineEdit * apLineEdit_ProductSettings_Price,
QLineEdit * apLineEdit_ProductSettings_Quantity,
ProductManager * apProductMgr,
PickAndDragHandlerShopEditor * apPickAndDragHandlerShopEditor)	{

	m_pPushButton_ProductSettings_AddNewProduct = apPushButton_ProductSettings_AddNewProduct;
	m_pPushButton_ProductSettings_RemoveProduct = apPushButton_ProductSettings_RemoveProduct;
	m_pPushButton_ProductSettings_Apply = apPushButton_ProductSettings_Apply;
	m_pPushButton_ProductSettings_Cancel = apPushButton_ProductSettings_Cancel;
	m_pPushButton_ProductSettings_MoreSettings = apPushButton_ProductSettings_MoreSettings;
	m_pComboBox_ProductSettings_ProductName = apComboBox_ProductSettings_ProductName;
	m_pLineEdit_ProductSettings_NewPrice = apLineEdit_ProductSettings_NewPrice;
	m_pLineEdit_ProductSettings_NewQuantity = apLineEdit_ProductSettings_NewQuantity;
	m_pLineEdit_ProductSettings_Price = apLineEdit_ProductSettings_Price;
	m_pLineEdit_ProductSettings_Quantity = apLineEdit_ProductSettings_Quantity;
	m_pProductMgr = apProductMgr;

	m_pPickAndDragHandlerShopEditor = apPickAndDragHandlerShopEditor;

	connect(m_pPushButton_ProductSettings_AddNewProduct, SIGNAL(pressed()), this, SLOT(slotAddNewProduct()));
	connect(m_pPushButton_ProductSettings_RemoveProduct,SIGNAL(pressed()),this,SLOT(slotRemoveProduct()));
	connect(m_pPushButton_ProductSettings_MoreSettings,SIGNAL(pressed()),this,SLOT(slotProductMoreSettings()));

	connect(m_pPushButton_ProductSettings_Apply,SIGNAL(clicked(bool)),this,SLOT(slotSetModifyProduct()));

	connect(
		m_pPickAndDragHandlerShopEditor,SIGNAL(signalProductPicked(const AbstractObject *)),
		this,SLOT(slotSetModifyProduct(const AbstractObject *)));
}

//---------------------------------------------------------

ProductController::~ProductController()	{
}

//=========================================================

void ProductController::slotAddNewProduct()	{
	m_pProductMgr->addNewProduct();
}

//---------------------------------------------------------

void ProductController::slotRemoveProduct()	{
	AbstractObject *pAO = m_pPickAndDragHandlerShopEditor->m_pPickedObject;

	if (pAO == 0)	{
	} else {
		//Only first parent is checked
		int nParent = pAO->getParentalNodePaths().size()-1;
		const string & strParentName = pAO->getParents()[nParent]->className();
		if (strParentName == "ProductManager")	{
			ProductShopEditor * pProductShopEditor = m_pProductMgr->getProduct(pAO);
			m_pProductMgr-> removeProduct(pProductShopEditor);
			m_pPickAndDragHandlerShopEditor->clearList();
		} else {
			//Picked object was not a product
		}
	}
}

//---------------------------------------------------------

void ProductController::slotProductMoreSettings()	{
	AbstractObject *pAO = m_pPickAndDragHandlerShopEditor->m_pPickedObject;

	if (pAO == 0)	{
		return;
	}

	//Only first parent is checked
	int nParent = pAO->getParentalNodePaths().size()-1;
	const string & strParentName = pAO->getParents()[nParent]->getName();
	if (strParentName == "Products")	{
		ProductShopEditor * pProductShopEditor = m_pProductMgr->getProduct(pAO);
		m_pProductMgr->modifyProduct(pProductShopEditor);
	} else {
		//Picked object was not a product
	}
	m_pPickAndDragHandlerShopEditor->clearList();
}

//---------------------------------------------------------

void ProductController::slotSetModifyProduct(const AbstractObject * apAbstractObject)	{
	const AbstractObject *pAO = apAbstractObject;

	m_pComboBox_ProductSettings_ProductName->clear();
	m_pLineEdit_ProductSettings_Price->clear();
	m_pLineEdit_ProductSettings_Quantity->clear();

	m_pProductShopEditor = m_pProductMgr->getProduct(pAO);
	ProductShopEditorParams params;
	m_pProductShopEditor->getParams(params);

	m_pComboBox_ProductSettings_ProductName->insertItem(0,params.m_strProductName.c_str());
	m_pLineEdit_ProductSettings_Price->setText(tostr(params.m_flPricePerUnit).c_str());
	m_pLineEdit_ProductSettings_Quantity->setText(tostr(params.m_flQuantity).c_str());

	m_pLineEdit_ProductSettings_NewPrice->setEnabled(true);
	m_pLineEdit_ProductSettings_NewQuantity->setEnabled(true);
}

//---------------------------------------------------------

void ProductController::slotSetModifyProduct()	{
	ProductShopEditorParams params;
	m_pProductShopEditor->getParams(params);

	m_pLineEdit_ProductSettings_Price->setText(m_pLineEdit_ProductSettings_NewPrice->text());
	m_pLineEdit_ProductSettings_Quantity->setText(m_pLineEdit_ProductSettings_NewQuantity->text());

	m_pLineEdit_ProductSettings_NewPrice->clear();
	m_pLineEdit_ProductSettings_NewQuantity->clear();

	params.m_flPricePerUnit = m_pLineEdit_ProductSettings_Price->text().toFloat();
	params.m_flQuantity = m_pLineEdit_ProductSettings_Quantity->text().toFloat();

	m_pProductShopEditor->setParams(params);
}