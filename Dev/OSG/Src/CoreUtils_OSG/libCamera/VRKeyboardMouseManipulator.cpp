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

/* Written by Don Burns */

#include <iostream>

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
	m_dbPitchOffsetRate			= 0.0;
	m_dbPitchOffset				= 0.0;
	m_dbLateralRotationRate		= 0.0;

	m_dbDefaultMoveSpeed = 1;
}

//-------------------------------------------------------------------------------

KeyboardMouseManipulator::KeyboardMouseManipulator(const KeyboardMouseManipulator& cm, const CopyOp& copyOp) :
	Object(cm, copyOp),
    inherited(cm, copyOp),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.001)

{
	m_dbDirectionRotationRate	= 0.0;
	m_dbPitchOffsetRate			= 0.0;
	m_dbPitchOffset				= 0.0;
	m_dbLateralRotationRate		= 0.0;

	m_dbDefaultMoveSpeed = 1.0;
}

//-------------------------------------------------------------------------------

bool KeyboardMouseManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)	{
	bool bRes = true;

	int nResEvent = ea.getEventType();

	cout << "KeyboardMouseManipulator::handle "<< endl;

	//Orbit manipulator
	if(nResEvent == GUIEventAdapter::EventType::DRAG ||
		GUIEventAdapter::EventType::MOVE ||
		GUIEventAdapter::EventType::PUSH ||
		GUIEventAdapter::EventType::RELEASE ||
		GUIEventAdapter::EventType::SCROLL) {

			cout << "nResEvent == GUIEventAdapter::EventType::DRAG "<< endl;
			bRes = OrbitManipulator::handle(ea,us);
	}

	if(nResEvent == GUIEventAdapter::KEYDOWN) {
		cout << "nResEvent == GUIEventAdapter::KEYDOWN "<< endl;
		bRes = keyDown(ea, us);
	}
	else if(nResEvent == GUIEventAdapter::KEYUP)	{
		cout << "nResEvent == GUIEventAdapter::KEYUP "<< endl;
		bRes = keyUp(ea, us);
	}
	return(bRes);
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
			m_dbForwardFactor = m_bShift ? 0.01*(m_dbDefaultMoveSpeed*=1.1) : 0.01*m_dbDefaultMoveSpeed;
			zoomModel(m_dbForwardFactor);
		} else { //Rotate view (but not direction of travel) up.
			m_dbLateralRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0,m_dbLateralRotationRate);
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Down)	{
		if(m_bCtrl)	{ //Move backwards
			m_dbForwardFactor = m_bShift ? -0.01*(m_dbDefaultMoveSpeed*=1.1) : -0.01*m_dbDefaultMoveSpeed;
			zoomModel(m_dbForwardFactor);
		} else { //Rotate view (but not direction of travel) down.
			m_dbLateralRotationRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(0.0,m_dbLateralRotationRate);
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Right)	{
		if(m_bCtrl)	{	//Translate camera
			m_dbPitchOffsetRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbPitchOffsetRate,0.0);
		} else {	//Rotate camera
			m_dbDirectionRotationRate = - m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);

			if( fabs( m_dbDirectionRotationRate ) > 0.0001 )	{
				Vec3d prevCenter, prevEye, prevUp;
				getTransformation(prevEye, prevCenter, prevUp);
				Vec3d dbvecDirection = prevCenter-prevEye;

				Vec3d normalized = dbvecDirection * osg::Matrix::rotate(osg::DegreesToRadians(m_dbDirectionRotationRate),prevUp);
				Vec3d newCenter = prevEye+normalized;

				setTransformation(prevEye, newCenter, prevUp);	
			}
		}
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Left)	{
		if(m_bCtrl)	{	//Translate view left.
			m_dbPitchOffsetRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			panModel(m_dbPitchOffsetRate,0.0);
		}
		else	{	//Rotate camera
			m_dbDirectionRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
			if( fabs( m_dbDirectionRotationRate ) > 0.0001 )	{
				Vec3d prevCenter, prevEye, prevUp;
				getTransformation(prevEye, prevCenter, prevUp);
				Vec3d dbvecDirection = prevCenter-prevEye;

				Vec3d normalized = dbvecDirection * osg::Matrix::rotate(osg::DegreesToRadians(m_dbDirectionRotationRate),prevUp);
				Vec3d newCenter = prevEye+normalized;

				setTransformation(prevEye, newCenter, prevUp);	
			}
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
		m_dbDefaultMoveSpeed = 1;
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Up) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Down))	{
		m_dbForwardFactor = 0.0;
		m_dbLateralRotationRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}

	if ((nResKey == osgGA::GUIEventAdapter::KEY_Left) ||
		(nResKey == osgGA::GUIEventAdapter::KEY_Right))	{
		m_dbDirectionRotationRate = 0.0;
		m_dbPitchOffsetRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}

	return(bRes);
}

//-------------------------------------------------------------------------------
