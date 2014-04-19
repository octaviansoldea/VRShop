#include <iostream>
#include <string>

#include "VRProductController.h"

#include "VRProductSettings_GUI.h"
#include "VRRemoveProduct_GUI.h"

#include "VRProduct.h"

#include "VRProductManager.h"

using namespace VR;
using namespace std;
using namespace osg;

//-----------------------------------------------------------------------------

ProductManager::ProductManager() :
m_pProduct(0)	{
	setName("Products");
}

//-----------------------------------------------------------------------------

ProductManager::~ProductManager()	{
	if (m_pProductSettings_GUI)
		delete m_pProductSettings_GUI;
	if (m_pRemoveProduct_GUI)
		delete m_pRemoveProduct_GUI;
	if (m_pProduct)
		delete m_pProduct;
}

//==============================================================================

const char* ProductManager::className() const	{
	return "ProductManager";
}

//--------------------------------------------------------------------------

Node * ProductManager::getChild(const string & astrChildName)	{
	Node * pChild = 0;
	if (astrChildName.empty())	{
		return pChild;
	}

	NodeList::iterator it = _children.begin();
	for (it; it != _children.end(); it++)	{
		const string & strChild = it->get()->getName();
		if (strChild == astrChildName)	{
			pChild = dynamic_cast<Node*>(it->get());

			return pChild;
		}
	}
	return pChild;
}

//-----------------------------------------------------------------------------

Product * ProductManager::getProduct(const AbstractObject * apAbstractObject)	{
	if (apAbstractObject == NULL)
		return 0;

	vector<Product*>::iterator it;
	for (it = m_pvecProducts.begin(); it != m_pvecProducts.end(); it++)	{
		if ((*it)->getRepresentation() == apAbstractObject)
			return *it;
	}
	return 0;
}

//-----------------------------------------------------------------------------

void ProductManager::addNewProduct()	{
	m_pProduct = new Product();
	modifyProduct(m_pProduct);

	if (m_pProduct != 0)	{
		m_pvecProducts.push_back(m_pProduct);

		//Fill osg group whose pointer is sent to the scene 
		//with the 3D representation of the product
		ref_ptr<AbstractObject> pProduct = m_pProduct->getRepresentation();
		addChild(pProduct);
	}

/*
	m_pProductSettings_GUI = new ProductSettings_GUI(m_pProduct);

	m_pProductSettings_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pProductSettings_GUI->exec();

	//If SAVE is clicked in the PROD.SETTINGS_GUI
	if (bRes == QDialog::Accepted)	{
		//Fill vector of products
		m_pvecProducts.push_back(m_pProduct);

		//Fill osg group whose pointer is sent to the scene 
		//with the 3D representation of the product
		ref_ptr<AbstractObject> pProduct = m_pProduct->getRepresentation();
		addChild(pProduct);

		ProductParams productParams;
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_strProductCategory = m_pProductSettings_GUI->m_pComboBoxProductCategory->currentText().toStdString();
		productParams.m_strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
		productParams.m_nProductCode = m_pProductSettings_GUI->m_pLineEditProductCode->text().toInt();
		productParams.m_strProductDescription = m_pProductSettings_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
		productParams.m_strProductShortDescription = m_pProductSettings_GUI->m_pLineEditShortDescription->text().toStdString();

	////	m_pProductParams->m_nManufacturerID = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strManufacturerOrigin = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateAdded = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateLastModified = m_pProductSettings_GUI-> ;
		productParams.m_strProductUnit = m_pProductSettings_GUI->m_pComboBoxProductUnit->currentText().toStdString();
		productParams.m_flPricePerUnit = m_pProductSettings_GUI->m_pLineEditPrice->text().toFloat();
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_flTaxRate = m_pProductSettings_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
	////	m_pProductParams->m_nCurrency = m_pProductSettings_GUI-> ;


		m_pProduct->setParams(productParams);

	} else {
		m_pProduct = 0;
	}
*/
}

//-----------------------------------------------------------------------------

void ProductManager::removeProduct()	{
	if (m_pProduct == 0)
		m_pProduct = new Product;

	removeProduct(m_pProduct);
}

//-----------------------------------------------------------------------------

void ProductManager::removeProduct(Product * apProduct)	{
	m_pProduct = apProduct;

	m_pRemoveProduct_GUI = new RemoveProduct_GUI(m_pProduct);
	m_pRemoveProduct_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pRemoveProduct_GUI->exec();

	if (bRes == QDialog::Accepted)	{	//Remove product confirmed
		removeChild(m_pProduct->getRepresentation());	//remove 3D
		m_pvecProducts.erase(remove(m_pvecProducts.begin(), m_pvecProducts.end(), m_pProduct),
			m_pvecProducts.end());	//Remove from the vector of products
	} else {
		m_pProduct = 0;
		//Remove product cancelled
	}

	delete m_pRemoveProduct_GUI;
}

//-----------------------------------------------------------------------------

void ProductManager::modifyProduct(Product * apProduct)	{
	m_pProduct = apProduct;
	m_pProductSettings_GUI = new ProductSettings_GUI(m_pProduct);

	AbstractObject * pAO = m_pProduct->getRepresentation();
	m_pProductSettings_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pProductSettings_GUI->exec();

	//If SAVE is clicked in the PROD.SETTINGS_GUI
	if (bRes == QDialog::Accepted)	{
		//Fill vector of products
//		m_pvecProducts.push_back(m_pProduct);

		ProductParams productParams;
		m_pProduct->getParams(productParams);

		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_strProductCategory = m_pProductSettings_GUI->m_pComboBoxProductCategory->currentText().toStdString();
		productParams.m_strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
		productParams.m_nProductCode = m_pProductSettings_GUI->m_pLineEditProductCode->text().toInt();
		productParams.m_strProductDescription = m_pProductSettings_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
		productParams.m_strProductShortDescription = m_pProductSettings_GUI->m_pLineEditShortDescription->text().toStdString();

	////	m_pProductParams->m_nManufacturerID = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strManufacturerOrigin = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateAdded = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateLastModified = m_pProductSettings_GUI-> ;
		productParams.m_strProductUnit = m_pProductSettings_GUI->m_pComboBoxProductUnit->currentText().toStdString();
		productParams.m_flPricePerUnit = m_pProductSettings_GUI->m_pLineEditPrice->text().toFloat();
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_flTaxRate = m_pProductSettings_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
	////	m_pProductParams->m_nCurrency = m_pProductSettings_GUI-> ;


		m_pProduct->setParams(productParams);

	} else {
		m_pProduct = 0;
	}
}