#include "BasicStringDefinitions.h"
#include <string>

#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>

#include <QFileDialog>
#include <QMessageBox>

#include "VRShopBuilder.h"
#include "VRScene.h"

#include "VRCameraController.h"
#include "VRPickAndDragController.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"
#include "VRPickAndDragHandlerShopEditor.h"
#include "VRSceneObjectsSearchShopEditor.h"

#include "VRDataStructureModel.h"

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI()	{
	setupUi(this);

	setWindowTitle("ShopBuilder");

	m_pShopBuilder = new ShopBuilder(m_pOSGQTWidget);
	ref_ptr<Scene> pScene = m_pShopBuilder->getScene();
	string strFileName = m_pShopBuilder->getCurrentFileName();

	ref_ptr<KeyboardMouseManipulatorShopEditor> pKeyboardMouseManipulatorShopEditor = 
		(KeyboardMouseManipulatorShopEditor *)(m_pOSGQTWidget->getCameraManipulator());

	try{
		typeid(*pKeyboardMouseManipulatorShopEditor);

		m_pCameraController = new CameraController(
			m_p_ComboBox_PredefinedViewport,
			m_p_DoubleSpinBox_CameraPositionX,
			m_p_DoubleSpinBox_CameraPositionY,
			m_p_DoubleSpinBox_CameraPositionZ,
			m_p_PushButton_SetCameraPositionDefault,
			m_p_PushButton_CameraPosition,
			m_p_DoubleSpinBox_CameraHeadingDirectionX,
			m_p_DoubleSpinBox_CameraHeadingDirectionY,
			m_p_DoubleSpinBox_CameraHeadingDirectionZ,
			m_p_PushButton_SetCameraHeadingDirectionDefault,
			m_p_PushButton_CameraHeadingDirection,
			pKeyboardMouseManipulatorShopEditor);
		m_pCameraController->slotUpdateCameraGUI();

	} catch(std::bad_typeid & bt) {
		m_pCameraController = 0;
		cerr << bt.what() << endl;
	}

	ref_ptr<PickAndDragHandlerShopEditor> pPickAndDragHandlerShopEditor = m_pShopBuilder->getPicker();

	m_pPickAndDragController = new PickAndDragController(
		m_p_DoubleSpinBox_TranslationX,
		m_p_DoubleSpinBox_TranslationY,
		m_p_DoubleSpinBox_TranslationZ,
		m_p_DoubleSpinBox_ScalingX,
		m_p_DoubleSpinBox_ScalingY,
		m_p_DoubleSpinBox_ScalingZ,
		m_p_DoubleSpinBox_RotationX,
		m_p_DoubleSpinBox_RotationY,
		m_p_DoubleSpinBox_RotationZ,
		m_p_ComboBox_DirectionOfTranslation,
		m_p_ComboBox_TranslateRelativeTo,
		pPickAndDragHandlerShopEditor);


	m_pOSGQTWidget->show();

	buildConnections();

	connect(pPickAndDragHandlerShopEditor,SIGNAL(signalProductPicked(const std::string &)),
		this,SLOT(slotProductClicked(const std::string &))
	);
}

//=========================================================================================

ShopBuilder_GUI::~ShopBuilder_GUI() {
	delete m_pCameraController;
	delete m_pPickAndDragController;

	delete m_pShopBuilder;
}

//=========================================================================================

