#include <QDoubleSpinBox>
#include <QComboBox>

#include "VRAbstractObject.h"

#include "VRPickAndDragHandlerShopEditor.h"

#include "VRPickAndDragController.h"

using namespace VR;
using namespace osg;

PickAndDragController::PickAndDragController(
QDoubleSpinBox * apDoubleSpinBoxTranslationX,
QDoubleSpinBox * apDoubleSpinBoxTranslationY,
QDoubleSpinBox * apDoubleSpinBoxTranslationZ,
QDoubleSpinBox * apDoubleSpinBoxScalingX,
QDoubleSpinBox * apDoubleSpinBoxScalingY,
QDoubleSpinBox * apDoubleSpinBoxScalingZ,
QDoubleSpinBox * apDoubleSpinBoxRotationX,
QDoubleSpinBox * apDoubleSpinBoxRotationY,
QDoubleSpinBox * apDoubleSpinBoxRotationZ,
QComboBox * apComboBoxDirectionOfTranslation,
QComboBox * apComboBoxTranslateRelativeTo,
PickAndDragHandlerShopEditor * apPickAndDragHandlerShopEditor)	{

	m_pDoubleSpinBoxTranslationX = apDoubleSpinBoxTranslationX;
	m_pDoubleSpinBoxTranslationY = apDoubleSpinBoxTranslationY;
	m_pDoubleSpinBoxTranslationZ = apDoubleSpinBoxTranslationZ;

	m_pDoubleSpinBoxScalingX = apDoubleSpinBoxScalingX,
	m_pDoubleSpinBoxScalingY = apDoubleSpinBoxScalingY,
	m_pDoubleSpinBoxScalingZ = apDoubleSpinBoxScalingZ,
	m_pDoubleSpinBoxRotationX = apDoubleSpinBoxRotationX,
	m_pDoubleSpinBoxRotationY = apDoubleSpinBoxRotationY,
	m_pDoubleSpinBoxRotationZ = apDoubleSpinBoxRotationZ,

	m_pComboBoxDirectionOfTranslation = apComboBoxDirectionOfTranslation;
	m_pComboBoxTranslateRelativeTo = apComboBoxTranslateRelativeTo;

	m_pPickAndDragHandlerShopEditor = apPickAndDragHandlerShopEditor;

	connect(m_pDoubleSpinBoxTranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(m_pDoubleSpinBoxTranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(m_pDoubleSpinBoxTranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));

	connect(m_pDoubleSpinBoxRotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(m_pDoubleSpinBoxRotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(m_pDoubleSpinBoxRotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	connect(m_pDoubleSpinBoxScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(m_pDoubleSpinBoxScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(m_pDoubleSpinBoxScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));

	connect(m_pComboBoxDirectionOfTranslation,SIGNAL(currentTextChanged(const QString &)),
		m_pPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));
	connect(m_pComboBoxTranslateRelativeTo,SIGNAL(currentTextChanged(const QString &)),
		m_pPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));

	connect(m_pPickAndDragHandlerShopEditor,
		SIGNAL(signalPropertiesSettingsChanged()),
		this,
		SLOT(slotUpdatePickAndDragGUI()));
}

//======================================================================================

void PickAndDragController::slotUpdatePickAndDragGUI() {
	disconnect(m_pDoubleSpinBoxTranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	disconnect(m_pDoubleSpinBoxTranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	disconnect(m_pDoubleSpinBoxTranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));

	disconnect(m_pDoubleSpinBoxRotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	disconnect(m_pDoubleSpinBoxRotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	disconnect(m_pDoubleSpinBoxRotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	disconnect(m_pDoubleSpinBoxScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	disconnect(m_pDoubleSpinBoxScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	disconnect(m_pDoubleSpinBoxScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));

	ref_ptr<AbstractObject> pPickedObject = m_pPickAndDragHandlerShopEditor->getPickedObject();

	//Updates dialogs that reflect transformation changes done with the mouse
	Vec3d vec3dPos = pPickedObject->getPosition();
	m_pDoubleSpinBoxTranslationX->setValue(vec3dPos.x());
	m_pDoubleSpinBoxTranslationY->setValue(vec3dPos.y());
	m_pDoubleSpinBoxTranslationZ->setValue(vec3dPos.z());

	Vec3d vec3dScale = pPickedObject->getScaling();
	m_pDoubleSpinBoxScalingX->setValue(vec3dScale.x());
	m_pDoubleSpinBoxScalingY->setValue(vec3dScale.y());
	m_pDoubleSpinBoxScalingZ->setValue(vec3dScale.z());

	Vec3d vec3dRot = pPickedObject->getRotation();
	m_pDoubleSpinBoxRotationX->setValue(vec3dRot.x());
	m_pDoubleSpinBoxRotationY->setValue(vec3dRot.y());
	m_pDoubleSpinBoxRotationZ->setValue(vec3dRot.z());

	connect(m_pDoubleSpinBoxTranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(m_pDoubleSpinBoxTranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(m_pDoubleSpinBoxTranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	
	connect(m_pDoubleSpinBoxRotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(m_pDoubleSpinBoxRotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(m_pDoubleSpinBoxRotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	connect(m_pDoubleSpinBoxScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(m_pDoubleSpinBoxScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(m_pDoubleSpinBoxScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));

}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesPosition()	{
	Vec3d vec3dPosition;

	vec3dPosition[0] = m_pDoubleSpinBoxTranslationX->value();
	vec3dPosition[1] = m_pDoubleSpinBoxTranslationY->value();
	vec3dPosition[2] = m_pDoubleSpinBoxTranslationZ->value();

	m_pPickAndDragHandlerShopEditor->setPropertiesPosition(vec3dPosition);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesRotation()	{
	Vec3d vec3dRotation;

	vec3dRotation[0] = m_pDoubleSpinBoxRotationX->value();
	vec3dRotation[1] = m_pDoubleSpinBoxRotationY->value();
	vec3dRotation[2] = m_pDoubleSpinBoxRotationZ->value();

	m_pPickAndDragHandlerShopEditor->setPropertiesRotation(vec3dRotation);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesScaling()	{
	Vec3d vec3dScaling;

	vec3dScaling[0] = m_pDoubleSpinBoxScalingX->value();
	vec3dScaling[1] = m_pDoubleSpinBoxScalingY->value();
	vec3dScaling[2] = m_pDoubleSpinBoxScalingZ->value();

	m_pPickAndDragHandlerShopEditor->setPropertiesScaling(vec3dScaling);
}

//=====================================================================================