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

#ifndef VR_KEYBOARD_MOUSE_MANIPULATOR_SHOP_CLIENT_H
#define VR_KEYBOARD_MOUSE_MANIPULATOR_SHOP_CLIENT_H

#include <QObject>
#include <osg/Node>

#include "VRKeyboardMouseManipulator.h"
#include <vector>

namespace VR {

	class KeyboardMouseManipulatorShopClient : public QObject, public KeyboardMouseManipulator	{
		Q_OBJECT
    public:

        KeyboardMouseManipulatorShopClient(int flags = DEFAULT_SETTINGS);
        KeyboardMouseManipulatorShopClient(const KeyboardMouseManipulatorShopClient& cm,
                             const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);
	private:
		virtual bool keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

		osg::BoundingBox getBoundingBox() const;

		void setViewPerspective(bool abFirstPerson);
		bool getViewPerspective() const;
		osg::Vec3d cameraPerspectiveCorrector() const;

		osg::Matrixd getAvatar2CameraMatrix();

		void setCameraPosition2Object(osg::Node * apNode);
		std::vector<osg::Matrixd> m_vecPredefinedViews;

	private:
		bool checkObstructionInFront(float aflDistance);

		bool m_bFirstPerson;
		osg::Matrixd setMatrixTransform(osg::Vec3d &avec3dEye,osg::Vec3d &avec3dCenter,osg::Vec3d &avec3dUp);
		osg::BoundingBox m_BoundingBox;

		float m_flCameraCorrector;

	signals:
		void signalCameraPositionOrHeadingDirectionChanged(bool abAnimation);
	};
}
#endif //VR_KEYBOARD_MOUSE_MANIPULATOR_SHOP_CLIENT_H