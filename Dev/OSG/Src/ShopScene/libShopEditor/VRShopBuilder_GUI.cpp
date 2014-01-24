#include "StringManipulation.h"

#include <osgDB/ReadFile>

#include <QFileDialog>
#include <QMessageBox>

#include "VRProductSettings_GUI.h"
#include "VRRemoveProduct_GUI.h"
#include "VRRemoveSelection_GUI.h"

#include "VRNewProject_GUI.h"
#include "VRInsertNewItem_GUI.h"
#include "VRDuplicateItem_GUI.h"
#include "VRSaveAs_GUI.h"

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI()	{	
	setupUi(this);

	setWindowTitle("VR Shop Server Dialog");

	m_ShopBuilder.init(m_pOSGQTWidget, m_pTreeView);

	m_pOSGQTWidget->show();

	buildConnections();
}


//=========================================================================================

void ShopBuilder_GUI::buildConnections() {
	connect(actionNew, SIGNAL(triggered()), this, SLOT(slotNewProject()));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenDB()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSaveDB()));
	connect(actionSave_As, SIGNAL(triggered()), this, SLOT(slotSaveAsDB()));
	connect(actionClose, SIGNAL(triggered()), this, SLOT(slotCloseDB()));

	connect(m_p_ToolButton_GridOnOff, SIGNAL(toggled(bool)),this,SLOT(slotGridOnOff(bool)));
	connect(m_p_ToolButton_CameraManipulatorOnOff, SIGNAL(toggled(bool)),this,SLOT(slotCameraManipulatorOnOff(bool)));

	connect(m_p_ToolButton_RefinedZoom, SIGNAL(toggled(bool)),this,SLOT(slotRefinedZoom(bool)));
	connect(m_pComboBox_PercentageZoom, SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotPercentageZoom(const QString &)));

	connect(m_p_ComboBox_DefineDragAxis, SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotDefineDragAxis(const QString &)));

	connect(m_p_DoubleSpinBox_TranslationX,SIGNAL(valueChanged(double)),this,SLOT(slotSetTranslation()));
	connect(m_p_DoubleSpinBox_TranslationY,SIGNAL(valueChanged(double)),this,SLOT(slotSetTranslation()));
	connect(m_p_DoubleSpinBox_TranslationZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetTranslation()));

	connect(m_p_DoubleSpinBox_RotationX,SIGNAL(valueChanged(double)),this,SLOT(slotSetRotation()));
	connect(m_p_DoubleSpinBox_RotationY,SIGNAL(valueChanged(double)),this,SLOT(slotSetRotation()));
	connect(m_p_DoubleSpinBox_RotationZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetRotation()));

	connect(m_p_DoubleSpinBox_ScalingX,SIGNAL(valueChanged(double)),this,SLOT(slotSetScaling()));
	connect(m_p_DoubleSpinBox_ScalingY,SIGNAL(valueChanged(double)),this,SLOT(slotSetScaling()));
	connect(m_p_DoubleSpinBox_ScalingZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetScaling()));

	connect(m_p_DoubleSpinBox_ShearingX,SIGNAL(valueChanged(double)),this,SLOT(slotSetShearing()));
	connect(m_p_DoubleSpinBox_ShearingY,SIGNAL(valueChanged(double)),this,SLOT(slotSetShearing()));
	connect(m_p_DoubleSpinBox_ShearingZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetShearing()));

	connect(m_p_DoubleSpinBox_CameraPositionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetPosition()));

	connect(m_p_DoubleSpinBox_CameraDirectionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetDirection()));
	connect(m_p_DoubleSpinBox_CameraDirectionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetDirection()));
	connect(m_p_DoubleSpinBox_CameraDirectionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetDirection()));

	connect(m_p_ComboBox_DirectionOfTranslation,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetDirectionOfTranslation(const QString &)));
	connect(m_p_ComboBox_TranslateRelativeTo,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetTranslateRelativeTo(const QString &)));
	connect(m_p_ComboBox_CenterOfRotation,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetCenterOfRotation(const QString &)));

	connect(m_p_ComboBox_PredefinedViewport,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetPredefinedViewport(const QString &)));

	connect(m_p_PushButton_SetHomePosition,SIGNAL(clicked()),this,SLOT(slotSetHomePosition()));
	connect(m_p_PushButton_HomePosition,SIGNAL(clicked()),this,SLOT(slotSetHomePosition()));
	connect(m_p_PushButton_SetHomeDirection,SIGNAL(clicked()),this,SLOT(slotSetHomeDirection()));
	connect(m_p_PushButton_HomeDirection,SIGNAL(clicked()),this,SLOT(slotSetHomeDirection()));

	connect(m_p_PushButton_ModifyScene_AddNewItem,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
	connect(m_p_PushButton_ModifyScene_EditItem,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
	connect(m_p_PushButton_ModifyScene_GroupItems,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
	connect(m_p_PushButton_ModifyScene_SplitItem,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
	connect(m_p_PushButton_ModifyScene_DuplicateSelection,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));
	connect(m_p_PushButton_ModifyScene_DeleteSelection,SIGNAL(clicked()),this,SLOT(slotModifySceneActions()));	

	connect(m_p_PushButton_ProductSettings_AddNewProduct,SIGNAL(clicked()),this,SLOT(slotModifyProductSettings()));
	connect(m_p_PushButton_ProductSettings_RemoveProduct,SIGNAL(clicked()),this,SLOT(slotModifyProductSettings()));

	connect(m_p_ComboBox_ProductSettings_ProductName,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slotSetProductSettings(const QString &)));

	connect(m_p_PushButton_ProductSettings_Apply,SIGNAL(clicked()),this,SLOT(slotModifyProductButtons()));
	connect(m_p_PushButton_ProductSettings_Cancel,SIGNAL(clicked()),this,SLOT(slotModifyProductButtons()));
	connect(m_p_PushButton_ProductSettings_MoreSettings,SIGNAL(clicked()),this,SLOT(slotModifyProductButtons()));
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
		QString qstrFileName;
		qstrFileName = newProject.m_pLineEditDirectory->text() + "/" + newProject.m_pLineEditFileName->text() + ".db";
		m_ShopBuilder.newDB(qstrFileName.toStdString());
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
	m_ShopBuilder.readDB(qstrFileName.toStdString());
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
	m_ShopBuilder.saveDB(qstrFileName.toStdString());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSaveAsDB()	{
	SaveAs_GUI saveAsGUI;

	//To get a widget without a "TitleBar"
	saveAsGUI.setWindowFlags(Qt::FramelessWindowHint);
	saveAsGUI.exec();
	return;
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

void ShopBuilder_GUI::slotGridOnOff(bool abIndicator)	{
	m_ShopBuilder.gridOnOff(abIndicator);
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

void ShopBuilder_GUI::slotSetTranslation()	{
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetDirectionOfTranslation(const QString & astrText)	{
	std::string strText = astrText.toStdString();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetTranslateRelativeTo(const QString & astrText)	{
	std::string strText = astrText.toStdString();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetCenterOfRotation(const QString & astrText)	{
	std::string strText = astrText.toStdString();
}

//---------------------------------------------------------------------------------------
void ShopBuilder_GUI::slotSetRotation()	{
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
	
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetPredefinedViewport(const QString & astrText)	{
	std::string strText = astrText.toStdString();
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetScaling() {
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetShearing()	{
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetPosition() {
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetDirection() {
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetHomePosition()	{
	QPushButton * pPushButton = dynamic_cast<QPushButton*>(sender());
	if(pPushButton == m_p_PushButton_SetHomePosition)	{
	}
	else if	(pPushButton == m_p_PushButton_HomePosition)	{
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetHomeDirection()	{
	QPushButton * pPushButton = dynamic_cast<QPushButton*>(sender());
	if(pPushButton == m_p_PushButton_SetHomeDirection)	{
		return;
	}
	if	(pPushButton == m_p_PushButton_HomeDirection)	{
		return;
	}
	else	{
		return;
	}
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
	if	(pPushButton == m_p_PushButton_ModifyScene_EditItem)	{
		std::cout << "Edit item" << std::endl;
		// void editItemWidget();
		return;
	}
	if	(pPushButton == m_p_PushButton_ModifyScene_GroupItems)	{
		std::cout << "Group items" << std::endl;
		// void groupItemsWidget();
		return;
	}
	if	(pPushButton == m_p_PushButton_ModifyScene_SplitItem)	{
		std::cout << "Split item" << std::endl;
		// void splitItemWidget();
		return;
	}
	if	(pPushButton == m_p_PushButton_ModifyScene_DuplicateSelection)	{
		DuplicateItem_GUI * pDuplicateItem_GUI = new DuplicateItem_GUI;

		//To get a widget without a "TitleBar"
		pDuplicateItem_GUI->setWindowFlags(Qt::FramelessWindowHint);
		pDuplicateItem_GUI->exec();

		delete pDuplicateItem_GUI;
		return;
	}
	if	(pPushButton == m_p_PushButton_ModifyScene_DeleteSelection)	{
		RemoveSelection_GUI * pRemoveSelection_GUI = new RemoveSelection_GUI;

		//To get a widget without a "TitleBar"
		pRemoveSelection_GUI->setWindowFlags(Qt::FramelessWindowHint);
		pRemoveSelection_GUI->exec();

		delete pRemoveSelection_GUI;
		return;
	}
	else	{
		return;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotModifyProductSettings()	{
	QPushButton * pPushButton = dynamic_cast<QPushButton*>(sender());
	if(pPushButton == m_p_PushButton_ProductSettings_AddNewProduct)	{
		ProductSettings_GUI productSettings;
		
		//To get a widget without a "TitleBar"
		productSettings.setWindowFlags(Qt::FramelessWindowHint);
		productSettings.exec();
		return;
	}
	if	(pPushButton == m_p_PushButton_ProductSettings_RemoveProduct)	{
		RemoveProduct_GUI rProduct;
		
		//To get a widget without a "TitleBar"
		rProduct.setWindowFlags(Qt::FramelessWindowHint);
		rProduct.exec();
		return;
	}
	else	{
		return;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetProductSettings(const QString & astrSelectedProduct)	{
	QString strSelectedproduct = astrSelectedProduct;

	QString strPrice = strSelectedproduct + " 10.1";
	QString strQuantity = strSelectedproduct + " 10";

	m_p_LineEdit_ProductSettings_Price->setText(strPrice);
	m_p_LineEdit_ProductSettings_Quantity->setText(strQuantity);

	m_p_LineEdit_ProductSettings_NewPrice->setEnabled(true);
	m_p_LineEdit_ProductSettings_NewQuantity->setEnabled(true);

}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotSetNewPriceQuantity()	{
	//Update database with new data
	//Perhaps open a new "confirmation" widget

	m_p_LineEdit_ProductSettings_NewPrice;
	m_p_LineEdit_ProductSettings_NewQuantity;
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotModifyProductButtons()	{
	QPushButton * pPushButton = dynamic_cast<QPushButton*>(sender());
	if(pPushButton == m_p_PushButton_ProductSettings_Apply)	{
		std::cout << "Apply button clicked" << std::endl;
		// void applyProductSettingstWidget();
		return;
	}

	if(pPushButton == m_p_PushButton_ProductSettings_Cancel)	{
		m_p_LineEdit_ProductSettings_NewPrice->clear();
		m_p_LineEdit_ProductSettings_NewQuantity->clear();
		m_p_ComboBox_ProductSettings_ProductName->clearEditText();
		m_p_LineEdit_ProductSettings_Price->clear();
		m_p_LineEdit_ProductSettings_Quantity->clear();

		return;
	}
	if(pPushButton == m_p_PushButton_ProductSettings_MoreSettings)	{
		std::cout << "More settings button clicked" << std::endl;
		// void applyProductSettingstWidget();
		return;
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotAddNewItem(const QString & aqstrItemName)	{
	m_ShopBuilder.addNewItem(aqstrItemName.toStdString());
}