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

#ifndef VR_CAMERA_CONTROLLER_H
#define VR_CAMERA_CONTROLLER_H

#include <QObject>
class QComboBox;
class QPushButton;
class QDoubleSpinBox;
class QToolButton;

namespace VR {
	class KeyboardMouseManipulatorShopEditor;
	class KeyboardMouseManipulatorShopClient;

	struct CameraController : public QObject {
		CameraController(
			QComboBox * ap_ComboBox_PredefinedViewport,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionX,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionY,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraPositionZ,
			QPushButton * ap_PushButton_SetHomePositionDefault,
			QPushButton * ap_PushButton_HomePosition,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionX,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionY,
			QDoubleSpinBox * ap_DoubleSpinBox_CameraHeadingDirectionZ,
			QPushButton * ap_PushButton_SetCameraHeadingDirectionDefault,
			QPushButton * ap_PushButton_CameraHeadingDirection,
			VR::KeyboardMouseManipulatorShopEditor * aKeyboardMouseManipulatorShopEditor);

		//Client camera perspective
		CameraController(
			QToolButton * apToolButton1View,
			QToolButton * apToolButton3View,
			KeyboardMouseManipulatorShopClient * apKeyboardMouseManipulatorShopClient);


		public slots:
			void slotUpdateCameraGUI();

			void slotCameraHomePosition();

			void slotSetCameraPosition();
			void slotSetCameraPositionDefault();
			void slotSetCameraHeadingDirection();
			void slotSetCameraHeadingDirectionDefault();

	private:

		Q_OBJECT

		QComboBox * m_p_ComboBox_PredefinedViewport;

		QDoubleSpinBox * m_p_DoubleSpinBox_CameraPositionX;
		QDoubleSpinBox * m_p_DoubleSpinBox_CameraPositionY;
		QDoubleSpinBox * m_p_DoubleSpinBox_CameraPositionZ;
		QPushButton * m_p_PushButton_SetCameraPositionDefault;
		QPushButton * m_p_PushButton_CameraPosition;

		QDoubleSpinBox * m_p_DoubleSpinBox_CameraHeadingDirectionX;
		QDoubleSpinBox * m_p_DoubleSpinBox_CameraHeadingDirectionY;
		QDoubleSpinBox * m_p_DoubleSpinBox_CameraHeadingDirectionZ;
		QPushButton * m_p_PushButton_SetCameraHeadingDirectionDefault;
		QPushButton *  m_p_PushButton_CameraHeadingDirection;

		KeyboardMouseManipulatorShopEditor * m_pKeyboardMouseManipulatorShopEditor;

		//Client camera
		QToolButton * m_pToolButton1View;
		QToolButton * m_pToolButton3View;
		KeyboardMouseManipulatorShopClient * m_pKeyboardMouseManipulatorShopClient;

		private slots:
			void slotSetCameraPerspective(bool abIndicator);
	};
}
#endif //VR_CAMERA_CONTROLLER_H