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

#include <osg/Matrix>
#include <osg/Vec3d>

class QComboBox;
class QDoubleSpinBox;

namespace VR {
	class PickAndDragHandlerShopEditor;
	
	struct PickAndDragController : public QObject {
		PickAndDragController(
			QDoubleSpinBox * ap_DoubleSpinBox_TranslationX,
			QDoubleSpinBox * ap_DoubleSpinBox_TranslationY,
			QDoubleSpinBox * ap_DoubleSpinBox_TranslationZ,

			QDoubleSpinBox * ap_DoubleSpinBox_ScalingX,
			QDoubleSpinBox * ap_DoubleSpinBox_ScalingY,
			QDoubleSpinBox * ap_DoubleSpinBox_ScalingZ,

			QComboBox * ap_ComboBox_DirectionOfTranslation,
			QComboBox * ap_ComboBox_TranslateRelativeTo,

			PickAndDragHandlerShopEditor * apPickAndDragHandlerShopEditor);

	public slots:
		void slotUpdatePickAndDragGUI();

		void slotSetPropertiesPosition(const osg::Matrixd & amtrxMatrix);
		void slotSetPropertiesPositionFromDlg();

	private:
		Q_OBJECT

		QDoubleSpinBox * mp_DoubleSpinBox_TranslationX;
		QDoubleSpinBox * mp_DoubleSpinBox_TranslationY;
		QDoubleSpinBox * mp_DoubleSpinBox_TranslationZ;

		QDoubleSpinBox * mp_DoubleSpinBox_ScalingX;
		QDoubleSpinBox * mp_DoubleSpinBox_ScalingY;
		QDoubleSpinBox * mp_DoubleSpinBox_ScalingZ;

		QComboBox * mp_ComboBox_DirectionOfTranslation;
		QComboBox * mp_ComboBox_TranslateRelativeTo;

		PickAndDragHandlerShopEditor * mpPickAndDragHandlerShopEditor;

		void setRotationController();
		void setTranslationController();
		void setScalingController();

	};
}
#endif //VR_PICK_AND_DRAG_CONTROLLER_H