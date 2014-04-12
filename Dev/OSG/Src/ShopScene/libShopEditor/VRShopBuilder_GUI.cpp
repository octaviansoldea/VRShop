#include "BasicStringDefinitions.h"

#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>

#include <QFileDialog>
#include <QMessageBox>


#include "VRNewProject_GUI.h"
#include "VRInsertNewItem_GUI.h"
//#include "VRSaveAs_GUI.h"

#include "VRShopBuilder.h"
#include "VRScene.h"
#include "VRProductManager.h"

#include "VRCameraController.h"
#include "VRPickAndDragController.h"
#include "VRSearchListController.h"
#include "VRProductController.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"
#include "VRPickAndDragHandlerShopEditor.h"
#include "VRSceneObjectsSearchShopEditor.h"
#include "VRProductManager.h"

#include "VRDataStructureModel.h"

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI()	{
	setupUi(this);

	setWindowTitle("VR Shop Server Dialog");

	m_pShopBuilder = new ShopBuilder(m_pOSGQTWidget);
	ref_ptr<Scene> pScene = m_pShopBuilder->getScene();
	ref_ptr<ProductManager> pProductMgr = m_pShopBuilder->getProducts();

	KeyboardMouseManipulatorShopEditor * pKeyboardMouseManipulatorShopEditor = 
		dynamic_cast<KeyboardMouseManipulatorShopEditor *>(m_pOSGQTWidget->getCameraManipulator());

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

	PickAndDragHandlerShopEditor *pPickAndDragHandlerShopEditor = 		
		dynamic_cast<PickAndDragHandlerShopEditor *>(m_pShopBuilder->m_pEventHandler);

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
		pPickAndDragHandlerShopEditor,
		pScene);


	m_pPickAndDragController = new PickAndDragController(
		m_p_PushButton_ModifyScene_DuplicateSelection,
		m_p_PushButton_ModifyScene_DeleteSelection,
		m_p_PushButton_ModifyScene_SplitItem,
		m_p_PushButton_ModifyScene_GroupItems,
		m_p_PushButton_ModifyScene_EditItem,
		pPickAndDragHandlerShopEditor,
		pScene);


	m_pProductController = new ProductController(
		m_p_PushButton_ProductSettings_AddNewProduct,
		m_p_PushButton_ProductSettings_RemoveProduct,
		m_p_PushButton_ProductSettings_Apply,
		m_p_PushButton_ProductSettings_Cancel,
		m_p_PushButton_ProductSettings_MoreSettings,
		m_p_ComboBox_ProductSettings_ProductName,
		m_p_LineEdit_ProductSettings_NewPrice,
		m_p_LineEdit_ProductSettings_NewQuantity,
		m_p_LineEdit_ProductSettings_Price,
		m_p_LineEdit_ProductSettings_Quantity,
		pProductMgr,
		pPickAndDragHandlerShopEditor
	);

	m_pOSGQTWidget->show();

	buildConnections();
}

//=========================================================================================

