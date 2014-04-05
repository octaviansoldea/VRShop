#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>

#include "VRAbstractObject.h"
#include "VRScene.h"

#include "VRPickAndDragHandlerShopEditor.h"

#include "VRPickAndDragController.h"

using namespace VR;
using namespace osg;

PickAndDragController::PickAndDragController(
QDoubleSpinBox * a_p_DoubleSpinBox_TranslationX,
QDoubleSpinBox * a_p_DoubleSpinBox_TranslationY,
QDoubleSpinBox * a_p_DoubleSpinBox_TranslationZ,
QDoubleSpinBox * a_p_DoubleSpinBox_ScalingX,
QDoubleSpinBox * a_p_DoubleSpinBox_ScalingY,
QDoubleSpinBox * a_p_DoubleSpinBox_ScalingZ,
QDoubleSpinBox * a_p_DoubleSpinBox_RotationX,
QDoubleSpinBox * a_p_DoubleSpinBox_RotationY,
QDoubleSpinBox * a_p_DoubleSpinBox_RotationZ,
QComboBox * a_p_ComboBox_DirectionOfTranslation,
QComboBox * a_p_ComboBox_TranslateRelativeTo,
PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
ref_ptr<Scene> a_pScene)	{

	mp_DoubleSpinBox_TranslationX = a_p_DoubleSpinBox_TranslationX;
	mp_DoubleSpinBox_TranslationY = a_p_DoubleSpinBox_TranslationY;
	mp_DoubleSpinBox_TranslationZ = a_p_DoubleSpinBox_TranslationZ;

	mp_DoubleSpinBox_ScalingX = a_p_DoubleSpinBox_ScalingX,
	mp_DoubleSpinBox_ScalingY = a_p_DoubleSpinBox_ScalingY,
	mp_DoubleSpinBox_ScalingZ = a_p_DoubleSpinBox_ScalingZ,
	mp_DoubleSpinBox_RotationX = a_p_DoubleSpinBox_RotationX,
	mp_DoubleSpinBox_RotationY = a_p_DoubleSpinBox_RotationY,
	mp_DoubleSpinBox_RotationZ = a_p_DoubleSpinBox_RotationZ,

	mp_ComboBox_DirectionOfTranslation = a_p_ComboBox_DirectionOfTranslation;
	mp_ComboBox_TranslateRelativeTo = a_p_ComboBox_TranslateRelativeTo;

	mpPickAndDragHandlerShopEditor = dynamic_cast<PickAndDragHandlerShopEditor*>(a_pPickAndDragHandlerShopEditor);

	mp_Scene = a_pScene;

	connect(mp_DoubleSpinBox_TranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(mp_DoubleSpinBox_TranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(mp_DoubleSpinBox_TranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));

	connect(mp_DoubleSpinBox_RotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(mp_DoubleSpinBox_RotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(mp_DoubleSpinBox_RotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	connect(mp_DoubleSpinBox_ScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(mp_DoubleSpinBox_ScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(mp_DoubleSpinBox_ScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));

	connect(mp_ComboBox_DirectionOfTranslation,SIGNAL(currentTextChanged(const QString &)),
		mpPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));
	connect(mp_ComboBox_TranslateRelativeTo,SIGNAL(currentTextChanged(const QString &)),
		mpPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));

	connect(mpPickAndDragHandlerShopEditor,
		SIGNAL(signalPropertiesSettingsChanged()),
		this,
		SLOT(slotUpdatePickAndDragGUI()));
}

//--------------------------------------------------------------------------------------

PickAndDragController::PickAndDragController(
QPushButton * a_pPushButton_ModifyScene_DuplicateSelection,
QPushButton * a_pPushButton_ModifyScene_DeleteSelection,
QPushButton * a_pPushButton_ModifyScene_SplitItem,
QPushButton * a_pPushButton_ModifyScene_GroupItems,
PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
ref_ptr<Scene> a_pScene)	{

	mp_PushButton_ModifyScene_DuplicateSelection = a_pPushButton_ModifyScene_DuplicateSelection;
	mp_PushButton_ModifyScene_DeleteSelection = a_pPushButton_ModifyScene_DeleteSelection;
	mp_PushButton_ModifyScene_SplitItem = a_pPushButton_ModifyScene_SplitItem;
	mp_PushButton_ModifyScene_GroupItems = a_pPushButton_ModifyScene_GroupItems;

	mpPickAndDragHandlerShopEditor = dynamic_cast<PickAndDragHandlerShopEditor*>(a_pPickAndDragHandlerShopEditor);

	mp_Scene = a_pScene;

	connect(mp_PushButton_ModifyScene_DeleteSelection,SIGNAL(clicked()),
		this,SLOT(slotRemoveSelection()));
	connect(mp_PushButton_ModifyScene_SplitItem,SIGNAL(clicked()),
		this,SLOT(slotSplitItem()));
	connect(mp_PushButton_ModifyScene_GroupItems,SIGNAL(clicked()),
		this,SLOT(slotGroupItems()));
	connect(mp_PushButton_ModifyScene_DuplicateSelection,SIGNAL(clicked()),
		this,SLOT(slotDuplicateSelection()));
}

//======================================================================================

void PickAndDragController::slotUpdatePickAndDragGUI() {
	disconnect(mp_DoubleSpinBox_TranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	disconnect(mp_DoubleSpinBox_TranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	disconnect(mp_DoubleSpinBox_TranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));

	disconnect(mp_DoubleSpinBox_RotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	disconnect(mp_DoubleSpinBox_RotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	disconnect(mp_DoubleSpinBox_RotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	disconnect(mp_DoubleSpinBox_ScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	disconnect(mp_DoubleSpinBox_ScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	disconnect(mp_DoubleSpinBox_ScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));


	//Updates dialogs that reflect transformation changes done with the mouse
	Vec3d & vec3dPos = mpPickAndDragHandlerShopEditor->m_pPickedObject->getPosition();
	mp_DoubleSpinBox_TranslationX->setValue(vec3dPos.x());
	mp_DoubleSpinBox_TranslationY->setValue(vec3dPos.y());
	mp_DoubleSpinBox_TranslationZ->setValue(vec3dPos.z());

	Vec3d & vec3dScale = mpPickAndDragHandlerShopEditor->m_pPickedObject->getScaling();
	mp_DoubleSpinBox_ScalingX->setValue(vec3dScale.x());
	mp_DoubleSpinBox_ScalingY->setValue(vec3dScale.y());
	mp_DoubleSpinBox_ScalingZ->setValue(vec3dScale.z());

	Vec3d & vec3dRot = mpPickAndDragHandlerShopEditor->m_pPickedObject->getRotation();
	mp_DoubleSpinBox_RotationX->setValue(vec3dRot.x());
	mp_DoubleSpinBox_RotationY->setValue(vec3dRot.y());
	mp_DoubleSpinBox_RotationZ->setValue(vec3dRot.z());

	connect(mp_DoubleSpinBox_TranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(mp_DoubleSpinBox_TranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));
	connect(mp_DoubleSpinBox_TranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPosition()));

	connect(mp_DoubleSpinBox_RotationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(mp_DoubleSpinBox_RotationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));
	connect(mp_DoubleSpinBox_RotationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesRotation()));

	connect(mp_DoubleSpinBox_ScalingX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(mp_DoubleSpinBox_ScalingY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));
	connect(mp_DoubleSpinBox_ScalingZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesScaling()));

}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesPosition()	{
	Vec3d vec3dPosition;

	vec3dPosition[0] = mp_DoubleSpinBox_TranslationX->value();
	vec3dPosition[1] = mp_DoubleSpinBox_TranslationY->value();
	vec3dPosition[2] = mp_DoubleSpinBox_TranslationZ->value();

	mpPickAndDragHandlerShopEditor->setPropertiesPosition(vec3dPosition);
	mp_Scene->print();
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesRotation()	{
	Vec3d vec3dRotation;

	vec3dRotation[0] = mp_DoubleSpinBox_RotationX->value();
	vec3dRotation[1] = mp_DoubleSpinBox_RotationY->value();
	vec3dRotation[2] = mp_DoubleSpinBox_RotationZ->value();

	mpPickAndDragHandlerShopEditor->setPropertiesRotation(vec3dRotation);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesScaling()	{
	Vec3d vec3dScaling;

	vec3dScaling[0] = mp_DoubleSpinBox_ScalingX->value();
	vec3dScaling[1] = mp_DoubleSpinBox_ScalingY->value();
	vec3dScaling[2] = mp_DoubleSpinBox_ScalingZ->value();

	mpPickAndDragHandlerShopEditor->setPropertiesScaling(vec3dScaling);
}

//=====================================================================================

void PickAndDragController::slotGroupItems()	{
	mpPickAndDragHandlerShopEditor->groupSelection(mp_Scene);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSplitItem()	{
	mpPickAndDragHandlerShopEditor->splitSelection(mp_Scene);
	mp_Scene->print();
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotDuplicateSelection()	{
	mpPickAndDragHandlerShopEditor->duplicateSelection(mp_Scene);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotRemoveSelection()	{
	mpPickAndDragHandlerShopEditor->removeSelection(mp_Scene);
}