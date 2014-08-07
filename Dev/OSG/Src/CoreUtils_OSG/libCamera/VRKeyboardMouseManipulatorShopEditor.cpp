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

#include "BasicDefinitions.h"

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
	Matrixd prevCameraMatrix = getMatrix();

	bool bRes = KeyboardMouseManipulator::handle(ea, aa);
	if(bRes == false) {
		return(bRes);
	}
	
	Matrixd currentCameraMatrix = getMatrix();

	int iI, iJ;
	for(iI = 0; iI < 4; iI++)	{
		for(iJ = 0; iJ < 4; iJ++)	{
			if (fabs(prevCameraMatrix(iI,iJ) - currentCameraMatrix(iI,iJ)) > EPS)	{

				//Emit signal only if there was a change in the matrix
				emit signalCameraPositionOrHeadingDirectionChanged();
				return true;
			}
		}
	}
 
	return(bRes);
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopEditor::slotSetPredefinedViewport(const QString & astrText) {
	const QString & strText = astrText;
	osg::Vec3d vec3dEye, vec3dCenter(osg::Vec3d(0,0,0)), vec3dUp(osg::Vec3d(0,0,1));

	if (strText == "Front")	{
		vec3dEye[0] = 0.0;
		vec3dEye[1] = -10.0;
		vec3dEye[2] = 0.0;
	} else if (strText == "Rear")	{
		vec3dEye[0] = 0.0;
		vec3dEye[1] = 10.0;
		vec3dEye[2] = 0.0;
	} else if (strText == "Left")	{
		vec3dEye[0] = -10.0;
		vec3dEye[1] = 0.0;
		vec3dEye[2] = 0.0;
	} else if (strText == "Right")	{
		vec3dEye[0] = 10.0;
		vec3dEye[1] = 0.0;
		vec3dEye[2] = 0.0;
	} else if (strText == "Top-Down")	{
		vec3dEye[0] = 0.0;
		vec3dEye[1] = 0.0;
		vec3dEye[2] = 20.0;
	}

	emit signalCameraPositionOrHeadingDirectionChanged();
	setTransformation(vec3dEye, vec3dCenter, vec3dUp);
}
