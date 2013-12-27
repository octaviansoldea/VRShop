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

#include <osgGA/GUIEventAdapter>

#include <iostream>

#include "OSGCameraManipulator.h"

using namespace osgGA;
using namespace osg;
using namespace VR;

OSGCameraManipulator::OSGCameraManipulator():
m_bCtrl(false),
m_bShift(false),
m_cdbRotationFactor(osg::PI*0.001)
{
	m_dbDirectionRotationRate	= 0.0;
	m_dbPitchOffsetRate			= 0.0;
	m_dbPitchOffset				= 0.0;
	m_dbLateralRotationRate		= 0.0;

	m_dbDefaultMoveSpeed = 1;
	
	m_mtrxdbOffset.makeIdentity();

	m_vecdbDirection.set(0,1,0);
}

OSGCameraManipulator::~OSGCameraManipulator()	{
}

void OSGCameraManipulator::setNode(osg::Node *node)	{
	m_pNode = node;

	if (getAutoComputeHomePosition())
		computeHomePosition();

	home(0.0);
}

const osg::Node* OSGCameraManipulator::getNode() const	{
	return m_pNode.get();
}

osg::Node* OSGCameraManipulator::getNode()	{
	return m_pNode.get();
}


const char* OSGCameraManipulator::className() const	{
	return "OSGCameraManipulator";
}

void OSGCameraManipulator::setByMatrix(const osg::Matrixd &mat)	{
	m_mtrxdbInverseMatrix = mat;
	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);

	m_vecdbPosition.set( m_mtrxdbInverseMatrix(3,0), m_mtrxdbInverseMatrix(3,1), m_mtrxdbInverseMatrix(3,2 ));
	osg::Matrix R(m_mtrxdbInverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	m_vecdbDirection = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame
}

void OSGCameraManipulator::setByInverseMatrix( const osg::Matrixd &invmat)	{
	m_mtrxdbMatrix = invmat;
	m_mtrxdbInverseMatrix.invert(m_mtrxdbMatrix);

	m_vecdbPosition.set(m_mtrxdbInverseMatrix(3,0), m_mtrxdbInverseMatrix(3,1), m_mtrxdbInverseMatrix(3,2));
	osg::Matrix R(m_mtrxdbInverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	m_vecdbDirection = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame
}

osg::Matrixd OSGCameraManipulator::getMatrix() const	{
	return (osg::Matrix::inverse(m_mtrxdbOffset) * m_mtrxdbMatrix);
}

osg::Matrixd OSGCameraManipulator::getInverseMatrix() const	{
	return (m_mtrxdbInverseMatrix * m_mtrxdbOffset);
}

void OSGCameraManipulator::computeHomePosition()	{
	_homeCenter = osg::Vec3(0.0, 0.0, 0.0);
	_homeEye = osg::Vec3(0.0, 10.0, 0.0);

	setHomePosition(-_homeEye, _homeCenter, _homeUp);

	m_vecdbPosition = _homeEye;
	m_vecdbDirection = _homeCenter - _homeEye;
	m_vecdbDirection.normalize();
	m_mtrxdbInverseMatrix.makeLookAt(_homeEye, _homeCenter, _homeUp);
	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);

	m_mtrxdbOffset.makeIdentity();

	m_dbDirectionRotationRate = 0.0;
	m_dbPitchOffset = 0.0;
	m_dbPitchOffsetRate = 0.0;
	m_dbLateralRotationRate = 0.0;
	m_dbForwardFactor = 0.0;
}

void OSGCameraManipulator::init(const GUIEventAdapter&, GUIActionAdapter&)	{
}

void OSGCameraManipulator::home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)	{
	home(ea.getTime());
	aa.requestRedraw();
	aa.requestContinuousUpdate(false);
}

void OSGCameraManipulator::home(double)	{
	if (!getAutoComputeHomePosition())
		computeHomePosition();
}

//----------------------------------------------------------------------------------------

