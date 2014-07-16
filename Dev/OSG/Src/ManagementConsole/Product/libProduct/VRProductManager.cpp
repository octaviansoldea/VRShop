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

ProductManager::ProductManager() {
	m_pProductSettings_GUI = 0;
	m_pRemoveProduct_GUI = 0;

	m_pgrpProductsRepresentation = new Group();
	m_pgrpProductsRepresentation->setName("Products");
}

//-----------------------------------------------------------------------------

ProductManager::~ProductManager()	{
	if (m_pProductSettings_GUI !=0)
		delete m_pProductSettings_GUI;
	if (m_pRemoveProduct_GUI != 0)
		delete m_pRemoveProduct_GUI;

	list<Product*>::iterator it = m_lstProducts.begin();
	for(it; it != m_lstProducts.end(); ++it)	{
		Product * pProduct = (Product*)(*it);
		delete pProduct;
		pProduct = 0;
	}
}

//==============================================================================

const char* ProductManager::className() const	{
	return "ProductManager";
}

//--------------------------------------------------------------------------

Node * ProductManager::getProductsRepresentation()	{
	return m_pgrpProductsRepresentation;
}

//--------------------------------------------------------------------------

Node * ProductManager::getChild(const string & astrChildName)	{
	Node * pChild = 0;
	if (astrChildName.empty())	{
		return pChild;
	}

	int nSize = m_pgrpProductsRepresentation->getNumChildren();
	int nI;

	for (nI=0; nI<nSize; nI++)	{
		const string & strChild = m_pgrpProductsRepresentation->getChild(nI)->getName();
		if (strChild == astrChildName)	{
			pChild = dynamic_cast<Node*>(m_pgrpProductsRepresentation->getChild(nI));

			return pChild;
		}
	}
	return pChild;
}

//-----------------------------------------------------------------------------

Product * ProductManager::getProduct(const AbstractObject * apAbstractObject)	{
	if (apAbstractObject == NULL)
		return 0;

	list<Product*>::iterator it;
	for (it = m_lstProducts.begin(); it != m_lstProducts.end(); it++)	{
		if ((*it)->getRepresentation() == apAbstractObject)	{
			return *it;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------

void ProductManager::addNewProduct(Product * apProduct)	{
	Product * pProduct = dynamic_cast<VR::Product*>(apProduct);
	if (pProduct != 0)	{
		m_lstProducts.push_back(pProduct);

		//Fill osg group whose pointer is sent to the scene 
		//with the 3D representation of the product
		ref_ptr<AbstractObject> pProd = pProduct->getRepresentation();
		m_pgrpProductsRepresentation->addChild(pProd);
	}
}

//-----------------------------------------------------------------------------

void ProductManager::addNewProduct()	{
	Product * pProduct = new Product();
	modifyProduct(pProduct);

	if (pProduct != 0)	{
		m_lstProducts.push_back(pProduct);

		float flScaleX = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeX->value();
		float flScaleY = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeY->value();
		float flScaleZ = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeZ->value();

		//Fill osg group whose pointer is sent to the scene 
		//with the 3D representation of the product
		ref_ptr<AbstractObject> prefProduct = pProduct->getRepresentation();
		prefProduct->setScaling(flScaleX, flScaleY, flScaleZ);
		m_pgrpProductsRepresentation->addChild(prefProduct);
	}
}

//-----------------------------------------------------------------------------

//void ProductManager::removeProduct()	{
//	removeProduct(m_pProduct);
//}

//-----------------------------------------------------------------------------

void ProductManager::removeProduct(Product * apProduct)	{

	m_pRemoveProduct_GUI = new RemoveProduct_GUI(apProduct);
	m_pRemoveProduct_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pRemoveProduct_GUI->exec();

	if (bRes == QDialog::Accepted)	{	//Remove product confirmed
		m_pgrpProductsRepresentation->removeChild(apProduct->getRepresentation());	//remove 3D
		m_lstProducts.erase(remove(m_lstProducts.begin(), m_lstProducts.end(), apProduct),
			m_lstProducts.end());	//Remove from the vector of products
	}

	delete m_pRemoveProduct_GUI;
}

//-----------------------------------------------------------------------------

void ProductManager::modifyProduct(Product * apProduct)	{
	m_pProductSettings_GUI = new ProductSettings_GUI(apProduct);

	AbstractObject * pAO = apProduct->getRepresentation();
	m_pProductSettings_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pProductSettings_GUI->exec();

	//If SAVE is clicked in the PROD.SETTINGS_GUI
	if (bRes == QDialog::Accepted)	{
		//Fill vector of products
//		m_pvecProducts.push_back(m_pProduct);

		ProductParams productParams;
		apProduct->getParams(productParams);

		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_strProductCategory = m_pProductSettings_GUI->m_pComboBoxProductCategory->currentText().toStdString();
		productParams.m_strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
		productParams.m_nProductCode = m_pProductSettings_GUI->m_pLineEditProductCode->text().toInt();
		productParams.m_strProductDescription = m_pProductSettings_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
		productParams.m_strProductShortDescription = m_pProductSettings_GUI->m_pLineEditShortDescription->text().toStdString();

	////	m_pProductParams->m_strManufacturerName = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strManufacturerOrigin = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateAdded = m_pProductSettings_GUI-> ;
	////	m_pProductParams->m_strDateLastModified = m_pProductSettings_GUI-> ;
		productParams.m_strProductUnit = m_pProductSettings_GUI->m_pComboBoxProductUnit->currentText().toStdString();
		productParams.m_flPricePerUnit = m_pProductSettings_GUI->m_pLineEditPrice->text().toFloat();
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_flTaxRate = m_pProductSettings_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
	////	m_pProductParams->m_nCurrency = m_pProductSettings_GUI-> ;


		apProduct->setParams(productParams);

	}
}

//-----------------------------------------------------------------------------

void ProductManager::createDBTableProduct() const	{
	vector<pair<string,string>> avecStmtPairs;
	string strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Products ( \
		ProductCode TEXT UNIQUE \
		ProductCategory TEXT \
		ProductName TEXT \
		ProductDescription TEXT \
		ProductShortDescription TEXT \
		ManufacturerID INTEGER UNIQUE \
		ManufacturerOrigin TEXT \
		ProductUnit TEXT \
		PricePerUnit TEXT \
		Quantity TEXT \
		TaxRate TEXT \
		Currency TEXT \
		ProductFrame TEXT \
		ProductImage TEXT \
		ProductSize TEXT \
		FOREIGN KEY (ManufacturerID) REFERENCES Manufacturer(ManufacturerID)";
	avecStmtPairs.push_back(make_pair("Products", strSQLFormat));

	strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Manufacturer ( \
		ManufacturerID INTEGER UNIQUE \
		ManufacturerName TEXT \
		ManufacturerAddress TEXT \
		ManufacturerOrigin TEXT \
		ManufacturerURL TEXT);";
	avecStmtPairs.push_back(make_pair("Manufacturer", strSQLFormat));
}

//-----------------------------------------------------------------------------

void ProductManager::productViewed(const Product & aProduct /*, User & aUser*/)	{

	//When a product is viewed, update the database
	string strSQLCommand;

	strSQLCommand = "UPDATE " /* + PRODUCT_TABLE + */ 
		"SET products_viewed = products_viewed+1"
		"WHERE products_id = '" /*+ GET_PRODUCT_ID + */ "'";

}

//-----------------------------------------------------------------------------