ShopBuilder_GUI::~ShopBuilder_GUI() {
	delete m_pCameraController;
	delete m_pPickAndDragController;
	delete m_pProductController;

	delete m_pOSGQTWidget;

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

	connect(m_p_PushButton_ModifyScene_AddNewItem,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
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
	NewProject_GUI newProject;
		
	//To get a widget without a "TitleBar"
	newProject.setWindowFlags(Qt::FramelessWindowHint);
	newProject.exec();

	//Result == 1 indicates that path+name are valid
	if (newProject.result() == 1)	{
		string & strFileName = 
			(newProject.m_pLineEditDirectory->text() + "/" + newProject.m_pLineEditFileName->text()).toStdString();
		strFileName += (isAtEndOfString(strFileName, ".db")) ? "" : ".db";
		replace(strFileName.begin(), strFileName.end(), '/', '\\');

		QDir dir(strFileName.c_str());
		if(dir.exists(strFileName.c_str()))	{
			QMessageBox msgBox;
			string strText = "File " + strFileName + " already exists. \n Press OK to overwrite it, else press NO.";
			msgBox.setText(strText.c_str());
			msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
			msgBox.setWindowTitle("Warning window");
			int nRes = msgBox.exec();

			if (nRes == QMessageBox::Ok)	{
				dir.remove(strFileName.c_str());
				m_pShopBuilder->newDB(strFileName);
			} else {
				newProject.close();
				slotNewProject();
			}
		}
		m_pShopBuilder->newDB(strFileName);
	}
	return;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotOpenDB() {
	QString qstrFileName = openDialog("*.db");

	if(isAtEndOfString(qstrFileName.toStdString(), ".db") == false)	{
		QMessageBox msgBox;
		msgBox.setText(qstrFileName + " Could not open file");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}
	m_pShopBuilder->readDB(qstrFileName.toStdString());
}

//=========================================================================================

void ShopBuilder_GUI::slotSaveDB() {
	QString qstrFileName = saveDialog("*.db");
	if(qstrFileName != "") {
		QMessageBox msgBox;
		msgBox.setText(qstrFileName + "Save");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
		return;
	}
	m_pShopBuilder->saveDB(qstrFileName.toStdString());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSaveAsDB()	{
	//SaveAs_GUI saveAsGUI;

	////To get a widget without a "TitleBar"
	//saveAsGUI.setWindowFlags(Qt::FramelessWindowHint);
	//saveAsGUI.exec();
	//return;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotCloseDB()	{
	/* Close if no unsaved changes are done to the project
	If the project has been modified, then write a warning message admonishing to the changes
	done which will be lost if not saved.
	If YES pressed, open Save As dialog
	*/

	std::cout << "slot Close entered" << std::endl;
	return;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSearchScene()	{
	string & strSearchQuery = m_p_LineEdit_Search->text().toStdString();

	if (strSearchQuery.empty())
		return;

	DataStructureModel * pDataStructureModel = 0;
	
	if(m_pShopBuilder->searchScene(strSearchQuery, &pDataStructureModel))	{
		m_pSearchListWidget->show();
		m_pListView->setModel(pDataStructureModel);
		m_pListView->show();
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotItemClicked(const QModelIndex & aItemIndex)	{
	QString & strClickedItem = aItemIndex.data().toString();

	PickAndDragHandlerShopEditor *pPickAndDragHandlerShopEditor = 		
		dynamic_cast<PickAndDragHandlerShopEditor *>(m_pShopBuilder->m_pEventHandler);

	SearchListController searchList(
		strClickedItem,
		pPickAndDragHandlerShopEditor,
		m_pShopBuilder->getScene()
	);
	searchList.updateSearchListGUI();
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

void ShopBuilder_GUI::slotModifySceneActions()	{
	QPushButton * pPushButton = dynamic_cast<QPushButton*>(sender());
	if(pPushButton == m_p_PushButton_ModifyScene_AddNewItem)	{
		InsertNewItem_GUI * pInsertNewItem_GUI = new InsertNewItem_GUI;
		connect(pInsertNewItem_GUI, SIGNAL(signalNewItemRequested(const QString &)),
				this, SLOT(slotAddNewItem(const QString & )));

		//To get a widget without a "TitleBar"
		pInsertNewItem_GUI->setWindowFlags(Qt::FramelessWindowHint);
		pInsertNewItem_GUI->exec();

		delete pInsertNewItem_GUI;
		return;
	}
	else	{
		return;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetNewPriceQuantity()	{
	//Update database with new data
	//Perhaps open a new "confirmation" widget

	m_p_LineEdit_ProductSettings_NewPrice;
	m_p_LineEdit_ProductSettings_NewQuantity;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotAddNewItem(const QString & aqstrItemName)	{
	m_pShopBuilder->addNewItem(aqstrItemName.toStdString());
}

//=======================================================================================