void OSGCameraManipulator::setCameraPosition()	{
	_homeEye = m_vecdbPosition;

	Vec3d lv( _homeCenter - _homeEye );

    Vec3d f( lv );
    f.normalize();
    Vec3d s( f^_homeUp );
    s.normalize();
    Vec3d u( s^f );
    u.normalize();

    osg::Matrixd rotation_matrix( s[0], u[0], -f[0], 0.0f,
                            s[1], u[1], -f[1], 0.0f,
                            s[2], u[2], -f[2], 0.0f,
                            0.0f, 0.0f,  0.0f, 1.0f );

    double _distance = lv.length();
	osg::Quat _rotation = rotation_matrix.getRotate().inverse();

    _homeEye = _homeCenter + _rotation * osg::Vec3d( 0., 0., _distance );
    _homeUp = _rotation * osg::Vec3d( 0., 1., 0. );

//===============================================================================================================
//	double distance = sqrt(pow(m_mtrxdbMatrix(3,0),2)+pow(m_mtrxdbMatrix(3,1),2)+pow(m_mtrxdbMatrix(3,2),2));
//
//    _homeCenter = _homeEye + m_mtrxdbMatrix * osg::Vec3d( 0., 0., -distance);
//
//
//
//	m_vecdbPosition = _homeEye;
//	m_vecdbDirection = _homeCenter - _homeEye;
//	m_vecdbDirection.normalize();


//	m_mtrxdbInverseMatrix.makeLookAt(_homeEye, _homeCenter, _homeUp);
	_homeCenter += osg::Vec3d(100,100,1) * osg::Matrix::rotate(DegreesToRadians(45.0),osg::Z_AXIS);

	m_mtrxdbInverseMatrix.makeLookAt(_homeEye , _homeCenter, _homeUp);
	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);

	m_mtrxdbOffset.makeIdentity();
}

//----------------------------------------------------------------------------------------

bool OSGCameraManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &us)	{
	int nButton = ea.getEventType();
	switch(nButton)	{
	case osgGA::GUIEventAdapter::KEYUP:
		return keyUp(ea, us);

	case osgGA::GUIEventAdapter::KEYDOWN:
		return keyDown(ea, us);
          
	default:
		return false;
	}
}


bool OSGCameraManipulator::keyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter & aa)	{
	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		m_bCtrl = false;
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Shift_L:
	case osgGA::GUIEventAdapter::KEY_Shift_R:
		m_bShift = false;
//		m_dbDefaultMoveSpeed = 1;
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Up:
	case osgGA::GUIEventAdapter::KEY_Down:
		m_dbForwardFactor = 0.0;
		m_dbLateralRotationRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Left:
	case osgGA::GUIEventAdapter::KEY_Right:
		m_dbDirectionRotationRate = 0.0;
		m_dbPitchOffsetRate = 0.0;
		m_dbDefaultMoveSpeed = 1;
		return true;
		break;

	default:
		return true;
		break;
	}
}

bool OSGCameraManipulator::keyDown( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & aa)	{
	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		m_bCtrl = true;
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Shift_L:
	case osgGA::GUIEventAdapter::KEY_Shift_R:
		m_bShift = true;
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Up :
		if(m_bCtrl)	{		
			m_dbForwardFactor = m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed;
		}
		else	{ //Rotate view (but not direction of travel) up.
			m_dbLateralRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Down:
		if(m_bCtrl)	{	
			m_dbForwardFactor = m_bShift ? -(m_dbDefaultMoveSpeed*=1.1) : -m_dbDefaultMoveSpeed;
		}
		else	{ //Rotate view (but not direction of travel) down.
			m_dbLateralRotationRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Right:
		if(m_bCtrl)	{
			m_dbPitchOffsetRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		else	{	//Rotate view (but not direction of travel) right.
			m_dbDirectionRotationRate = - m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
		return true;
		break;

	case osgGA::GUIEventAdapter::KEY_Left:
		if(m_bCtrl)	{
			m_dbPitchOffsetRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		else	{	//Rotate view (but not direction of travel) left.
			m_dbDirectionRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
		}
		updateMatrices();
		return true;
		break;

	case ' ':
		home(ea.getTime());
		updateMatrices();
		return true;
		break;

	case '1':
		setCameraPosition();
		updateMatrices();
		return true;
		break;

	default:
		return true;
		break;
	}
}


void OSGCameraManipulator::updateMatrices()	{
	osg::CoordinateFrame cf(getCoordinateFrame(m_vecdbPosition));
	osg::Vec3d upVec(getUpVector(cf));

	osg::Matrix mtrxRotate = osg::Matrix::rotate(
						m_dbLateralRotationRate,	getSideVector(cf),
						0.0,						getFrontVector(cf),
						m_dbDirectionRotationRate,	upVec);

	m_vecdbDirection = m_vecdbDirection * mtrxRotate;

	m_vecdbPosition += (m_vecdbDirection * m_dbForwardFactor);

	m_dbPitchOffset += m_dbPitchOffsetRate;
	if(m_dbPitchOffset >= osg::PI || m_dbPitchOffset < -osg::PI)
		m_dbPitchOffset *= -1;

	m_mtrxdbOffset = osg::Matrix::rotate(
						0.0,			getSideVector(cf),
						m_dbPitchOffset,getFrontVector(cf),
						0.0,			upVec);

	m_mtrxdbInverseMatrix.makeLookAt(m_vecdbPosition, m_vecdbPosition + m_vecdbDirection, upVec);
	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);
}