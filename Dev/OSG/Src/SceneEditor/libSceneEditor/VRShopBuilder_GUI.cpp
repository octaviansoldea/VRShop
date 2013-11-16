#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include <QFileDialog>
#include <QMessageBox>

#include "VRGrid.h"

#include "VRShopBuilder_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder_GUI::ShopBuilder_GUI() {	
	setupUi(this);

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_ShopBuilder.m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);

	setWindowTitle("VR Shop Server Dialog");

	m_pGridlines = new Grid;
	if(m_p_ToolButton_GridOnOff->isChecked())	{
		m_ShopBuilder.m_pScene->addChild(m_pGridlines);
	}


	m_pOSGQTWidget->show();

	//SIGNAL/SLOT CONNECTIONS
	buildConnections();
	slotSetTranslation();
}


//=========================================================================================

void ShopBuilder_GUI::buildConnections() {
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenDB()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSaveDB()));

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

	std::cout << qstrFileName.toStdString() << std::endl;

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

void ShopBuilder_GUI::slotOpenDB() {
	QString qstrFileName = openDialog("*.db");
	if(qstrFileName != "") {
		QMessageBox msgBox;
		msgBox.setText(qstrFileName + "Write");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setWindowTitle("Error window");
		int nRes = msgBox.exec();
	}
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
	}
}

//---------------------------------------------------------------------------------------

void ShopBuilder_GUI::slotGridOnOff(bool abIndicator)	{
	int nRes = m_ShopBuilder.m_pScene->getChildIndex(m_pGridlines);
	int nSize = m_ShopBuilder.m_pScene->getNumChildren();

	//ToolButton checked && Grid not already a child
	if (abIndicator && nRes == nSize) {
		m_pGridlines = new Grid;
		m_ShopBuilder.m_pScene->addChild(m_pGridlines);
	}
	else	{
		if(nRes < nSize)	{
			int nI;
			for(nI = 0; nI < m_pGridlines->getNumParents();nI++)	{
				m_ShopBuilder.m_pScene->removeChild(m_pGridlines->getParent(nI));
			}
			m_ShopBuilder.m_pScene->removeChild(m_pGridlines);
		}
		else	{
			return;
			//If here, do nothing (the grid not part of the scene)
		}
	}
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
		std::cout << "Add new item" << std::endl;
		// void addNewSceneWidget();
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
		std::cout << "Duplicate selection" << std::endl;
		// void duplicateSelectionWidget();
		return;
	}
	if	(pPushButton == m_p_PushButton_ModifyScene_DeleteSelection)	{
		std::cout << "delete selection" << std::endl;
		// void deleteSelectionWidget();
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
		std::cout << "Add new product" << std::endl;
		// void addNewProductWidget();
		return;
	}
	if	(pPushButton == m_p_PushButton_ProductSettings_RemoveProduct)	{
		std::cout << "Remove product" << std::endl;
		// void removeProductWidget();
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
		std::cout << "Cancel button clicked" << std::endl;
		// void applyProductSettingstWidget();
		return;
	}

	if(pPushButton == m_p_PushButton_ProductSettings_MoreSettings)	{
		std::cout << "More settings button clicked" << std::endl;
		// void applyProductSettingstWidget();
		return;
	}
}