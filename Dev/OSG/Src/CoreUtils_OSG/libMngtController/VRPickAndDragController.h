/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
*
* This library is open source and may be redistributed and/or modified under
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* OpenSceneGraph Public License for more details.
*/

#ifndef VR_PICK_AND_DRAG_CONTROLLER_H
#define VR_PICK_AND_DRAG_CONTROLLER_H

#include <QObject>

#include "VRAbstractObject.h"

class QComboBox;
class QDoubleSpinBox;
class QPushButton;

namespace VR {
	class PickAndDragHandlerShopEditor;
	class Scene;
	
	struct PickAndDragController : public QObject {
		PickAndDragController(
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
			osg::ref_ptr<Scene> a_pScene);	//End of constructor

		PickAndDragController(
			QPushButton * a_pPushButton_ModifyScene_DuplicateSelection,
			QPushButton * a_pPushButton_ModifyScene_DeleteSelection,
			QPushButton * a_pPushButton_ModifyScene_SplitItem,
			QPushButton * a_pPushButton_ModifyScene_GroupItems,

			PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
			osg::ref_ptr<Scene> a_pScene);	//End of constructor

	public slots:
		void slotUpdatePickAndDragGUI();

		void slotSetPropertiesPosition();
		void slotSetPropertiesRotation();
		void slotSetPropertiesScaling();

		void slotGroupItems();
		void slotSplitItem();
		void slotDuplicateSelection();
		void slotRemoveSelection();

	private:
		Q_OBJECT

		QDoubleSpinBox * mp_DoubleSpinBox_TranslationX;
		QDoubleSpinBox * mp_DoubleSpinBox_TranslationY;
		QDoubleSpinBox * mp_DoubleSpinBox_TranslationZ;

		QDoubleSpinBox * mp_DoubleSpinBox_ScalingX;
		QDoubleSpinBox * mp_DoubleSpinBox_ScalingY;
		QDoubleSpinBox * mp_DoubleSpinBox_ScalingZ;
		QDoubleSpinBox * mp_DoubleSpinBox_RotationX;
		QDoubleSpinBox * mp_DoubleSpinBox_RotationY;
		QDoubleSpinBox * mp_DoubleSpinBox_RotationZ;

		QComboBox * mp_ComboBox_DirectionOfTranslation;
		QComboBox * mp_ComboBox_TranslateRelativeTo;

		QPushButton * mp_PushButton_ModifyScene_DuplicateSelection;
		QPushButton * mp_PushButton_ModifyScene_DeleteSelection;
		QPushButton * mp_PushButton_ModifyScene_SplitItem;
		QPushButton * mp_PushButton_ModifyScene_GroupItems;

		PickAndDragHandlerShopEditor * mpPickAndDragHandlerShopEditor;

		osg::ref_ptr<Scene> mp_Scene;
	};
}
#endif //VR_PICK_AND_DRAG_CONTROLLER_H