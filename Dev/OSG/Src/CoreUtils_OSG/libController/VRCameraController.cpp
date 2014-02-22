#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>


#include "VRKeyboardMouseManipulatorShopEditor.h"
#include "VRCameraController.h"

using namespace VR;

CameraController::CameraController(
	QComboBox * ap_ComboBox_PredefinedViewport,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionX,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionY,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionZ,
	QPushButton * ap_PushButton_SetCameraPositionDefault,
	QPushButton * ap_PushButton_CameraPosition,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionX,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionY,
	QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionZ,
	QPushButton * ap_PushButton_SetCameraHeadingDirectionDefault,
	QPushButton * ap_PushButton_CameraHeadingDirection,
	KeyboardMouseManipulatorShopEditor * apKeyboardMouseManipulatorShopEditor) {

	m_p_ComboBox_PredefinedViewport = ap_ComboBox_PredefinedViewport;
	
	m_p_DoubleSpinBox_CameraPositionX = ap_DoubleSpinBox_CameraPositionX;
	m_p_DoubleSpinBox_CameraPositionY = ap_DoubleSpinBox_CameraPositionY;
	m_p_DoubleSpinBox_CameraPositionZ = ap_DoubleSpinBox_CameraPositionZ;
	m_p_PushButton_SetCameraPositionDefault = ap_PushButton_SetCameraPositionDefault;
	m_p_PushButton_CameraPosition = ap_PushButton_CameraPosition;
	m_p_PushButton_CameraHeadingDirection = ap_PushButton_CameraHeadingDirection;
	
	m_p_DoubleSpinBox_CameraHeadingDirectionX = ap_DoubleSpinBox_CameraHeadingDirectionX;
	m_p_DoubleSpinBox_CameraHeadingDirectionY = ap_DoubleSpinBox_CameraHeadingDirectionY;
	m_p_DoubleSpinBox_CameraHeadingDirectionZ = ap_DoubleSpinBox_CameraHeadingDirectionZ;
	m_p_PushButton_SetCameraHeadingDirectionDefault = ap_PushButton_SetCameraHeadingDirectionDefault;

	m_pKeyboardMouseManipulatorShopEditor = apKeyboardMouseManipulatorShopEditor;

	connect(m_p_ComboBox_PredefinedViewport,SIGNAL(currentTextChanged(const QString &)),
		m_pKeyboardMouseManipulatorShopEditor,SLOT(slotSetPredefinedViewport(const QString &)));

	connect(m_p_DoubleSpinBox_CameraPositionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));

	connect(m_p_PushButton_SetCameraPositionDefault,SIGNAL(clicked()),this,SLOT(slotSetCameraPositionDefault()));
	connect(m_p_PushButton_SetCameraHeadingDirectionDefault,SIGNAL(clicked()),this,SLOT(slotSetCameraHeadingDirectionDefault()));

	connect(m_p_PushButton_CameraPosition,SIGNAL(clicked()),this,SLOT(slotCameraHomePosition()));
	connect(m_p_PushButton_CameraHeadingDirection,SIGNAL(clicked()),this,SLOT(slotCameraHomePosition()));

	connect(m_pKeyboardMouseManipulatorShopEditor,
			SIGNAL(signalCameraPositionOrHeadingDirectionChanged()),
			this,
			SLOT(slotUpdateCameraGUI()));
}

void CameraController::slotUpdateCameraGUI() {
	disconnect(m_p_DoubleSpinBox_CameraPositionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	disconnect(m_p_DoubleSpinBox_CameraPositionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	disconnect(m_p_DoubleSpinBox_CameraPositionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	disconnect(m_p_DoubleSpinBox_CameraHeadingDirectionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	disconnect(m_p_DoubleSpinBox_CameraHeadingDirectionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	disconnect(m_p_DoubleSpinBox_CameraHeadingDirectionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));

	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;
	m_pKeyboardMouseManipulatorShopEditor->getTransformation(vec3dEye, vec3dCenter, vec3dUp);
	m_p_DoubleSpinBox_CameraPositionX->setValue(vec3dEye[0]);
	m_p_DoubleSpinBox_CameraPositionY->setValue(vec3dEye[1]);
	m_p_DoubleSpinBox_CameraPositionZ->setValue(vec3dEye[2]);
	m_p_DoubleSpinBox_CameraHeadingDirectionX->setValue(vec3dCenter[0]);
	m_p_DoubleSpinBox_CameraHeadingDirectionY->setValue(vec3dCenter[1]);
	m_p_DoubleSpinBox_CameraHeadingDirectionZ->setValue(vec3dCenter[2]);

	//THESE SEEM UNNECESSARY
	connect(m_p_DoubleSpinBox_CameraPositionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraPositionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraPosition()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionX,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionY,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
	connect(m_p_DoubleSpinBox_CameraHeadingDirectionZ,SIGNAL(valueChanged(double)),this,SLOT(slotSetCameraHeadingDirection()));
}


void CameraController::slotCameraHomePosition() {
	m_pKeyboardMouseManipulatorShopEditor->home(0);
}


void CameraController::slotSetCameraPosition() {
	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;
	m_pKeyboardMouseManipulatorShopEditor->getTransformation(vec3dEye, vec3dCenter, vec3dUp);
	vec3dEye[0] = m_p_DoubleSpinBox_CameraPositionX->value();
	vec3dEye[1] = m_p_DoubleSpinBox_CameraPositionY->value();
	vec3dEye[2] = m_p_DoubleSpinBox_CameraPositionZ->value();
	m_pKeyboardMouseManipulatorShopEditor->setTransformation(vec3dEye, vec3dCenter, vec3dUp);
}

void CameraController::slotSetCameraPositionDefault() {
	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;
	m_pKeyboardMouseManipulatorShopEditor->getHomePosition(vec3dEye, vec3dCenter, vec3dUp);
	vec3dEye[0] = m_p_DoubleSpinBox_CameraPositionX->value();
	vec3dEye[1] = m_p_DoubleSpinBox_CameraPositionY->value();
	vec3dEye[2] = m_p_DoubleSpinBox_CameraPositionZ->value();
	m_pKeyboardMouseManipulatorShopEditor->setHomePosition(vec3dEye, vec3dCenter, vec3dUp);	
}

void CameraController::slotSetCameraHeadingDirection() {
	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;
	m_pKeyboardMouseManipulatorShopEditor->getTransformation(vec3dEye, vec3dCenter, vec3dUp);
	vec3dCenter[0] = m_p_DoubleSpinBox_CameraHeadingDirectionX->value();
	vec3dCenter[1] = m_p_DoubleSpinBox_CameraHeadingDirectionY->value();
	vec3dCenter[2] = m_p_DoubleSpinBox_CameraHeadingDirectionZ->value();
	m_pKeyboardMouseManipulatorShopEditor->setTransformation(vec3dEye, vec3dCenter, vec3dUp);
}

void CameraController::slotSetCameraHeadingDirectionDefault() {
	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;
	m_pKeyboardMouseManipulatorShopEditor->getHomePosition(vec3dEye, vec3dCenter, vec3dUp);
	vec3dCenter[0] = m_p_DoubleSpinBox_CameraHeadingDirectionX->value();
	vec3dCenter[1] = m_p_DoubleSpinBox_CameraHeadingDirectionY->value();
	vec3dCenter[2] = m_p_DoubleSpinBox_CameraHeadingDirectionZ->value();
	m_pKeyboardMouseManipulatorShopEditor->setHomePosition(vec3dEye, vec3dCenter, vec3dUp);
}
