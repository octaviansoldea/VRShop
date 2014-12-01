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

/*
	LEGEND:
		SHIFT:			acceleration

		KEYUP:			move UP
		KEYDOWN:		move DOWN
		
		KEYUP+CTRL:		move FORWARD
		KEYDOWN+CTRL:	move BACKWARD

		KEYLEFT:		rotation LEFT
		KEYRIGHT:		rotation RIGHT
		KEYLEFT+CTRL:	translation LEFT
		KEYRIGHT+CTRL:	translation RIGHT
*/

#include <osgGA/GUIEventAdapter>

#include "VRKeyboardMouseManipulator.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


KeyboardMouseManipulator::KeyboardMouseManipulator(int flags) : 
osgGA::OrbitManipulator(flags),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.1)	{
	setVerticalAxisFixed(false);

	m_dbDirectionRotationRate = 0.0;
	m_dbTranslationFactorZ = 0.0;
	m_dbTranslationFactorX = 0.0;
	m_dbDefaultMoveSpeed = 1.0;

	setAutoComputeHomePosition(false);
	setHomePosition(Vec3d(0,-10,1.5),Vec3d(0,0,0),Vec3d(0,0,1));
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulator::KeyboardMouseManipulator(const KeyboardMouseManipulator& cm, const CopyOp& copyOp) :
Object(cm, copyOp),
osgGA::OrbitManipulator(cm, copyOp),
m_bCtrl(cm.m_bCtrl),
m_bShift(cm.m_bShift),
m_cdbRotationFactor(cm.m_cdbRotationFactor)	{
	m_dbDirectionRotationRate = cm.m_dbDirectionRotationRate;
	m_dbTranslationFactorZ = cm.m_dbTranslationFactorZ;
	m_dbTranslationFactorX = cm.m_dbTranslationFactorX;

	m_dbDefaultMoveSpeed = cm.m_dbDefaultMoveSpeed;
	setAutoComputeHomePosition(cm.getAutoComputeHomePosition());

	Vec3d vec3dEye, vec3dCenter, vec3dUp;
	cm.getHomePosition(vec3dEye, vec3dCenter, vec3dUp);
	setHomePosition(vec3dEye, vec3dCenter, vec3dUp);
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)	{
	bool bRes = false;

	int nResEvent = ea.getEventType();

	if (nResEvent == GUIEventAdapter::FRAME)	{
		bRes = OrbitManipulator::handleFrame(ea, aa);
	}

	if (nResEvent == GUIEventAdapter::RELEASE)	{
		bRes = OrbitManipulator::handleMouseRelease(ea, aa);
	}

	if (nResEvent == GUIEventAdapter::PUSH)	{
		bRes = OrbitManipulator::handleMousePush(ea, aa);
	}

	if (nResEvent == GUIEventAdapter::KEYDOWN)	{
		bRes = keyDown(ea, aa);
	}

	if (nResEvent == GUIEventAdapter::KEYUP)	{
		bRes = keyUp(ea, aa);
	}

	if(ea.getHandled())
		return false;

	if (nResEvent == GUIEventAdapter::DRAG)	{
		bRes = OrbitManipulator::handleMouseDrag(ea, aa);		
	}

//	return(bRes);
	return true;
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulator::keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)	{
	bool bRes = true;

	int nResKey = ea.getKey();
	if ((nResKey == GUIEventAdapter::KEY_Control_L) ||
		(nResKey == GUIEventAdapter::KEY_Control_R))	{
		m_bCtrl = true;
	}

	if ((nResKey == GUIEventAdapter::KEY_Shift_L) ||
		(nResKey == GUIEventAdapter::KEY_Shift_R))	{
		m_bShift = true;
	}

	//Go UP/DOWN
	if ((nResKey == GUIEventAdapter::KEY_F) || (nResKey == GUIEventAdapter::KEY_S))	{
		int nDirection = -1;	//DOWN
		if (nResKey == GUIEventAdapter::KEY_F)
			nDirection = 1;	//UP

		m_dbTranslationFactorX = nDirection * m_cdbRotationFactor *
			(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

		panModel(0.0, m_dbTranslationFactorX);
	}

	//Move forward/backward
	if ((nResKey == GUIEventAdapter::KEY_Up) || (nResKey == GUIEventAdapter::KEY_Down))	{		
		m_dbForwardFactor = 0.5 * (m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

		Vec3d prevCenter, prevEye, prevUp;
		getTransformation(prevEye, prevCenter, prevUp);
		Vec3d dbvecDirection = prevCenter - prevEye;
		dbvecDirection.z()=0;
		dbvecDirection.normalize();

		int nDirection = -1;	//Backward
		if (nResKey == GUIEventAdapter::KEY_Up)
			nDirection = 1;	//Forward

		Vec3d newEye = prevEye + Vec3d(dbvecDirection.x(), dbvecDirection.y(), 0.0)*nDirection;
		Vec3d newCenter = prevCenter + Vec3d(dbvecDirection.x(), dbvecDirection.y(), 0.0)*nDirection;

		setTransformation(newEye, newCenter, prevUp);
	}

	if ((nResKey == GUIEventAdapter::KEY_Right) ||
		((nResKey == GUIEventAdapter::KEY_Left))) {

		double dbDir = 1.0;
		if (nResKey == GUIEventAdapter::KEY_Left) {
			dbDir = -1.0;
		}

		if (m_bCtrl)	{	//Translate camera right
			m_dbTranslationFactorZ = dbDir * m_cdbRotationFactor *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbTranslationFactorZ, 0.0);
		}
		else {	//Rotate camera to the right
			m_dbDirectionRotationRate = dbDir  * (- m_cdbRotationFactor) *
				(m_bShift ? (m_dbDefaultMoveSpeed *= 1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d vecdbDirection = prevCenter - prevEye;

			Vec3d normalized = vecdbDirection * Matrix::rotate(DegreesToRadians(m_dbDirectionRotationRate), prevUp);
			Vec3d newCenter = prevEye + normalized;
			setTransformation(prevEye, newCenter, prevUp);
		}

	}

	if (nResKey == ' ')	{
		home(0);
	} else	{
		bRes = false;
	}

	return(bRes);
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulator::keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)	{
	bool bRes = true;

	int nResKey = ea.getKey();
	if ((nResKey ==	osgGA::GUIEventAdapter::KEY_Control_L) ||
		(nResKey ==	osgGA::GUIEventAdapter::KEY_Control_R))	{
			m_bCtrl = false;
	}

	if ((nResKey ==	osgGA::GUIEventAdapter::KEY_Shift_L) ||
		(nResKey ==	osgGA::GUIEventAdapter::KEY_Shift_R))	{
		m_bShift = false;
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Up) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Down))	{
		m_dbForwardFactor = 0.0;
		m_dbTranslationFactorX = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Left) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Right))	{
		m_dbDirectionRotationRate = 0.0;
		m_dbTranslationFactorZ = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}

	return(bRes);
}

//-------------------------------------------------------------------------------
