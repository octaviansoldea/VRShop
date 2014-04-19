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

#include "VRKeyboardMouseManipulator.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


KeyboardMouseManipulator::KeyboardMouseManipulator(int flags) : inherited( flags ),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.1)
{
	setVerticalAxisFixed(false);

	m_dbDirectionRotationRate	= 0.0;
	m_dbTranslationFactorZ		= 0.0;
	m_dbTranslationFactorX		= 0.0;

	m_dbDefaultMoveSpeed = 1;
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulator::KeyboardMouseManipulator(const KeyboardMouseManipulator& cm, const CopyOp& copyOp) :
	Object(cm, copyOp),
    inherited(cm, copyOp),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.1)

{
	m_dbDirectionRotationRate	= 0.0;
	m_dbTranslationFactorZ		= 0.0;
	m_dbTranslationFactorX		= 0.0;

	m_dbDefaultMoveSpeed = 1.0;
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
		bRes = VR::KeyboardMouseManipulator::keyDown(ea, aa);
	}

	if (nResEvent == GUIEventAdapter::KEYUP)	{
		bRes = VR::KeyboardMouseManipulator::keyUp(ea, aa);
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
	int bRes = true;

	int nResKey = ea.getKey();
	if ((nResKey ==	osgGA::GUIEventAdapter::KEY_Control_L) ||
		(nResKey ==	osgGA::GUIEventAdapter::KEY_Control_R))	{
			m_bCtrl = true;
	}

	if ((nResKey ==	osgGA::GUIEventAdapter::KEY_Shift_L) ||
		(nResKey ==	osgGA::GUIEventAdapter::KEY_Shift_R))	{
			m_bShift = true;
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Up)	{
		if(m_bCtrl)	{ //Move forward
			m_dbForwardFactor = 0.01 * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			zoomModel(m_dbForwardFactor);
		} else { //Rotate view (but not direction of travel) up.
			m_dbTranslationFactorX = m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0,m_dbTranslationFactorX);
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Down)	{
		if(m_bCtrl)	{ //Move backwards
			m_dbForwardFactor = -0.01 * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			zoomModel(m_dbForwardFactor);
		} else { //Rotate view (but not direction of travel) down.
			m_dbTranslationFactorX = -m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0,m_dbTranslationFactorX);
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Right)	{
		if (m_bCtrl)	{	//Translate camera right
			m_dbTranslationFactorZ = m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbTranslationFactorZ,0.0);
		} else {	//Rotate cameram right
			m_dbDirectionRotationRate = - m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d dbvecDirection = prevCenter-prevEye;

			Vec3d normalized = dbvecDirection * Matrix::rotate(DegreesToRadians(m_dbDirectionRotationRate),prevUp);
			Vec3d newCenter = prevEye+normalized;

			setTransformation(prevEye, newCenter, prevUp);	
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Left)	{
		if (m_bCtrl)	{	//Translate camera to the left.
			m_dbTranslationFactorZ = -m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbTranslationFactorZ,0.0);
		} else {	//Rotate camera to the left
			m_dbDirectionRotationRate = m_cdbRotationFactor * 
				(m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);

			Vec3d prevCenter, prevEye, prevUp;
			getTransformation(prevEye, prevCenter, prevUp);
			Vec3d dbvecDirection = prevCenter-prevEye;

			Vec3d normalized = dbvecDirection * Matrix::rotate(DegreesToRadians(m_dbDirectionRotationRate),prevUp);
			Vec3d newCenter = prevEye+normalized;

			setTransformation(prevEye, newCenter, prevUp);
		}
	}

	if (nResKey == ' ')	{
		home(ea.getTime());
	} else	{
		bRes = false;
	}

	return(bRes);
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulator::keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)	{
	int bRes = true;

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
