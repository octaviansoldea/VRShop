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
#include <cassert>

#include <osg/io_utils>
#include <osgGA/GUIEventAdapter>
#include <osgUtil/LineSegmentIntersector>
#include <osg/BoundsChecking>

#include "OSGCameraManipulator.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


OSGCameraManipulator::OSGCameraManipulator(int flags) : inherited( flags ),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.001)
{
	setVerticalAxisFixed(false);

	m_dbDirectionRotationRate	= 0.0;
	m_dbPitchOffsetRate			= 0.0;
	m_dbPitchOffset				= 0.0;
	m_dbLateralRotationRate		= 0.0;

	m_dbDefaultMoveSpeed = 1;
}

//-------------------------------------------------------------------------------

OSGCameraManipulator::OSGCameraManipulator(const OSGCameraManipulator& om, const CopyOp& copyOp) :
	Object(om, copyOp),
    inherited(om, copyOp),
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.001)

{
	m_dbDirectionRotationRate	= 0.0;
	m_dbPitchOffsetRate			= 0.0;
	m_dbPitchOffset				= 0.0;
	m_dbLateralRotationRate		= 0.0;

	m_dbDefaultMoveSpeed = 1;
}

//-------------------------------------------------------------------------------

bool OSGCameraManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)	{
	bool bRes = true;

	//Orbit manipulator
	bRes = OrbitManipulator::handle(ea,us);

	int nResEvent = ea.getEventType();
	if(nResEvent == GUIEventAdapter::KEYDOWN) {
		bRes = keyDown(ea, us);
	}
	else if(nResEvent == GUIEventAdapter::KEYUP)	{
		bRes = keyUp(ea, us);
	}
	return(bRes);
}

//-------------------------------------------------------------------------------

bool OSGCameraManipulator::keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)	{
	int bRes = true;

	int nResKey = ea.getKey();
	if (nResKey ==	osgGA::GUIEventAdapter::KEY_Control_L ||
					osgGA::GUIEventAdapter::KEY_Control_R)	{
		m_bCtrl = true;
	}

	if (nResKey ==	osgGA::GUIEventAdapter::KEY_Shift_L ||
					osgGA::GUIEventAdapter::KEY_Shift_R)	{
		m_bShift = true;
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Up)	{
		if(m_bCtrl)	{		
			m_dbForwardFactor = m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed;
		}
		else	{ //Rotate view (but not direction of travel) up.
			m_dbLateralRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Down)	{
		if(m_bCtrl)	{	
			m_dbForwardFactor = m_bShift ? -(m_dbDefaultMoveSpeed*=1.1) : -m_dbDefaultMoveSpeed;
		}
		else	{ //Rotate view (but not direction of travel) down.
			m_dbLateralRotationRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Right)	{
		if(m_bCtrl)	{
			m_dbPitchOffsetRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		else	{	//Rotate view (but not direction of travel) right.
			m_dbDirectionRotationRate = - m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
	}

	if (nResKey == osgGA::GUIEventAdapter::KEY_Left)	{
		if(m_bCtrl)	{
			m_dbPitchOffsetRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		else	{	//Rotate view (but not direction of travel) left.
			m_dbDirectionRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
	}

	if (nResKey == ' ')	{
		home(ea.getTime());
		updateMatrices();
	}

	if (nResKey == 1)	{
		setCameraPosition();
		updateMatrices();
	}
	else	{
		bRes = false;
	}
	return(bRes);
}

//-------------------------------------------------------------------------------

bool OSGCameraManipulator::keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa)	{
	int bRes = true;

	int nResKey = ea.getKey();
	if (nResKey == osgGA::GUIEventAdapter::KEY_Control_L ||
		osgGA::GUIEventAdapter::KEY_Control_R)	{
			m_bCtrl = false;
	}

	else if (nResKey == osgGA::GUIEventAdapter::KEY_Shift_L ||
		osgGA::GUIEventAdapter::KEY_Shift_R)	{
		m_bShift = false;
//		m_dbDefaultMoveSpeed = 1;
	}

	else if (nResKey == osgGA::GUIEventAdapter::KEY_Up ||
		osgGA::GUIEventAdapter::KEY_Down)	{
		m_dbForwardFactor = 0.0;
		m_dbLateralRotationRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}

	else if (nResKey == osgGA::GUIEventAdapter::KEY_Left ||
		osgGA::GUIEventAdapter::KEY_Right)	{
		m_dbDirectionRotationRate = 0.0;
		m_dbPitchOffsetRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
	}
	else {
		bRes = false;
	}
	return(bRes);
}

//-------------------------------------------------------------------------------

void OSGCameraManipulator::updateMatrices()	{
	//osg::CoordinateFrame cf(getCoordinateFrame(m_vecdbPosition));
	//osg::Vec3d upVec(getUpVector(cf));

	//osg::Matrix mtrxRotate = osg::Matrix::rotate(
	//					m_dbLateralRotationRate,	getSideVector(cf),
	//					0.0,						getFrontVector(cf),
	//					m_dbDirectionRotationRate,	upVec);

	//m_vecdbDirection = m_vecdbDirection * mtrxRotate;

	//m_vecdbPosition += (m_vecdbDirection * m_dbForwardFactor);

	//m_dbPitchOffset += m_dbPitchOffsetRate;
	//if(m_dbPitchOffset >= osg::PI || m_dbPitchOffset < -osg::PI)
	//	m_dbPitchOffset *= -1;

	//m_mtrxdbOffset = osg::Matrix::rotate(
	//					0.0,			getSideVector(cf),
	//					m_dbPitchOffset,getFrontVector(cf),
	//					0.0,			upVec);

	//m_mtrxdbInverseMatrix.makeLookAt(m_vecdbPosition, m_vecdbPosition + m_vecdbDirection, upVec);
	//m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);
}


//-------------------------------------------------------------------------------

void OSGCameraManipulator::setCameraPosition()	{
}
