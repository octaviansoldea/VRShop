    #include <iostream>
    #include <string>
    #include <QString>
    
    #include <QObject>
  #include <QImageReader>
  
    #include "VRBasicQtOperations.h"
    
  #include "VRAppData.h"
  
    #include "VRRemoveProduct_GUI.h"
    #include "VRAddProduct_GUI.h"
    
    #include "VRAbstractObjectFactory.h"
    #include "VRAbstractGeomShape.h"
    
    #include "VRProductShopEditor.h"
    
    #include "BasicStringDefinitions.h"
    
    #include "VRDatabaseInterface.h"
    #include "VRDatabaseInterfaceShopEditor.h"
    
    #include "VRProductManager.h"
    
    using namespace VR;
    using namespace std;
    using namespace osg;
    
    //DatabaseInterface ProductManager::m_DIProductEditor(ProductManager::getDBParams());
    
    //-----------------------------------------------------------------------------
    
    ProductManager::ProductManager(QObject * apParent) : QObject(apParent), m_DIProductEditor(ProductManager::getDBParams()) {
    	m_pAddProduct_GUI = new AddProduct_GUI;
    	m_pAddProduct_GUI->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    	m_pAddProduct_GUI->setParent(0);
    
    	m_pgrpProductsRepresentation = new Group();
    	m_pgrpProductsRepresentation->setName("Products");
    
    	//Update combos
    	connect(m_pAddProduct_GUI->m_pComboBoxProductCategoryFromDB,
    		SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    	connect(m_pAddProduct_GUI->m_pComboBoxProductNameFromDB,
    		SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    	connect(m_pAddProduct_GUI->m_pComboBoxProductCodeFromDB,
    		SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    
    	connect(m_pAddProduct_GUI->m_pComboBoxFrame,
    		SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotBoxFrameChanged()));
    	connect(m_pAddProduct_GUI->m_pToolButtonSetTexture,SIGNAL(pressed()),this,SLOT(slotSelectTexture()));
    	connect(m_pAddProduct_GUI->m_pComboBoxImageSelect,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetTexture()));
    
    
    	ref_ptr<AbstractGeomShape> pAGS = dynamic_cast<AbstractGeomShape*>(AbstractObjectFactory::createAbstractObject("Plate3D").get());
    	OSGQT_Widget * pOSGQT_Widget = m_pAddProduct_GUI->m_pOSGQT_Widget;
    	pOSGQT_Widget->setSceneData(pAGS);
    }
    
    //-----------------------------------------------------------------------------
    
    ProductManager::~ProductManager()	{
    	delete m_pAddProduct_GUI;
    	
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
    	if (astrChildName.empty())	{
    		return 0;
    	}
    
    	int nSize = m_pgrpProductsRepresentation->getNumChildren();
    	int nI;
    
    	for (nI=0; nI<nSize; nI++)	{
    		const string & strChild = m_pgrpProductsRepresentation->getChild(nI)->getName();
    		if (strChild == astrChildName)	{
    			ref_ptr<AbstractObject> pChild = dynamic_cast<AbstractObject*>(m_pgrpProductsRepresentation->getChild(nI));
    			return pChild;
    		}
    	}
    	return 0;
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
    
    void ProductManager::addNewProduct()	{
    	//Fill product category ComboBox
    	list<string> lststrQuery = requestData(FILL_PRODUCT_CATEGORY,vector<string>(0));
    
    	list<string>::iterator it;
    	for (it = lststrQuery.begin(); it != lststrQuery.end(); it++)	{
    		m_pAddProduct_GUI->m_pComboBoxProductCategoryFromDB->addItem(it->c_str());
    		m_pAddProduct_GUI->m_pComboBoxProductCategory->addItem(it->c_str());
    	}
    
    	bool bRes = m_pAddProduct_GUI->exec();
    
    	if (bRes == false)	{
    		return;
    	}
    
    	//Check what type of operation is managed
    	bool bOperation = m_pAddProduct_GUI->m_pToolButtonFromDB->isChecked();
    
    	if (bOperation == true)	{	//Read product from DB
    		string strProductCode = m_pAddProduct_GUI->m_pComboBoxProductCodeFromDB->currentText().toStdString();
    
    		vector<string> vecstrProductMgrParams;
    		vecstrProductMgrParams.push_back(strProductCode);
    		list<string> lststrQueryProduct = requestData(PRODUCT_FROM_DB,vecstrProductMgrParams);
    
    		ProductShopEditor * pProductShopEditor = new ProductShopEditor(lststrQueryProduct.front());			
    		pProductShopEditor->createRepresentation("Plate3D");
    
    		ref_ptr<AbstractGeomShape> pProductGraphics = (AbstractGeomShape*)(pProductShopEditor->getRepresentation().get());
    
    		if (pProductGraphics==0)	{
    			delete pProductShopEditor;
    			return;
    		}
    
    		pProductGraphics->setName(tostr(pProductShopEditor->getProductCode()));
    		pProductGraphics->setScaling(1.0, 0.1, 1.0);
    		pProductGraphics->setTexture(pProductShopEditor->getTexture());
    
    		addNewProduct(pProductShopEditor);
    	} else {	//Insert product into the DB and the scene
    		ProductShopEditor * pProductShopEditor = new ProductShopEditor();
    		ProductShopEditorParams productParams = initProduct();
    
    		pProductShopEditor->setParams(productParams);
    
    		//Insert product to database of products
    		databaseRequest(pProductShopEditor,ProductManager::INSERT_PRODUCT);
    
    		pProductShopEditor->createRepresentation("Plate3D");
    		ref_ptr<AbstractGeomShape> pProductGraphics = (AbstractGeomShape*)(pProductShopEditor->getRepresentation().get());
    
    		if (pProductGraphics==0)	{
    			delete pProductShopEditor;
    			return;
    		}
    
    		pProductGraphics->setName(tostr(pProductShopEditor->getProductCode()));
    		pProductGraphics->setScaling(1.0, 0.01, 1.0);
    		pProductGraphics->setTexture(pProductShopEditor->getTexture());
    
    		addNewProduct(pProductShopEditor);
    	}
    }
    
    //-----------------------------------------------------------------------------
    
    void ProductManager::productMoreSettings(const string & astrProductCode)	{
    	//Browse data of the product from DB and initialize the GUI
    	vector<string> vecstrProductMgrParams;
    	vecstrProductMgrParams.push_back(astrProductCode);
    	list<string> lststrQueryProduct = requestData(PRODUCT_FROM_DB,vecstrProductMgrParams);
    
    	vector<string> vecstrProductData = splitString(lststrQueryProduct.front(),";");
    	vector<string>::iterator it = vecstrProductData.begin();
    
    	m_pAddProduct_GUI->m_pComboBoxProductCategory->addItem((it+1)->c_str());
    	m_pAddProduct_GUI->m_pLineEditProductName->setText((it+2)->c_str());
    	m_pAddProduct_GUI->m_pLineEditProductCode->setText((it+3)->c_str());
    	m_pAddProduct_GUI->m_pLineEditShortDescription->setText((it+4)->c_str());
    	m_pAddProduct_GUI->m_pTextEditProductDescription->setText((it+5)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxProducer->addItem((it+6)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxPlaceOfOrigin->addItem((it+7)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxProductUnit->addItem((it+8)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxUnitQuantity->addItem((it+9)->c_str());
    	m_pAddProduct_GUI->m_pLineEditQuantity->setText((it+10)->c_str());
    	m_pAddProduct_GUI->m_pLineEditPrice->setText((it+11)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxTaxRate->findText((it+12)->c_str());
    	m_pAddProduct_GUI->m_pComboBoxImageSelect->addItem((it+16)->c_str());
    
    	float flX = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeX->value();
    	float flY = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeY->value();
    	float flZ = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeZ->value();
    
    	const string strTextureName = *(it+16);
    
    	setActiveWidget(MODIFY_PRODUCT);
    
    	ref_ptr<AbstractGeomShape> pAGS = dynamic_cast<AbstractGeomShape*>(AbstractObjectFactory::createAbstractObject("Plate3D").get());
    
    	pAGS->setScaling(flX,flY,flZ);
    	pAGS->setTexture(strTextureName);
    
    	OSGQT_Widget * pOSGQT_Widget = m_pAddProduct_GUI->m_pOSGQT_Widget;
    	Group * pSceneData = (Group*)pOSGQT_Widget->getSceneData();
    	pSceneData->addChild(pAGS);
    
    	int nRes = m_pAddProduct_GUI->exec();
    	if(nRes == QDialog::Accepted)	{
    		//Save changes done
    		ProductShopEditorParams productParams = initProduct();
    
    		ProductShopEditor product;
    		product.setParams(productParams);
    
    		databaseRequest(&product,ProductManager::MODIFY_PRODUCT);
    	}
    
    	pSceneData->removeChildren(0, pSceneData->getNumChildren()-1);	//Deletes pointer as well
    }
    
    //-----------------------------------------------------------------------------
    
    void ProductManager::addNewProduct(ProductShopEditor * apProductShopEditor)	{
    	ProductShopEditor * pProductShopEditor = (ProductShopEditor*)(apProductShopEditor);
    	if (pProductShopEditor != 0)	{
    		m_lstProducts.push_back(pProductShopEditor);
    
    		//Fill osg group whose pointer is sent to the scene 
    		//with the 3D representation of the product
    		ref_ptr<AbstractObject> pProd = pProductShopEditor->getRepresentation();
    		
    		m_pgrpProductsRepresentation->addChild(pProd);
    	}
    }
    
    //-----------------------------------------------------------------------------
    
    bool ProductManager::removeProduct(const string & astrProductCode)	{	
    
    	vector<string> vecstrProductMgrParams;
    	vecstrProductMgrParams.push_back(astrProductCode);
    	list<string> lststrQuery = requestData(REMOVE_PRODUCT,vecstrProductMgrParams);
    
    	if (lststrQuery.size() == 0)	{
    		return false;
    	}
    
    	vector<string> vecstrResult = splitString(lststrQuery.front(),";");
    	vector<string>::iterator it = vecstrResult.begin();
    
    	string strProductCategory = *it;
    	string strProductName = *(it+1);
    	string strProductCode = *(it+2);
    	const string strProductTexture = *(it+3);
    
    	RemoveProduct_GUI removeProduct_GUI;
    	removeProduct_GUI.setWindowFlags(Qt::FramelessWindowHint);
    
    	removeProduct_GUI.m_pComboBoxCategory->addItem(strProductCategory.c_str());
    	removeProduct_GUI.m_pComboBoxProduct->addItem(strProductName.c_str());
    	removeProduct_GUI.m_pComboBoxID->addItem(tostr(strProductCode).c_str());
    
    	ref_ptr<AbstractGeomShape> pAGS = dynamic_cast<AbstractGeomShape*>(AbstractObjectFactory::createAbstractObject("Plate3D").get());
    	
    	pAGS->setScaling(1,0.01,1);
    	pAGS->setTexture(strProductTexture);
    
    	OSGQT_Widget * pOSGQT_Widget = removeProduct_GUI.m_pOSGQT_Widget;
    	pOSGQT_Widget->setSceneData(pAGS);
    
    	int nRes = removeProduct_GUI.exec();
    
    	return nRes;
    }
    
    //-----------------------------------------------------------------------------
    
    void ProductManager::removeProduct(ProductShopEditor * apProductShopEditor)	{
    	//remove 3D
    	m_pgrpProductsRepresentation->removeChild(apProductShopEditor->getRepresentation());
    
    	//Remove from the vector of products
    	m_lstProducts.erase(remove(m_lstProducts.begin(), m_lstProducts.end(), apProductShopEditor),
    		m_lstProducts.end());
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
    
    	int nJ;
    	int nSize = m_pgrpProductsRepresentation->getNumChildren();
    	for (nJ = 0; nJ < nSize; nJ++)	{
    		ref_ptr<AbstractObject> pChild = dynamic_cast<AbstractObject*>(m_pgrpProductsRepresentation->getChild(nJ));
    
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
    
    		ref_ptr<AbstractObject> pAOChild = AbstractObjectFactory::createAbstractObject(strClass);
    		pAOChild->initFromSQLData(vecstrSqlDataLine);
    
    		pAOChild->setName(strObject);
    		pAOChild->setIsTargetPick(true);
    
    		m_pgrpProductsRepresentation->addChild(pAOChild);
    	}
    }
    
    //-----------------------------------------------------------------------------
    
    DatabaseInterfaceParams ProductManager::getDBParams()	{
    	DatabaseInterfaceParams dbParams;
    	dbParams.m_qstrConnectionName = "Product";
    	dbParams.m_qstrDBName = getDatabaseName().c_str();
    
    	return dbParams;
    }
    
    //------------------------------------------------------------------------------
    
    string ProductManager::getTableName()	{
    	return "Product";
    }
    
    //------------------------------------------------------------------------------
    
    string ProductManager::getDatabaseName()	{
  	return AppData::getFPathDatabases() + "/Products.db";
    }
    
    //------------------------------------------------------------------------------
    
    DatabaseInterface * ProductManager::getDatabaseInterface() {
    	return(&m_DIProductEditor);
    }
    
    //------------------------------------------------------------------------------
    
    void ProductManager::databaseRequest(ProductShopEditor * apProductShopEditor, ProductManager::OperationType aenumOperationType)	{
    	string strSqlQuery = "";
    
    	ProductShopEditorParams productParams;
    	apProductShopEditor->getParams(productParams);
    
    	switch (aenumOperationType)	{
    	case INSERT_PRODUCT:
    		{
    			strSqlQuery +=	"INSERT INTO Product (ProductCategory,ProductName,ProductCode,ProductShortDescription, "
    				"ProductDescription,ProductManufacturerName,ProductManufacturerOrigin,ProductUnit, "
    				"ProductUnitMeasure,ProductQuantity,ProductPricePerUnit,ProductTaxRate, "
    				"ProductCurrency,ProductDateAdded,ProductDateLastModified,ProductTextureFile) VALUES('";
    			
    			string strValues = productParams.m_strProductCategory + "','" +
    			productParams.m_strProductName + "','" + 
    			tostr(productParams.m_ulProductCode) + "','" +
    			productParams.m_strProductShortDescription + "','" +
    			productParams.m_strProductDescription + "','" +
    			productParams.m_strManufacturerName + "','" +
    			productParams.m_strManufacturerOrigin + "','" +
    			productParams.m_strProductUnit + "','" +
    			productParams.m_strProductUnitMeasure + "','" +
    			tostr(productParams.m_flQuantity) + "','" +
    			tostr(productParams.m_flPricePerUnit) + "','" +
    			tostr(productParams.m_flTaxRate) + "','" +
    			productParams.m_strCurrency + "','" +
    			productParams.m_strProductDateAdded + "','" +
    			productParams.m_strProductDateLastModified + "','" +
    			productParams.m_strTextureFile + "');";
    
    			strSqlQuery += strValues;
    
    			break;
    		}
    	case MODIFY_PRODUCT:
    		{
    			strSqlQuery = "UPDATE Product SET "
    			"ProductCategory = '" + productParams.m_strProductCategory + "'"
    			", ProductName = '" + productParams.m_strProductName + "'"
    			", ProductCode = '" + tostr(productParams.m_ulProductCode) + "'"
    			", ProductShortDescription = '" + productParams.m_strProductShortDescription + "'"
    			", ProductDescription = '" + productParams.m_strProductDescription + "'"
    			", ProductManufacturerName = '" + productParams.m_strManufacturerName + "'"
    			", ProductManufacturerOrigin = '" + productParams.m_strManufacturerOrigin + "'"
    			", ProductUnit = '" + productParams.m_strProductUnit + "'"
    			", ProductUnitMeasure = '" + productParams.m_strProductUnitMeasure + "'"
    			", ProductQuantity = '" + tostr(productParams.m_flQuantity) + "'"
    			", ProductPricePerUnit = '" + tostr(productParams.m_flPricePerUnit) + "'"
    			", ProductTaxRate = '" + tostr(productParams.m_flTaxRate) + "'"
    			", ProductCurrency = '" + productParams.m_strCurrency + "'"
    			", ProductDateAdded = '" + productParams.m_strProductDateAdded + "'"
    			", ProductDateLastModified = '" + productParams.m_strProductDateLastModified + "'"
    			", ProductTextureFile = '" + productParams.m_strTextureFile + "'"
    			" WHERE ProductCode = '" + tostr(productParams.m_ulProductCode) + "'";
    
    			break;
    		}
    	default:
    		{
    			break;
    		}
    	}
    
    	DatabaseInterface *pDI = getDatabaseInterface();
    	pDI->executeAndGetResult(strSqlQuery);
    }
    
    //------------------------------------------------------------------------------
    
    vector<pair<string,string>> ProductManager::getDBElements()	{
    	vector<pair<string,string>> vecpairDBElements;
    
    	vecpairDBElements.push_back(make_pair("ProductID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
    	vecpairDBElements.push_back(make_pair("ProductCategory", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductName", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductCode", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductShortDescription", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductDescription", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductManufacturerName", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductManufacturerOrigin", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductUnit", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductUnitMeasure", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductQuantity", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductPricePerUnit", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductTaxRate", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductCurrency", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductDateAdded", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductDateLastModified", "TEXT"));
    	vecpairDBElements.push_back(make_pair("ProductTextureFile", "TEXT"));
    
    	return vecpairDBElements;
    }
    
    //------------------------------------------------------------------------------
    
    void ProductManager::createProductDB() {
    	DatabaseInterfaceShopEditorParams dbParams;
    	dbParams.m_qstrDBName = this->getDatabaseName().c_str();
    	DatabaseInterfaceShopEditor dbInterface(dbParams);
    
    	dbInterface.createTable(getTableName(), getDBElements());
    }
    
    //------------------------------------------------------------------------------
    
    void ProductManager::slotUpdateCombo()	{
    	QComboBox * pComboBox = (QComboBox *)sender();
    	QString qstrObjectName = pComboBox->objectName();
    
    	if (qstrObjectName == m_pAddProduct_GUI->m_pComboBoxProductCategoryFromDB->objectName())	{
    		vector<string> vecstrProductMgrParams;
    		vecstrProductMgrParams.push_back(pComboBox->currentText().toStdString());
    		list<string> lststrQuery = requestData(PRODUCT_NAME_CODE_REQUEST,vecstrProductMgrParams);
    
    		QComboBox * pProductName = m_pAddProduct_GUI->m_pComboBoxProductNameFromDB;
    		QComboBox * pProductCode = m_pAddProduct_GUI->m_pComboBoxProductCodeFromDB;
    
    		disconnect(pProductName,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    		disconnect(pProductCode,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    
    		pProductName->clear();
    		pProductCode->clear();
    
    		list<string>::iterator it;
    		
    		for (it = lststrQuery.begin(); it != lststrQuery.end(); it++)	{
    			vector<string> vecstrResultLine = splitString(*it,";");
    			pProductName->addItem(vecstrResultLine[0].c_str());
    			pProductCode->addItem(vecstrResultLine[1].c_str());
    		}
    		
    		connect(pProductName,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    		connect(pProductCode,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotUpdateCombo()));
    	} else if (qstrObjectName == m_pAddProduct_GUI->m_pComboBoxProductNameFromDB->objectName())	{
    		int nComboBoxPos = pComboBox->currentIndex();
    
    		QComboBox * pProductCode = m_pAddProduct_GUI->m_pComboBoxProductCodeFromDB;
    		pProductCode->setCurrentIndex(nComboBoxPos);
    	} else if (qstrObjectName == m_pAddProduct_GUI->m_pComboBoxProductCodeFromDB->objectName())	{
    		int nComboBoxPos = pComboBox->currentIndex();
    
    		QComboBox * pProductName = m_pAddProduct_GUI->m_pComboBoxProductNameFromDB;
    		pProductName->setCurrentIndex(nComboBoxPos);
    	}
    }
    
    //----------------------------------------------------------------------------
    
    void ProductManager::setActiveWidget(const OperationType & aenumOperationType)	{
    	switch (aenumOperationType)	{
    	case NEW_PRODUCT_INSERT:
    	case MODIFY_PRODUCT:
    		{
    			m_pAddProduct_GUI->m_pToolButtonFromDB->setChecked(false);
    			m_pAddProduct_GUI->m_pToolButtonNew->setChecked(true);
    
    			m_pAddProduct_GUI->m_pFrameFromDB->setVisible(false);
    			m_pAddProduct_GUI->m_pScrollAreaNewProduct->setVisible(false);
    			m_pAddProduct_GUI->m_pScrollAreaNewProduct->setVisible(true);
    
    			break;
    		}
    	case PRODUCT_FROM_DB:
    	default:
    		{
    			m_pAddProduct_GUI->m_pToolButtonFromDB->setChecked(true);
    			m_pAddProduct_GUI->m_pToolButtonNew->setChecked(false);
    
    			m_pAddProduct_GUI->m_pFrameFromDB->setVisible(false);
    			m_pAddProduct_GUI->m_pScrollAreaNewProduct->setVisible(false);
    			m_pAddProduct_GUI->m_pFrameFromDB->setVisible(true);
    
    			break;
    		}
    	}
    }
    
    //----------------------------------------------------------------------------
    
    void ProductManager::slotBoxFrameChanged()	{
    	string strFrameName = m_pAddProduct_GUI->m_pComboBoxFrame->currentText().toStdString();
    	string strTextureFile = m_pAddProduct_GUI->m_pComboBoxImageSelect->currentText().toStdString();
    
    	float flX = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeX->value();
    	float flY = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeY->value();
    	float flZ = m_pAddProduct_GUI->m_pDoubleSpinBoxSizeZ->value();
    
    	ref_ptr<AbstractGeomShape> pAGS = dynamic_cast<AbstractGeomShape*>(AbstractObjectFactory::createAbstractObject(strFrameName).get());
    
    	pAGS->setScaling(flX,flY,flZ);
    	pAGS->setTexture(strTextureFile);
    
    	OSGQT_Widget * pOSGQT_Widget = m_pAddProduct_GUI->m_pOSGQT_Widget;
    	Group * pSceneData = (Group*)pOSGQT_Widget->getSceneData();
    	pSceneData->removeChild((unsigned int)0);
    	pSceneData->addChild(pAGS);
    }
    
    //----------------------------------------------------------------------------
    
    ProductShopEditorParams ProductManager::initProduct()	{
    	ProductShopEditorParams productParams;
    	productParams.m_strProductCategory = m_pAddProduct_GUI->m_pComboBoxProductCategory->currentText().toStdString();
    	productParams.m_strProductName = m_pAddProduct_GUI->m_pLineEditProductName->text().toStdString();
    	productParams.m_ulProductCode = m_pAddProduct_GUI->m_pLineEditProductCode->text().toULong();
    	productParams.m_strProductShortDescription = m_pAddProduct_GUI->m_pLineEditShortDescription->text().toStdString();
    	productParams.m_strProductDescription = m_pAddProduct_GUI->m_pTextEditProductDescription->toPlainText().toStdString();
    	productParams.m_strManufacturerName = m_pAddProduct_GUI->m_pComboBoxProducer->currentText().toStdString();
    	productParams.m_strManufacturerOrigin = m_pAddProduct_GUI->m_pComboBoxPlaceOfOrigin->currentText().toStdString();
    	productParams.m_strProductDateAdded = m_pAddProduct_GUI->m_pLineEditPriceLastChanged->text().toStdString();
    	productParams.m_strProductDateLastModified = m_pAddProduct_GUI->m_pLineEditPriceLastChanged->text().toStdString();
    	productParams.m_strProductUnit = m_pAddProduct_GUI->m_pComboBoxProductUnit->currentText().toStdString();
    	productParams.m_flPricePerUnit = m_pAddProduct_GUI->m_pLineEditPrice->text().toFloat();
    	productParams.m_flQuantity = m_pAddProduct_GUI->m_pLineEditQuantity->text().toFloat();
    	productParams.m_flTaxRate = m_pAddProduct_GUI->m_pComboBoxTaxRate->currentText().remove("%").toFloat();
    	productParams.m_strCurrency = "EUR";
    	productParams.m_strTextureFile = m_pAddProduct_GUI->m_pComboBoxImageSelect->currentText().toStdString();
    
    	return productParams;
    }
    
    //----------------------------------------------------------------------------
    
    list<string> ProductManager::requestData(const ProductManager::OperationType & aenumOperationType, vector<string> & avecstrProductMgrParams)	{
    	string strSqlQuery;
    	vector<string>::iterator it = avecstrProductMgrParams.begin();
    
    	switch (aenumOperationType)	{
    	case PRODUCT_QUANTITY_PRICE_REQUEST:
    		{
    			strSqlQuery = 
    				"SELECT ProductQuantity,ProductPricePerUnit FROM Product WHERE ProductCode = '" + 
    				*it + "'";
    
    			break;
    		}
    	case MODIFY_QUANTITY_PRICE:
    		{
    			strSqlQuery = 
    				"UPDATE Product SET "
    					"ProductQuantity = '" + (*it) + "' , "
    					"ProductPricePerUnit = '" + *(it+1) + "'"
    				" WHERE ProductCode = '" + *(it+2) + "'";
    
    			break;
    		}
    	case PRODUCT_FROM_DB:
    		{
    			strSqlQuery = "SELECT * FROM Product WHERE ProductCode = '" + 
    				*it + "'";
    			break;
    		}
    	case REMOVE_PRODUCT:
    		{
    			strSqlQuery = "SELECT ProductCategory, ProductName, ProductCode, ProductTextureFile FROM Product WHERE ProductCode = '" 
    				+ *it + "'";
    
    			break;
    		}
    	case PRODUCT_NAME_CODE_REQUEST:
    		{
    			strSqlQuery = "SELECT ProductName,ProductCode FROM Product WHERE ProductCategory = '" +
    				*it + "'";
    
    			break;
    		}
    	case FILL_PRODUCT_CATEGORY:
    		{
    			strSqlQuery = "SELECT DISTINCT ProductCategory FROM Product WHERE TRIM(ProductCategory) > ''";
    
    			break;
    		}		
    	default:
    		break;
    	}
    
    	DatabaseInterface *pDI = getDatabaseInterface();
    	list<string> lststrReceivedData;
    
    	lststrReceivedData = pDI->executeAndGetResult(strSqlQuery);
    
    	if (lststrReceivedData.empty())	{
    		return ((list<string>)0);
    	}
    	return lststrReceivedData;
    }
    
    //----------------------------------------------------------------------------
    
    void ProductManager::slotSetTexture()	{
    	QString qstrTextureFile = m_pAddProduct_GUI->m_pComboBoxImageSelect->currentText();
    
    	QImageReader image(qstrTextureFile);
    	QPixmap imageBasic(QPixmap::fromImageReader(&image));
    	QLabel * pImageLabel = m_pAddProduct_GUI->m_pLabelTexture;
    	QPixmap imageScaled(imageBasic.scaled(
    		pImageLabel->width(),
    		pImageLabel->height(),
    		Qt::IgnoreAspectRatio,
    		Qt::SmoothTransformation)
    		);
    	pImageLabel->setPixmap(imageScaled);
    
    	OSGQT_Widget * pOSGQT_Widget = m_pAddProduct_GUI->m_pOSGQT_Widget;
    	ref_ptr<AbstractGeomShape> pAGS = (AbstractGeomShape*)pOSGQT_Widget->getSceneData();
    	pAGS->setTexture(qstrTextureFile.toStdString());
    }
    
    //----------------------------------------------------------------------------
    
    void ProductManager::slotSelectTexture()	{
    	string strFileName = BasicQtOperations::openSaveDialog("*.bmp", m_pAddProduct_GUI);
    
    	if (strFileName.empty())	{
    		return;
    	}
    
    	m_pAddProduct_GUI->m_pComboBoxImageSelect->addItem(strFileName.c_str());
    }