void ShopBuilder_GUI::buildConnections() {
	connect(actionNew, SIGNAL(triggered()), this, SLOT(slotNewProject()));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenDB()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSaveDB()));
	connect(actionSave_As, SIGNAL(triggered()), this, SLOT(slotSaveAsDB()));
	connect(actionClose, SIGNAL(triggered()), this, SLOT(slotCloseDB()));

	connect(m_p_LineEdit_Search,SIGNAL(returnPressed()), this,SLOT(slotSearchScene()));
	connect(m_p_ToolButton_Search,SIGNAL(pressed()), this,SLOT(slotSearchScene()));
	connect(m_pListView,SIGNAL(clicked(const QModelIndex &)), this,SLOT(slotItemClicked(const QModelIndex &)));

	connect(m_p_ToolButton_GridOnOff, SIGNAL(toggled(bool)),this,SLOT(slotGridOnOff(bool)));
	connect(m_p_ToolButton_CameraManipulatorOnOff, SIGNAL(toggled(bool)),this,SLOT(slotCameraManipulatorOnOff(bool)));

	connect(m_p_ToolButton_RefinedZoom, SIGNAL(toggled(bool)),this,SLOT(slotRefinedZoom(bool)));
	connect(m_pComboBox_PercentageZoom, SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotPercentageZoom(const QString &)));

	connect(m_p_ComboBox_DefineDragAxis, SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotDefineDragAxis(const QString &)));

	connect(m_p_PushButton_ModifyScene_AddNewItem,SIGNAL(clicked()),this,SLOT(slotAddNewItem()));

	connect(m_p_PushButton_ProductSettings_AddNewProduct, SIGNAL(pressed()), this, SLOT(slotAddNewProductClicked()));

	connect(m_p_PushButton_ProductSettings_RemoveProduct,SIGNAL(pressed()),this,SLOT(slotRemoveProduct()));
	connect(m_p_PushButton_ProductSettings_MoreSettings,SIGNAL(pressed()),this,SLOT(slotProductMoreSettings()));

	connect(m_p_PushButton_ProductSettings_Apply,SIGNAL(clicked(bool)),this,SLOT(slotApplyModifyProductClicked()));

	connect(m_p_ComboBox_ProductSettings_ProductName,SIGNAL(editTextChanged(const QString &)),this,SLOT(slotComboBoxProductChanged()));

	//Item management
	connect(m_p_PushButton_ModifyScene_DeleteSelection,SIGNAL(clicked()),this,SLOT(slotRemoveSelection()));
	connect(m_p_PushButton_ModifyScene_SplitItem,SIGNAL(clicked()),this,SLOT(slotSplitItem()));
	connect(m_p_PushButton_ModifyScene_GroupItems,SIGNAL(clicked()),this,SLOT(slotGroupItems()));
	connect(m_p_PushButton_ModifyScene_DuplicateSelection,SIGNAL(clicked()),this,SLOT(slotDuplicateSelection()));
	connect(m_p_PushButton_ModifyScene_EditItem,SIGNAL(clicked()),this,SLOT(slotEditItem()));
}

//=========================================================================================

QString ShopBuilder_GUI::openDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		tr("."), apchDBName);

	return(qstrFileName);
}

//=========================================================================================

QString ShopBuilder_GUI::saveDialog(const char * apchDBName) {
	QString qstrFileName = QFileDialog::getSaveFileName(this, 
		tr("Save file"),
		tr(".\\"), apchDBName);
	return(qstrFileName);
}

//=========================================================================================

