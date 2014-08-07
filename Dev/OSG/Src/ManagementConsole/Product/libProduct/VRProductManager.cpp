#include <iostream>
#include <string>

#include "VRProductController.h"

#include "VRProductSettings_GUI.h"
#include "VRRemoveProduct_GUI.h"

#include "VRAbstractGeomShape.h"

#include "VRProductShopEditor.h"

#include "BasicStringDefinitions.h"

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
	//if (m_pProductSettings_GUI !=0)
	//	delete m_pProductSettings_GUI;
	if (m_pRemoveProduct_GUI != 0)
		delete m_pRemoveProduct_GUI;

	list<ProductShopEditor*>::iterator it = m_lstProducts.begin();
	for(it; it != m_lstProducts.end(); ++it)	{
		ProductShopEditor * pProductShopEditor = (ProductShopEditor*)(*it);
		delete pProductShopEditor;
		pProductShopEditor = 0;
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
	AbstractObject * pChild = 0;
	if (astrChildName.empty())	{
		return pChild;
	}

	int nSize = m_pgrpProductsRepresentation->getNumChildren();
	int nI;

	for (nI=0; nI<nSize; nI++)	{
		const string & strChild = m_pgrpProductsRepresentation->getChild(nI)->getName();
		if (strChild == astrChildName)	{
			pChild = dynamic_cast<AbstractObject*>(m_pgrpProductsRepresentation->getChild(nI));

			return pChild;
		}
	}
	return pChild;
}

//-----------------------------------------------------------------------------

