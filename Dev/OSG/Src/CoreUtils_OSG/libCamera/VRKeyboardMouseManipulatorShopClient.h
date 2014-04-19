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

#include "VRKeyboardMouseManipulator.h"

namespace VR {

	class KeyboardMouseManipulatorShopClient : public QObject, public KeyboardMouseManipulator
	{
		typedef KeyboardMouseManipulator inherited;

		Q_OBJECT
    public:

        KeyboardMouseManipulatorShopClient(int flags = DEFAULT_SETTINGS);
        KeyboardMouseManipulatorShopClient(const KeyboardMouseManipulatorShopClient& cm,
                             const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

		void setViewPerspective(bool abFirstPerson);

	private:
		bool checkObstructionInFront(float aflDistance);

		bool m_bFirstPerson;
	};
}
#endif //VR_KEYBOARD_MOUSE_MANIPULATOR_SHOP_CLIENT_H