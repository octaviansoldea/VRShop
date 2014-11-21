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


class QComboBox;
class QDoubleSpinBox;

namespace VR {
	class PickAndDragHandlerShopEditor;
	
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

			PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor);	//End of constructor


	public slots:
		void slotUpdatePickAndDragGUI();

		void slotSetPropertiesPosition();
		void slotSetPropertiesRotation();
		void slotSetPropertiesScaling();

	private:
		Q_OBJECT

		QDoubleSpinBox * m_pDoubleSpinBoxTranslationX;
		QDoubleSpinBox * m_pDoubleSpinBoxTranslationY;
		QDoubleSpinBox * m_pDoubleSpinBoxTranslationZ;

		QDoubleSpinBox * m_pDoubleSpinBoxScalingX;
		QDoubleSpinBox * m_pDoubleSpinBoxScalingY;
		QDoubleSpinBox * m_pDoubleSpinBoxScalingZ;
		QDoubleSpinBox * m_pDoubleSpinBoxRotationX;
		QDoubleSpinBox * m_pDoubleSpinBoxRotationY;
		QDoubleSpinBox * m_pDoubleSpinBoxRotationZ;

		QComboBox * m_pComboBoxDirectionOfTranslation;
		QComboBox * m_pComboBoxTranslateRelativeTo;

		PickAndDragHandlerShopEditor * m_pPickAndDragHandlerShopEditor;
	};
}
#endif //VR_PICK_AND_DRAG_CONTROLLER_H