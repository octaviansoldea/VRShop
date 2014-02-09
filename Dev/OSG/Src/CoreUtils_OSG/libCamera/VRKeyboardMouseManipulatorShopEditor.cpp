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

/* Modified by Matej Steinbacher and Octavian Soldea */

#include <osgGA/GUIEventAdapter>

#include "VRKeyboardMouseManipulatorShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


KeyboardMouseManipulatorShopEditor::KeyboardMouseManipulatorShopEditor(int flags) :
KeyboardMouseManipulator(flags) {
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulatorShopEditor::KeyboardMouseManipulatorShopEditor(const KeyboardMouseManipulatorShopEditor& cm, const CopyOp& copyOp) :
KeyboardMouseManipulator(cm, copyOp) {
}

//-------------------------------------------------------------------------------
bool KeyboardMouseManipulatorShopEditor::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
	bool bRes = KeyboardMouseManipulator::handle(ea, aa);
	if(bRes == false) {
		return(bRes);
	}
	int nResEvent = ea.getEventType();

	if (nResEvent == GUIEventAdapter::DRAG)	{
		emit signalCameraPositionOrHeadingDirectionChanged();
	}
	return(bRes);
}

////-------------------------------------------------------------------------------