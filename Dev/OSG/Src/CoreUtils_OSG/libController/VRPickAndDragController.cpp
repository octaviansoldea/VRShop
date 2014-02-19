#include <iostream>

#include <QDoubleSpinBox>
#include <QComboBox>

#include "VRPickAndDragHandlerShopEditor.h"

#include "VRPickAndDragController.h"

using namespace VR;
using namespace osg;

PickAndDragController::PickAndDragController(
QDoubleSpinBox * ap_DoubleSpinBox_TranslationX,
QDoubleSpinBox * ap_DoubleSpinBox_TranslationY,
QDoubleSpinBox * ap_DoubleSpinBox_TranslationZ,
QDoubleSpinBox * ap_DoubleSpinBox_ScalingX,
QDoubleSpinBox * ap_DoubleSpinBox_ScalingY,
QDoubleSpinBox * ap_DoubleSpinBox_ScalingZ,
QComboBox * ap_ComboBox_DirectionOfTranslation,
QComboBox * ap_ComboBox_TranslateRelativeTo,
PickAndDragHandlerShopEditor * apPickAndDragHandlerShopEditor)	{

	mp_DoubleSpinBox_TranslationX = ap_DoubleSpinBox_TranslationX;
	mp_DoubleSpinBox_TranslationY = ap_DoubleSpinBox_TranslationY;
	mp_DoubleSpinBox_TranslationZ = ap_DoubleSpinBox_TranslationZ;

	mp_DoubleSpinBox_ScalingX = ap_DoubleSpinBox_ScalingX,
	mp_DoubleSpinBox_ScalingY = ap_DoubleSpinBox_ScalingY,
	mp_DoubleSpinBox_ScalingZ = ap_DoubleSpinBox_ScalingZ,

	mp_ComboBox_DirectionOfTranslation = ap_ComboBox_DirectionOfTranslation;
	mp_ComboBox_TranslateRelativeTo = ap_ComboBox_TranslateRelativeTo;

	mpPickAndDragHandlerShopEditor = static_cast<PickAndDragHandlerShopEditor*>(apPickAndDragHandlerShopEditor);


	connect(mp_DoubleSpinBox_TranslationX,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPositionFromDlg()));
	connect(mp_DoubleSpinBox_TranslationY,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPositionFromDlg()));
	connect(mp_DoubleSpinBox_TranslationZ,SIGNAL(valueChanged(double)),
		this,SLOT(slotSetPropertiesPositionFromDlg()));

	connect(mp_ComboBox_DirectionOfTranslation,SIGNAL(currentTextChanged(const QString &)),
		mpPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));
	connect(mp_ComboBox_TranslateRelativeTo,SIGNAL(currentTextChanged(const QString &)),
		mpPickAndDragHandlerShopEditor,SLOT(slotSetTransformParams(const QString &)));
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotUpdatePickAndDragGUI() {
	connect(mpPickAndDragHandlerShopEditor,SIGNAL(signalPropertiesSettingsChanged(const osg::Matrixd & )),
		this,SLOT(slotSetPropertiesPosition(const osg::Matrixd & )));
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesPosition(const osg::Matrixd & amtrxPickedObject)	{
	mp_DoubleSpinBox_TranslationX->setValue(amtrxPickedObject(3,0));
	mp_DoubleSpinBox_TranslationY->setValue(amtrxPickedObject(3,1));
	mp_DoubleSpinBox_TranslationZ->setValue(amtrxPickedObject(3,2));
}

//--------------------------------------------------------------------------------------

void PickAndDragController::slotSetPropertiesPositionFromDlg()	{
	QDoubleSpinBox * pQDoubleSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
	if(pQDoubleSpinBox == mp_DoubleSpinBox_TranslationX ||
		pQDoubleSpinBox == mp_DoubleSpinBox_TranslationY ||
		pQDoubleSpinBox == mp_DoubleSpinBox_TranslationZ)	{
			setTranslationController();
	} else {
	}
}

//--------------------------------------------------------------------------------------

void PickAndDragController::setRotationController()	{
}

//--------------------------------------------------------------------------------------

void PickAndDragController::setTranslationController()	{
	osg::Vec3d vec3dPosition;

	vec3dPosition[0] = mp_DoubleSpinBox_TranslationX->value();
	vec3dPosition[1] = mp_DoubleSpinBox_TranslationY->value();
	vec3dPosition[2] = mp_DoubleSpinBox_TranslationZ->value();

	mpPickAndDragHandlerShopEditor->setPropertiesPosition(vec3dPosition);
}

//--------------------------------------------------------------------------------------

void PickAndDragController::setScalingController()	{
	osg::Vec3d vec3dScaling;

	vec3dScaling[0] = mp_DoubleSpinBox_TranslationX->value();
	vec3dScaling[1] = mp_DoubleSpinBox_TranslationY->value();
	vec3dScaling[2] = mp_DoubleSpinBox_TranslationZ->value();

	mpPickAndDragHandlerShopEditor->setPropertiesPosition(vec3dScaling);

}