ProductShopEditor * ProductManager::getProduct(const AbstractObject * apAbstractObject)	{
	if (apAbstractObject == NULL)
		return 0;

	list<ProductShopEditor*>::iterator it;
	for (it = m_lstProducts.begin(); it != m_lstProducts.end(); it++)	{
		if ((*it)->getRepresentation() == apAbstractObject)	{
			return *it;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------

void ProductManager::addNewProduct(ProductShopEditor * apProductShopEditor)	{
	ProductShopEditor * pProductShopEditor = dynamic_cast<ProductShopEditor*>(apProductShopEditor);
	if (pProductShopEditor != 0)	{
		m_lstProducts.push_back(pProductShopEditor);

		//Fill osg group whose pointer is sent to the scene 
		//with the 3D representation of the product
		ref_ptr<AbstractObject> pProd = pProductShopEditor->getRepresentation();
		m_pgrpProductsRepresentation->addChild(pProd);
	}
}

//-----------------------------------------------------------------------------

void ProductManager::addNewProduct()	{
	ProductShopEditor * pProductShopEditor = new ProductShopEditor();
	bool bRes = modifyProduct(pProductShopEditor);

	if (bRes == false)	{
		delete pProductShopEditor;
		return;
	}

	m_lstProducts.push_back(pProductShopEditor);

	float flScaleX = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeX->value();
	float flScaleY = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeY->value();
	float flScaleZ = m_pProductSettings_GUI->m_pDoubleSpinBoxSizeZ->value();
	string strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
	string strTexture = m_pProductSettings_GUI->getTexture();

	delete m_pProductSettings_GUI;

	//Fill osg group whose pointer is sent to the scene 
	//with the 3D representation of the product
//	ref_ptr<AbstractObject> pProductGraphics = pProductShopEditor->getRepresentation();
	ref_ptr<AbstractGeomShape> pProductGraphics = dynamic_cast<AbstractGeomShape*>(pProductShopEditor->getRepresentation().get());

	if (pProductGraphics==0)
		return;

	pProductGraphics->setName(strProductName);
	pProductGraphics->setScaling(flScaleX, flScaleY, flScaleZ);
	pProductGraphics->setTexture(strTexture);

	m_pgrpProductsRepresentation->addChild(pProductGraphics);
}

//-----------------------------------------------------------------------------

void ProductManager::removeProduct(ProductShopEditor * apProductShopEditor)	{

	m_pRemoveProduct_GUI = new RemoveProduct_GUI(apProductShopEditor);
	m_pRemoveProduct_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pRemoveProduct_GUI->exec();

	if (bRes == QDialog::Accepted)	{	//Remove product confirmed
		m_pgrpProductsRepresentation->removeChild(apProductShopEditor->getRepresentation());	//remove 3D
		m_lstProducts.erase(remove(m_lstProducts.begin(), m_lstProducts.end(), apProductShopEditor),
			m_lstProducts.end());	//Remove from the vector of products
	}

	delete m_pRemoveProduct_GUI;
}

//-----------------------------------------------------------------------------

bool ProductManager::modifyProduct(ProductShopEditor * apProductShopEditor)	{
	m_pProductSettings_GUI = new ProductSettings_GUI(apProductShopEditor);

	m_pProductSettings_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = m_pProductSettings_GUI->exec();

	//If SAVE is clicked in the PROD.SETTINGS_GUI
	if (bRes == QDialog::Accepted)	{
		//Fill vector of products

		ProductShopEditorParams productParams;
		apProductShopEditor->getParams(productParams);
/*
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_strProductCategory = m_pProductSettings_GUI->m_pComboBoxProductCategory->currentText().toStdString();
		productParams.m_strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
		productParams.m_nProductCode = m_pProductSettings_GUI->m_pLineEditProductCode->text().toInt();
		productParams.m_strProductDescription = m_pProductSettings_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
		productParams.m_strProductShortDescription = m_pProductSettings_GUI->m_pLineEditShortDescription->text().toStdString();

		productParams.m_strProductUnit = m_pProductSettings_GUI->m_pComboBoxProductUnit->currentText().toStdString();
		productParams.m_flPricePerUnit = m_pProductSettings_GUI->m_pLineEditPrice->text().toFloat();
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_flTaxRate = m_pProductSettings_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
*/

		productParams.m_strProductCategory = m_pProductSettings_GUI->m_pComboBoxProductCategory->currentText().toStdString();
		productParams.m_strProductName = m_pProductSettings_GUI->m_pLineEditProductName->text().toStdString();
		productParams.m_nProductCode = m_pProductSettings_GUI->m_pLineEditProductCode->text().toInt();
		productParams.m_strProductShortDescription = m_pProductSettings_GUI->m_pLineEditShortDescription->text().toStdString();
		productParams.m_strProductDescription = m_pProductSettings_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
		productParams.m_strManufacturerName = m_pProductSettings_GUI->m_pComboBoxProducer->currentText().toStdString();
		productParams.m_strManufacturerOrigin = m_pProductSettings_GUI->m_pComboBoxPlaceOfOrigin->currentText().toStdString();
		productParams.m_strProductDateAdded = m_pProductSettings_GUI->m_pLineEditPriceLastChanged->text().toStdString();
		productParams.m_strProductDateLastModified = m_pProductSettings_GUI->m_pLineEditPriceLastChanged->text().toStdString();
		productParams.m_strProductUnit = m_pProductSettings_GUI->m_pComboBoxProductUnit->currentText().toStdString();
		productParams.m_flPricePerUnit = m_pProductSettings_GUI->m_pLineEditPrice->text().toFloat();
		productParams.m_flQuantity = m_pProductSettings_GUI->m_pLineEditQuantity->text().toFloat();
		productParams.m_flTaxRate = m_pProductSettings_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
		productParams.m_strCurrency = "EUR";
		productParams.m_strTextureFile = m_pProductSettings_GUI->getTexture();

		apProductShopEditor->setParams(productParams);
	} else {
		bRes = false;

		delete m_pProductSettings_GUI;
	}

	return bRes;
}

//-----------------------------------------------------------------------------

void ProductManager::preparedObjectData(vector<string> &avecItems, string & astrParent)	{
	vector<string> * pvecItems = &avecItems;

	int nI=1;

	string strClassName = "ProductDisplay";
	const string * pstrObjectName = &m_pgrpProductsRepresentation->getName();
	string strItem = (string(2*nI,' ') + strClassName + ";" + *pstrObjectName + ";;;");
	pvecItems->push_back(strItem);

	nI += 1;	//enlarge indent by 1 unit

	AbstractObject * pChild = 0;
	int nJ;
	int nSize = m_pgrpProductsRepresentation->getNumChildren();
	for (nJ = 0; nJ < nSize; nJ++)	{
		pChild = dynamic_cast<AbstractObject*>(m_pgrpProductsRepresentation->getChild(nJ));

		if(pChild == NULL)	{
			break;
		}

		string strClassNameChild = pChild->className();
		string strObjectNameChild = pChild->getName();
		strItem = (strClassNameChild + ";" + strObjectNameChild + ";" + pChild->prepareRowData(strClassName));

		pvecItems->push_back(string(2*nI,' ') + strItem);
	}
}

//-----------------------------------------------------------------------------

void ProductManager::initFromSQLData(vector<string> & avecstrSQLData)	{
//**********************************************
//	HIERARCHY (how you get data inside)
//		OBJECT1				Layer: 0
//			|--PRIMITIVE1	Layer: 1
//			|--PRIMITIVE2	Layer: 1
//*******************************************/

	int nNoOfElements = avecstrSQLData.size();
	int nPos;	//Position of the indent

	vector<string> vecstrSqlDataLine;
	vector<string>::iterator it = avecstrSQLData.begin();
	for (it; it != avecstrSQLData.end(); it++)	{
		nPos = 0;

		//Find the position of the first character & clear empty spaces
		nPos = it->find_first_not_of(" ");
		int nFindPos = it->find_first_of(";");	//This one deletes ID number
		it->erase(0,nFindPos+1);

		vecstrSqlDataLine = splitString(*it,";");

		//Layer determines Parent/Child relations
		nPos = nPos/2;	//Divided with 2 because 2 is the layer indent

		if (nPos == 0)	{
			continue;
		}

		string strClass = vecstrSqlDataLine[0];
		string strObject = vecstrSqlDataLine[1];

		ref_ptr<AbstractObject> pAOChild = 0;

		pAOChild = AbstractObject::createInstance(strClass);
		pAOChild->initFromSQLData(vecstrSqlDataLine);

		pAOChild->setName(strObject);
		pAOChild->setIsTargetPick(true);

		m_pgrpProductsRepresentation->addChild(pAOChild);
	}
}

//-----------------------------------------------------------------------------

void ProductManager::prepareProductsData(vector<string> &avecProducts)	{
	std::list<ProductShopEditor*>::iterator it = m_lstProducts.begin();
	for (it; it != m_lstProducts.end(); it++)	{
		string strProductData = (*it)->prepareRowData();
		avecProducts.push_back(strProductData);
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

void ProductManager::productViewed(const ProductShopEditor & aProductShopEditor /*, User & aUser*/)	{

	//When a product is viewed, update the database
	string strSQLCommand;

	strSQLCommand = "UPDATE " /* + PRODUCT_TABLE + */ 
		"SET products_viewed = products_viewed+1"
		"WHERE products_id = '" /*+ GET_PRODUCT_ID + */ "'";

}

//-----------------------------------------------------------------------------