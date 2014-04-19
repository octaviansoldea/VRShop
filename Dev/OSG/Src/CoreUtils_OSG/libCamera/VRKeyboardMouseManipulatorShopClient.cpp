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
#include "VRKeyboardMouseManipulatorShopClient.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


KeyboardMouseManipulatorShopClient::KeyboardMouseManipulatorShopClient(int flags) :
KeyboardMouseManipulator(flags) {
	m_bFirstPerson = true;
	setViewPerspective(m_bFirstPerson);
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulatorShopClient::KeyboardMouseManipulatorShopClient
	(const KeyboardMouseManipulatorShopClient& cm, const CopyOp& copyOp) :
KeyboardMouseManipulator(cm, copyOp) {
	m_bFirstPerson = true;

	setViewPerspective(m_bFirstPerson);
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
	bool bRes = false;

	int nEventType = ea.getEventType();
	if ((nEventType != GUIEventAdapter::KEYDOWN) &&
		(nEventType != GUIEventAdapter::KEYUP)) {
			return bRes;
	} 
	bRes = KeyboardMouseManipulator::handle(ea, aa);
	if(bRes == false) {
		return(bRes);
	}

	if (ea.getKey() == '1')	{
		m_bFirstPerson = true;
		setViewPerspective(m_bFirstPerson);
	}

	if (ea.getKey() == '3')	{
		m_bFirstPerson = false;
		setViewPerspective(m_bFirstPerson);
	}

	return(bRes);
}

//-------------------------------------------------------------------------------

void KeyboardMouseManipulatorShopClient::setViewPerspective(bool abFirstPerson) {
	Vec3d vec3dEye, vec3dCenter, vec3dUp;
	getTransformation(vec3dEye, vec3dCenter, vec3dUp);

	const Vec3d & vec3dDiff = (vec3dCenter - vec3dEye);
	if (m_bFirstPerson == false)	{
		//3. person
		vec3dEye[0] = 
			(vec3dDiff[0] < 0) ? (vec3dEye[0]+sin(vec3dDiff[0])) : (vec3dEye[0]-sin(vec3dDiff[0]));
		vec3dEye[1] = 
			(vec3dDiff[1] < 0) ? (vec3dEye[1]+cos(vec3dDiff[0])) : (vec3dEye[1]-cos(vec3dDiff[0]));
		vec3dEye[2] = 3.5;
	} else {
		//1. person
		vec3dEye[0] = 
			(vec3dDiff[0] < 0) ? (vec3dEye[0]-sin(vec3dDiff[0])) : (vec3dEye[0]+sin(vec3dDiff[0]));
		vec3dEye[1] = 
			(vec3dDiff[1] < 0) ? (vec3dEye[1]-cos(vec3dDiff[0])) : (vec3dEye[1]+cos(vec3dDiff[0]));
		vec3dEye[2] = 1.5;
	}

	setTransformation(vec3dEye, vec3dCenter, vec3dUp);
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulatorShopClient::checkObstructionInFront(float aflDistance)	{
	bool bRes = true;

	return bRes;
}