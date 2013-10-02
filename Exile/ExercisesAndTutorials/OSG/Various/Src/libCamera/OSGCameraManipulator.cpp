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

#include "OSGCameraManipulator.h"


using namespace osgGA;
using namespace VR;

OSGCameraManipulator::OSGCameraManipulator():
_t0(0.0),
m_bCtrl(false)
{
	m_dbDefaultMoveSpeed	= 10;
	m_dbRotationFactor		= osg::PI*0.0005;

	_directionRotationRate	= 0.0;
	_pitchOffsetRate		= 0.0;
	_pitchOffset			= 0.0;
	_yawOffsetRate			= 0.0;
	_yawOffset				= 0.0;

	_offset.makeIdentity();

	_direction.set( 0,1,0);
	_stop();
}

OSGCameraManipulator::~OSGCameraManipulator()	{
}

void OSGCameraManipulator::setNode( osg::Node *node )	{
	_node = node;

	if (getAutoComputeHomePosition())
		computeHomePosition();

	home(0.0);
}

const osg::Node* OSGCameraManipulator::getNode() const	{
	return _node.get();
}

osg::Node* OSGCameraManipulator::getNode()	{
	return _node.get();
}


const char* OSGCameraManipulator::className() const	{
	return "OSGCameraManipulator";
}

void OSGCameraManipulator::setByMatrix( const osg::Matrixd &mat )	{
	_inverseMatrix = mat;
	_matrix.invert( _inverseMatrix );

	_position.set( _inverseMatrix(3,0), _inverseMatrix(3,1), _inverseMatrix(3,2 ));
	osg::Matrix R(_inverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	_direction = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame

	_stop();
}

void OSGCameraManipulator::setByInverseMatrix( const osg::Matrixd &invmat)	{
	_matrix = invmat;
	_inverseMatrix.invert( _matrix );

	_position.set( _inverseMatrix(3,0), _inverseMatrix(3,1), _inverseMatrix(3,2 ));
	osg::Matrix R(_inverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	_direction = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame

	_stop();
}

osg::Matrixd OSGCameraManipulator::getMatrix() const	{
	return (osg::Matrix::inverse(_offset) * _matrix);
}

osg::Matrixd OSGCameraManipulator::getInverseMatrix() const	{
	return (_inverseMatrix * _offset);
}

void OSGCameraManipulator::computeHomePosition()	{
	if(getNode()) {
        const osg::BoundingSphere& bs = getNode()->getBound();
        _homeCenter = osg::Vec3(bs._center.x(), bs._center.y(), bs._center.z());
		_homeEye = osg::Vec3(bs._center.x(), bs._center.y() + 3.5*bs.radius(), bs._center.z());
		setHomePosition(-_homeEye, _homeCenter, _homeUp);
	}
}

void OSGCameraManipulator::init(const GUIEventAdapter&, GUIActionAdapter&)	{
	_stop();
}

void OSGCameraManipulator::home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)	{
	home(ea.getTime());
	us.requestRedraw();
	us.requestContinuousUpdate(false);
}

void OSGCameraManipulator::home(double)	{
	if (getAutoComputeHomePosition())
		computeHomePosition();

	_position = _homeEye;
	_direction = _homeCenter - _homeEye;
	_direction.normalize();
	_inverseMatrix.makeLookAt( _homeEye, _homeCenter, _homeUp );
	_matrix.invert( _inverseMatrix );

	_offset.makeIdentity();

	_directionRotationRate = 0.0;
	_pitchOffset = 0.0;
	_yawOffset = 0.0;
	_pitchOffsetRate = 0.0;
	_yawOffsetRate = 0.0;
}

bool OSGCameraManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &aa)	{
	switch(ea.getEventType())	
	{
	case(osgGA::GUIEventAdapter::FRAME):
		_frame(ea,aa);
		return false;
	default:
		break;
	}

	if (ea.getHandled()) return false;

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYUP):
		_keyUp( ea, aa );
		return false;
		break;

	case(osgGA::GUIEventAdapter::KEYDOWN):
		_keyDown(ea, aa);
		return false;
		break;

	case(osgGA::GUIEventAdapter::FRAME):
		_frame(ea,aa);
		return false;
		break;

	default:
		return false;
	}
}


void OSGCameraManipulator::_keyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter & )	{
	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		m_bCtrl = false;
		break;

	case osgGA::GUIEventAdapter::KEY_Up:
	case osgGA::GUIEventAdapter::KEY_Down:
		m_dbForwardFactor = 0.0;
		_yawOffsetRate = 0.0;
		break;

	case osgGA::GUIEventAdapter::KEY_Left:
	case osgGA::GUIEventAdapter::KEY_Right:
		_directionRotationRate = 0.0;
		_pitchOffsetRate = 0.0;
		break;

	default:
		break;
	}
}

void OSGCameraManipulator::_keyDown( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & )	{
	//Yaw - Rotation on vertical axis (Z)
	//Pitch - Rotation on lateral axis (X)
	//Roll - Rotation on longitudinal axis (Y)

	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		m_bCtrl = true;
		break;

	case osgGA::GUIEventAdapter::KEY_Up :
		if(m_bCtrl)	{		//Rotate view (but not direction of travel) up.
			_yawOffsetRate = -m_dbRotationFactor*m_dbDefaultMoveSpeed;
		}
		else	{
			m_dbForwardFactor = m_dbDefaultMoveSpeed;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Down:
		if(m_bCtrl)	{	//Rotate view (but not direction of travel) down.
			_yawOffsetRate = m_dbRotationFactor*m_dbDefaultMoveSpeed;
		}
		else	{
			m_dbForwardFactor = -m_dbDefaultMoveSpeed;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Right:
		if(m_bCtrl)	{	//Rotate view (but not direction of travel) right.
			_pitchOffsetRate = m_dbRotationFactor*m_dbDefaultMoveSpeed;
		}
		else	{
			_directionRotationRate = - m_dbRotationFactor;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Left:
		if(m_bCtrl)	{	//Rotate view (but not direction of travel) left.
			_pitchOffsetRate = -m_dbRotationFactor*m_dbDefaultMoveSpeed;
		}
		else	{
			_directionRotationRate = m_dbRotationFactor;
		}
		break;

	case ' ':
		home(ea.getTime());
		break;

	default:
		break;
	}
}

void OSGCameraManipulator::_frame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & )	{
	double t1 = ea.getTime();
	double dt;
	if( _t0 == 0.0 )	{
		_t0 = ea.getTime();
		dt = 0.0;
	}
	else	{
		dt = t1 - _t0;
		_t0 = t1;
	}

	osg::CoordinateFrame cf( getCoordinateFrame(_position) );
	osg::Vec3d upVec( getUpVector(cf) );

	_direction = _direction * osg::Matrix::rotate( _directionRotationRate, upVec);

	_position += (_direction * m_dbForwardFactor ) * dt;

	_pitchOffset += _pitchOffsetRate * dt;
	if( _pitchOffset >= osg::PI || _pitchOffset < -osg::PI )
		_pitchOffset *= -1;

	_yawOffset += _yawOffsetRate * dt;
	if( _yawOffset >= osg::PI || _yawOffset < -osg::PI )
		_yawOffset *= -1;

	_offset = osg::Matrix::rotate(_yawOffset, getSideVector(cf),
								  _pitchOffset, getFrontVector(cf),
								  0.0, upVec);

	_inverseMatrix.makeLookAt( _position, _position + _direction, upVec);
	_matrix.invert(_inverseMatrix);
}


void OSGCameraManipulator::_stop()	{
	m_dbForwardFactor = 0.0;
	_directionRotationRate = 0.0;
}