void ShopBuilder_GUI::slotNewProject()	{
	m_pShopBuilder->newDB();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotOpenDB() {
	QString qstrFileName = openDialog("*.db");

	m_pShopBuilder->readDB(qstrFileName.toStdString());
}

//=========================================================================================

void ShopBuilder_GUI::slotSaveDB() {
	m_pShopBuilder->saveDB();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSaveAsDB()	{
	m_pShopBuilder->saveAsDB();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotCloseDB()	{
	slotSaveDB();
	
	const string strCurrentFile = m_pShopBuilder->getCurrentFileName();
	m_pShopBuilder->closeDB(strCurrentFile);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSearchScene()	{
	string strSearchQuery = m_p_LineEdit_Search->text().toStdString();

	if (strSearchQuery.empty())
		return;
	
	if(m_pShopBuilder->searchScene(strSearchQuery))	{
		m_pSearchListWidget->show();
		m_pListView->setModel(m_pShopBuilder->getSceneObjectsSearchModel());
		m_pListView->show();
	}

}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotItemClicked(const QModelIndex & aItemIndex)	{
	QString strClickedItem = aItemIndex.data().toString();

	m_pShopBuilder->updateSearchList(strClickedItem.toStdString());

	ref_ptr<PickAndDragHandlerShopEditor> pPickAndDragHandlerShopEditor = m_pShopBuilder->getPicker();
	emit pPickAndDragHandlerShopEditor->signalPropertiesSettingsChanged();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotGridOnOff(bool abIndicator)	{
	m_pShopBuilder->gridOnOff(abIndicator);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotCameraManipulatorOnOff(bool abIndicator)	{
	if(abIndicator)	{
		//Left mouse drag makes the camera change
		std::cout << "Pan activated" << std::endl;

		//Deactivate Zoom
	}
	else	{
		std::cout << "Pan de-activated" << std::endl;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotRefinedZoom(bool abIndicator)	{
	if(abIndicator)	{
		//Left mouse drag makes the Zoom
		std::cout << "Zoom activated" << std::endl;

		//Deactivate Pan
	}
	else	{
		std::cout << "Zoom de-activated" << std::endl;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotPercentageZoom(const QString & astrZoomFactor)	{
	std::string strZoomFactor = astrZoomFactor.toStdString();

	std::cout << strZoomFactor << std::endl;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotDefineDragAxis(const QString & astrAxis)	{
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotAddNewItem()	{
	m_pShopBuilder->addNewItem();
}

//=======================================================================================

void ShopBuilder_GUI::slotAddNewProductClicked()	{
	m_pShopBuilder->addNewProduct();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotRemoveProduct()	{
	string strProductCode = m_p_ComboBox_ProductSettings_ProductName->currentText().toStdString();
	m_pShopBuilder->removeProductClicked(strProductCode);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotProductMoreSettings()	{
	string strProductCode = m_p_ComboBox_ProductSettings_ProductName->currentText().toStdString();
	m_pShopBuilder->productMoreSettingsClicked(strProductCode);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotProductClicked(const std::string & astrProductName)	{
	ShopBuilder::ProductClickedItems aProductClickedItems;
	aProductClickedItems.m_pComboBox_ProductSettings_ProductName = m_p_ComboBox_ProductSettings_ProductName;
	aProductClickedItems.m_pLineEdit_ProductSettings_Price = m_p_LineEdit_ProductSettings_Price;
	aProductClickedItems.m_pLineEdit_ProductSettings_Quantity = m_p_LineEdit_ProductSettings_Quantity;
	aProductClickedItems.m_strProductName = astrProductName;

	m_pShopBuilder->productClicked(aProductClickedItems);

	m_p_LineEdit_ProductSettings_NewPrice->setEnabled(true);
	m_p_LineEdit_ProductSettings_NewQuantity->setEnabled(true);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotApplyModifyProductClicked()	{
	ShopBuilder::ProductClickedItems aProductClickedItems;
	aProductClickedItems.m_pComboBox_ProductSettings_ProductName = m_p_ComboBox_ProductSettings_ProductName;
	aProductClickedItems.m_pLineEdit_ProductSettings_Price = m_p_LineEdit_ProductSettings_Price;
	aProductClickedItems.m_pLineEdit_ProductSettings_Quantity = m_p_LineEdit_ProductSettings_Quantity;
	aProductClickedItems.m_pLineEdit_ProductSettings_NewPrice = m_p_LineEdit_ProductSettings_NewPrice;
	aProductClickedItems.m_pLineEdit_ProductSettings_NewQuantity = m_p_LineEdit_ProductSettings_NewQuantity;

	m_pShopBuilder->modifyProductClicked(aProductClickedItems);

	m_p_LineEdit_ProductSettings_NewPrice->clear();
	m_p_LineEdit_ProductSettings_NewQuantity->clear();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotComboBoxProductChanged()	{
	ShopBuilder::ProductClickedItems aProductClickedItems;
	aProductClickedItems.m_pComboBox_ProductSettings_ProductName = m_p_ComboBox_ProductSettings_ProductName;
	aProductClickedItems.m_pLineEdit_ProductSettings_Price = m_p_LineEdit_ProductSettings_Price;
	aProductClickedItems.m_pLineEdit_ProductSettings_Quantity = m_p_LineEdit_ProductSettings_Quantity;

	m_pShopBuilder->updateProductSettings(aProductClickedItems);
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotAboutToQuitCalled()	{
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotGroupItems()	{
	m_pShopBuilder->groupItems();
}

//--------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSplitItem()	{
	m_pShopBuilder->splitItem();
}

//--------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotDuplicateSelection()	{
	m_pShopBuilder->duplicateSelection();
}

//--------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotRemoveSelection()	{
	m_pShopBuilder->removeSelection();
}

//--------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotEditItem()	{
	m_pShopBuilder->editItem();
}