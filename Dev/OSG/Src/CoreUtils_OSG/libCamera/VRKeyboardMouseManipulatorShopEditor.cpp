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

#include "BasicDefinitions.h"
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

	double dbSumAbsDiff = 0.0;

	int iI, iJ;
	for(iI = 0; iI < 4; iI++) {
		for(iJ = 0; iJ < 4; iJ++) {
			dbSumAbsDiff += fabs(prevCameraMatrix(iI,iJ) - currentCameraMatrix(iI,iJ));
		}
	}
 
	//Emit signal only if there was a change in the matrix
	if (dbSumAbsDiff > EPS)	{
		emit signalCameraPositionOrHeadingDirectionChanged();
	}

	return(bRes);
}

//-------------------------------------------------------------------------------