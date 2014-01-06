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

using namespace std;
using namespace osg;
using namespace osgGA;

#include "VRKeyboardMouseManipulator.h"
using namespace VR;


//Begin UFOManipulator 
//#include <osgGA/UFOManipulator>

#ifndef M_PI
# define M_PI       3.14159265358979323846  /* pi */
#endif

void KeyboardMouseManipulator::initUFO() {

	_t0 = 0.0;
	_shift = false;
	_ctrl = false;

	_minHeightAboveGround          = 2.0;
	_minDistanceInFront            = 5.0;

	_speedAccelerationFactor       = 0.4;
	_speedDecelerationFactor       = 0.90;

	_directionRotationRate         = 0.0;
	_directionRotationAcceleration = M_PI*0.00005;
	_directionRotationDeceleration = 0.90;

	_speedEpsilon                  = 0.02;
	_directionRotationEpsilon      = 0.0001;

	_viewOffsetDelta = M_PI * 0.0025;
	_pitchOffsetRate = 0.0;
	_pitchOffset = 0.0;

	_yawOffsetRate = 0.0;
	_yawOffset = 0.0;
	_offset.makeIdentity();

	_decelerateOffsetRate = true;
	_straightenOffset = false;

	_direction.set( 0,1,0);
	_stop();

	m_bUFO = false;
}

KeyboardMouseManipulator::KeyboardMouseManipulator(int flags) :
	inherited( flags ),
    _distance( 1. ),
    _trackballSize( 0.8 ) {
	initUFO();

	setMinimumDistance( 0.05, true );
    setWheelZoomFactor( 0.1 );
    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
        setAnimationTime( 0.2 );
}

KeyboardMouseManipulator::KeyboardMouseManipulator( const KeyboardMouseManipulator& om, const osg::CopyOp& copyOp ) :
	osg::Object(om, copyOp),
    inherited( om, copyOp ),
    _center( om._center ),
    _rotation( om._rotation ),
    _distance( om._distance ),
    _trackballSize( om._trackballSize ),
    _wheelZoomFactor( om._wheelZoomFactor ),
    _minimumDistance( om._minimumDistance ) {
	initUFO();
}

void KeyboardMouseManipulator::setByMatrix( const osg::Matrixd &matrix ) {
	if(m_bUFO)
		setByMatrixUFO(matrix);
	else
		setByMatrixOrbit(matrix);
}

void KeyboardMouseManipulator::setByInverseMatrix( const osg::Matrixd &invmat) {
	if(m_bUFO)
		setByInverseMatrixUFO(invmat);
	else
		setByInverseMatrixOrbit(invmat);
}

osg::Matrixd KeyboardMouseManipulator::getMatrix() const {
	if(m_bUFO)
		return getMatrixUFO(); 
	else
		return getMatrixOrbit(); 
}

osg::Matrixd KeyboardMouseManipulator::getInverseMatrix() const {
	if(m_bUFO)
		return getInverseMatrixUFO(); 
	else
		return getInverseMatrixOrbit(); 
}

bool KeyboardMouseManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &aa)
{
	osgGA::GUIEventAdapter::EventType eventType = ea.getEventType();

	switch(eventType)
	{
	case(osgGA::GUIEventAdapter::FRAME):
		_frame(ea,aa);
		return handleFrame( ea, aa );
	case GUIEventAdapter::RESIZE:
        return handleResize( ea, aa );
	default:
		break;
	}

	if (ea.getHandled()) return false;

	switch(eventType)
	{
	/*case GUIEventAdapter::MOVE:
		if(m_bUFO == true) {
			updateUFOOrbit();
		}
		m_bUFO = false;
		return handleMouseMove( ea, aa );*/

	case GUIEventAdapter::DRAG:
		if(m_bUFO == true) {
			updateUFOOrbit();
		}
		m_bUFO = false;
		return handleMouseDrag( ea, aa );

	case GUIEventAdapter::PUSH:
		if(m_bUFO == true) {
			updateUFOOrbit();
		}
		m_bUFO = false;
		return handleMousePush( ea, aa );

	case GUIEventAdapter::RELEASE:
		if(m_bUFO == true) {
			updateUFOOrbit();
		}
		m_bUFO = false;
		return handleMouseRelease( ea, aa );

	case GUIEventAdapter::SCROLL:
		if(m_bUFO == true) {
			updateUFOOrbit();
		}
		m_bUFO = false;
		if( _flags & PROCESS_MOUSE_WHEEL )
			return handleMouseWheel( ea, aa );
		else
			return false;

	case(osgGA::GUIEventAdapter::KEYUP):
		if(m_bUFO == false) {
			updateOrbitUFO();
		}
		_keyUp( ea, aa );
		m_bUFO = true;
		return false;
		//return handleKeyUp( ea, us );
		break;

	case(osgGA::GUIEventAdapter::KEYDOWN):
		if(m_bUFO == false) {
			updateOrbitUFO();
		}
		_keyDown(ea, aa);
		m_bUFO = true;
		return false;
		//return handleKeyDown( ea, us );
		break;

	default:
		return false;
	}
}

void KeyboardMouseManipulator::updateUFOOrbit() {
	cout << "updateUFOOrbit" << endl;
	//setTransformation(_homeEye, _center, _homeUp);
	setByMatrixOrbit(getMatrixUFO());
	//setByInverseMatrixTrackball(getInverseMatrixUFO());
}

void KeyboardMouseManipulator::updateOrbitUFO() {
	cout << "updateOrbitUFO" << endl;
	setByMatrixUFO(getMatrixOrbit());
	// setByInverseMatrixUFO(getInverseMatrixTrackball());
}

bool KeyboardMouseManipulator::intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const
{
	osg::ref_ptr<osgUtil::LineSegmentIntersector> lsi = new osgUtil::LineSegmentIntersector(start,end);

	osgUtil::IntersectionVisitor iv(lsi.get());
	iv.setTraversalMask(_intersectTraversalMask);

	_node->accept(iv);

	if (lsi->containsIntersections())
	{
		intersection = lsi->getIntersections().begin()->getWorldIntersectPoint();
		return true;
	}
	return false;
}

void KeyboardMouseManipulator::setNode( osg::Node *node )
{
	_node = node;

	if (getAutoComputeHomePosition())
		computeHomePosition();

	home(0.0);
}

const osg::Node* KeyboardMouseManipulator::getNode() const
{
	return _node.get();
}

osg::Node* KeyboardMouseManipulator::getNode()
{
	return _node.get();
}

void KeyboardMouseManipulator::setByMatrixUFO( const osg::Matrixd &mat )
{
	_inverseMatrix = mat;
	_matrix.invert( _inverseMatrix );

	_position.set( _inverseMatrix(3,0), _inverseMatrix(3,1), _inverseMatrix(3,2 ));
	osg::Matrix R(_inverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	_direction = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame

	_stop();
}

void KeyboardMouseManipulator::setByInverseMatrixUFO( const osg::Matrixd &invmat)
{
	_matrix = invmat;
	_inverseMatrix.invert( _matrix );

	_position.set( _inverseMatrix(3,0), _inverseMatrix(3,1), _inverseMatrix(3,2 ));
	osg::Matrix R(_inverseMatrix);
	R(3,0) = R(3,1) = R(3,2) = 0.0;
	_direction = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame

	_stop();
}

osg::Matrixd KeyboardMouseManipulator::getMatrixUFO() const
{
	return (osg::Matrix::inverse(_offset) * _matrix);
}

osg::Matrixd KeyboardMouseManipulator::getInverseMatrixUFO() const
{
	return (_inverseMatrix * _offset);
}

void KeyboardMouseManipulator::computeHomePosition()
{
	if( !_node.valid() )
		return;

	osg::BoundingSphere bs = _node->getBound();

	/*
	* Find the ground - Assumption: The ground is the hit of an intersection
	* from a line segment extending from above to below the database at its
	* horizontal center, that intersects the database closest to zero. */

	osg::CoordinateFrame cf( getCoordinateFrame(bs.center()) ); // not sure what position to use here
	osg::Vec3d upVec( getUpVector(cf) );

	osg::Vec3d A = bs.center() + (upVec*(bs.radius()*2));
	osg::Vec3d B = bs.center() + (-upVec*(bs.radius()*2));

	if( (B-A).length() == 0.0)
	{
		return;
	}

	// start with it high
	double ground = bs.radius() * 3;

	osg::Vec3d ip;
	if (intersect(A, B, ip))
	{
		double d = ip.length();
		if( d < ground )
			ground = d;
	}
	else
	{
		//OSG_WARN<<"UFOManipulator : I can't find the ground!"<<std::endl;
		ground = 0.0;
	}


	osg::Vec3d p(bs.center() + upVec*( ground + _minHeightAboveGround*1.25 ) );
	setHomePosition( p, p + getFrontVector(cf), upVec );
}

void KeyboardMouseManipulator::init(const GUIEventAdapter&, GUIActionAdapter&)
{
	//home(ea.getTime());

	_stop();
}

void KeyboardMouseManipulator::home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	home(ea.getTime());
	us.requestRedraw();
	us.requestContinuousUpdate(false);

}

void KeyboardMouseManipulator::home(double)
{
	if (getAutoComputeHomePosition())
		computeHomePosition();

	_position = _homeEye;
	_direction = _homeCenter - _homeEye;
	_direction.normalize();
	_directionRotationRate = 0.0;

	_inverseMatrix.makeLookAt( _homeEye, _homeCenter, _homeUp );
	_matrix.invert( _inverseMatrix );

	_offset.makeIdentity();

	_forwardSpeed = 0.0;
	_sideSpeed = 0.0;
	_upSpeed = 0.0;
}

void KeyboardMouseManipulator::getUsage(osg::ApplicationUsage& usage) const
{
	/** Way too busy.  This needs to wait until we have a scrollable window
	usage.addKeyboardMouseBinding("UFO Manipulator: <SpaceBar>",        "Reset the viewing angle to 0.0");
	usage.addKeyboardMouseBinding("UFO Manipulator: <UpArrow>",         "Acceleration forward.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <DownArrow>",       "Acceleration backward (or deceleration forward");
	usage.addKeyboardMouseBinding("UFO Manipulator: <LeftArrow>",       "Rotate view and direction of travel to the left.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <RightArrow>",      "Rotate view and direction of travel to the right.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <SpaceBar>",        "Brake.  Gradually decelerates linear and rotational movement.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Shift/UpArrow>",   "Accelerate up.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Shift/DownArrow>", "Accelerate down.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Shift/LeftArrow>", "Accelerate (linearly) left.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Shift/RightArrow>","Accelerate (linearly) right.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Shift/SpaceBar>",  "Instant brake.  Immediately stop all linear and rotational movement.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Ctrl/UpArrow>",    "Rotate view (but not direction of travel) up.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Ctrl/DownArrow>",  "Rotate view (but not direction of travel) down.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Ctrl/LeftArrow>",  "Rotate view (but not direction of travel) left.");
	usage.addKeyboardMouseBinding("UFO Manipulator: <Ctrl/RightArrow>", "Rotate view (but not direction of travel) right.");
	*/
	usage.addKeyboardMouseBinding("UFO: ", "Please see http://www.openscenegraph.org/html/UFOCameraManipulator.html");
	// Keep this one as it might be confusing
	usage.addKeyboardMouseBinding("UFO: H", "Reset the viewing position to home");
}



void KeyboardMouseManipulator::_keyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter & )
{
	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		_ctrl = false;
		_decelerateOffsetRate = true;
		_straightenOffset = false;
		break;

	case osgGA::GUIEventAdapter::KEY_Shift_L:
	case osgGA::GUIEventAdapter::KEY_Shift_R:
		_shift = false;
		_decelerateUpSideRate = true;
		break;
	}
}

void KeyboardMouseManipulator::_keyDown( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & )
{
	switch( ea.getKey() )
	{
	case osgGA::GUIEventAdapter::KEY_Control_L:
	case osgGA::GUIEventAdapter::KEY_Control_R:
		_ctrl = true;
		break;

	case osgGA::GUIEventAdapter::KEY_Shift_L :
	case osgGA::GUIEventAdapter::KEY_Shift_R :
		_shift = true;
		break;

	case osgGA::GUIEventAdapter::KEY_Up:
		if( _ctrl )
		{
			_pitchOffsetRate -= _viewOffsetDelta;
			_decelerateOffsetRate = false;
		}
		else
		{
			if( _shift )
			{
				_upSpeed += _speedAccelerationFactor;
				_decelerateUpSideRate = false;
			}
			else
				_forwardSpeed += _speedAccelerationFactor;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Down:
		if( _ctrl )
		{
			_pitchOffsetRate += _viewOffsetDelta;
			_decelerateOffsetRate = false;
		}
		else
		{
			if( _shift )
			{
				_upSpeed -= _speedAccelerationFactor;
				_decelerateUpSideRate = false;
			}
			else
				_forwardSpeed -= _speedAccelerationFactor;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Right:
		if( _ctrl )
		{
			_yawOffsetRate += _viewOffsetDelta;
			_decelerateOffsetRate = false;
		}
		else
		{
			if(_shift)
			{
				_sideSpeed += _speedAccelerationFactor;
				_decelerateUpSideRate = false;
			}
			else
				_directionRotationRate -= _directionRotationAcceleration;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Left:
		if( _ctrl )
		{
			_yawOffsetRate -= _viewOffsetDelta;
			_decelerateOffsetRate = false;
		}
		else
		{
			if(_shift)
			{
				_sideSpeed -= _speedAccelerationFactor;
				_decelerateUpSideRate = false;
			}
			else
				_directionRotationRate += _directionRotationAcceleration;
		}
		break;

	case osgGA::GUIEventAdapter::KEY_Return:
		if( _ctrl )
		{
			_straightenOffset = true;
		}
		break;

	case ' ':
		if( _shift )
		{
			_stop();
		}
		else
		{
			if( fabs(_forwardSpeed) > 0.0 )
			{
				_forwardSpeed *= _speedDecelerationFactor;

				if( fabs(_forwardSpeed ) < _speedEpsilon )
					_forwardSpeed = 0.0;
			}
			if( fabs(_sideSpeed) > 0.0 )
			{
				_sideSpeed *= _speedDecelerationFactor;

				if( fabs( _sideSpeed ) < _speedEpsilon )
					_sideSpeed = 0.0;
			}

			if( fabs(_upSpeed) > 0.0 )
			{
				_upSpeed *= _speedDecelerationFactor;

				if( fabs( _upSpeed ) < _speedEpsilon )
					_sideSpeed = 0.0;
			}


			if( fabs(_directionRotationRate ) > 0.0 )
			{
				_directionRotationRate *= _directionRotationDeceleration;
				if( fabs( _directionRotationRate ) < _directionRotationEpsilon )
					_directionRotationRate = 0.0;
			}

		}
		break;

	case 'H':
		home(ea.getTime());
		break;
	}

}

void KeyboardMouseManipulator::_frame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & )
{
	double t1 = ea.getTime();
	if( _t0 == 0.0 )
	{
		_t0 = ea.getTime();
		_dt = 0.0;
	}
	else
	{
		_dt = t1 - _t0;
		_t0 = t1;
	}

	osg::CoordinateFrame cf( getCoordinateFrame(_position) );
	osg::Vec3d upVec( getUpVector(cf) );
	if( fabs( _directionRotationRate ) > _directionRotationEpsilon )
	{
		_direction = _direction * osg::Matrix::rotate( _directionRotationRate, upVec);
	}

	{
		osg::Vec3d _sideVec = _direction * osg::Matrix::rotate( -M_PI*0.5, upVec);

		_position += ((_direction       * _forwardSpeed) +
			(_sideVec         * _sideSpeed) +
			(upVec * _upSpeed))
			* _dt;

	}

	_pitchOffset += _pitchOffsetRate * _dt;
	if( _pitchOffset >= M_PI || _pitchOffset < -M_PI )
		_pitchOffset *= -1;

	_yawOffset   += _yawOffsetRate   * _dt;
	if( _yawOffset >= M_PI || _yawOffset < -M_PI )
		_yawOffset *= -1;

	_offset       = osg::Matrix::rotate( _yawOffset, getSideVector(cf),
		_pitchOffset, getFrontVector(cf),
		0.0, upVec);

	_adjustPosition();

	_inverseMatrix.makeLookAt( _position, _position + _direction, upVec);
	_matrix.invert(_inverseMatrix);

	if( _decelerateUpSideRate )
	{
		_upSpeed   *= 0.98;
		_sideSpeed *= 0.98;
	}

	if( _decelerateOffsetRate )
	{
		_yawOffsetRate   *= 0.98;
		_pitchOffsetRate *= 0.98;
	}

	if( _straightenOffset )
	{
		if( _shift )
		{
			_pitchOffset = 0.0;
			_yawOffset = 0.0;
			_pitchOffsetRate = 0.0;
			_yawOffsetRate   = 0.0;
		}
		else
		{
			_pitchOffsetRate = 0.0;
			_yawOffsetRate   = 0.0;
			_pitchOffset *= 0.99;
			_yawOffset *= 0.99;

			if( fabs(_pitchOffset ) < 0.01 )
				_pitchOffset = 0.0;
			if( fabs(_yawOffset ) < 0.01 )
				_pitchOffset = 0.0;

		}
		if( _pitchOffset == 0.0 && _yawOffset == 0.0 )
			_straightenOffset = false;
	}
}

void KeyboardMouseManipulator::_adjustPosition()
{
	if( !_node.valid() )
		return;

	// Forward line segment at 3 times our intersect distance


	typedef std::vector<osg::Vec3d> Intersections;
	Intersections intersections;

	// Check intersects infront.
	osg::Vec3d ip;
	if (intersect(_position,
		_position + (_direction * (_minDistanceInFront * 3.0)),
		ip ))
	{
		double d = (ip - _position).length();

		if( d < _minDistanceInFront )
		{
			_position = ip + (_direction * -_minDistanceInFront);
			_stop();
		}
	}

	// Check intersects below.
	osg::CoordinateFrame cf( getCoordinateFrame(_position) );
	osg::Vec3d upVec( getUpVector(cf) );

	if (intersect(_position,
		_position - upVec*_minHeightAboveGround*3,
		ip ))
	{
		double d = (ip - _position).length();

		if( d < _minHeightAboveGround )
			_position = ip + (upVec * _minHeightAboveGround);
	}
}


void KeyboardMouseManipulator::_stop()
{
	_forwardSpeed = 0.0;
	_sideSpeed = 0.0;
	_upSpeed = 0.0;
	_directionRotationRate = 0.0;
}

void KeyboardMouseManipulator::getCurrentPositionAsLookAt( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up )
{
	eye = _position;
	center = _position + _direction;
	up.set(getUpVector(getCoordinateFrame(_position)));
}
//End UFOManipulator 
//Begin OrbitManipulator 
int KeyboardMouseManipulator::_minimumDistanceFlagIndex = allocateRelativeFlag();

/** Set the position of the manipulator using a 4x4 matrix.*/
void KeyboardMouseManipulator::setByMatrixOrbit( const osg::Matrixd& matrix )
{
	_center = osg::Vec3d( 0., 0., -_distance ) * matrix;
	_rotation = matrix.getRotate();

	// fix current rotation
	if( getVerticalAxisFixed() )
		fixVerticalAxis( _center, _rotation, true );
}


/** Set the position of the manipulator using a 4x4 matrix.*/
void KeyboardMouseManipulator::setByInverseMatrixOrbit( const osg::Matrixd& matrix )
{
	setByMatrix( osg::Matrixd::inverse( matrix ) );
}


/** Get the position of the manipulator as 4x4 matrix.*/
osg::Matrixd KeyboardMouseManipulator::getMatrixOrbit() const
{
	return osg::Matrixd::translate( 0., 0., _distance ) *
		osg::Matrixd::rotate( _rotation ) *
		osg::Matrixd::translate( _center );
}


/** Get the position of the manipulator as a inverse matrix of the manipulator,
typically used as a model view matrix.*/
osg::Matrixd KeyboardMouseManipulator::getInverseMatrixOrbit() const
{
	return osg::Matrixd::translate( -_center ) *
		osg::Matrixd::rotate( _rotation.inverse() ) *
		osg::Matrixd::translate( 0.0, 0.0, -_distance );
}


// doc in parent
void KeyboardMouseManipulator::setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation )
{
	_center = eye + rotation * osg::Vec3d( 0., 0., -_distance );
	_rotation = rotation;

	// fix current rotation
	if( getVerticalAxisFixed() )
		fixVerticalAxis( _center, _rotation, true );
}


// doc in parent
void KeyboardMouseManipulator::getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const
{
	eye = _center - _rotation * osg::Vec3d( 0., 0., -_distance );
	rotation = _rotation;
}


// doc in parent
void KeyboardMouseManipulator::setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up )
{
	Vec3d lv( center - eye );

	Vec3d f( lv );
	f.normalize();
	Vec3d s( f^up );
	s.normalize();
	Vec3d u( s^f );
	u.normalize();

	osg::Matrixd rotation_matrix( s[0], u[0], -f[0], 0.0f,
		s[1], u[1], -f[1], 0.0f,
		s[2], u[2], -f[2], 0.0f,
		0.0f, 0.0f,  0.0f, 1.0f );

	_center = center;
	_distance = lv.length();
	_rotation = rotation_matrix.getRotate().inverse();

	// fix current rotation
	if( getVerticalAxisFixed() )
		fixVerticalAxis( _center, _rotation, true );
}


// doc in parent
void KeyboardMouseManipulator::getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const
{
	center = _center;
	eye = _center + _rotation * osg::Vec3d( 0., 0., _distance );
	up = _rotation * osg::Vec3d( 0., 1., 0. );
}


/** Sets the transformation by heading. Heading is given as an angle in radians giving a azimuth in xy plane.
Its meaning is similar to longitude used in cartography and navigation.
Positive number is going to the east direction.*/
void KeyboardMouseManipulator::setHeading( double azimuth )
{
	CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
	Vec3d localUp = getUpVector( coordinateFrame );
	Vec3d localRight = getSideVector( coordinateFrame );

	Vec3d dir = Quat( getElevation(), localRight ) * Quat( azimuth, localUp ) * Vec3d( 0., -_distance, 0. );

	setTransformation( _center + dir, _center, localUp );
}


/// Returns the heading in radians. \sa setHeading
double KeyboardMouseManipulator::getHeading() const
{
	CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
	Vec3d localFront = getFrontVector( coordinateFrame );
	Vec3d localRight = getSideVector( coordinateFrame );

	Vec3d center, eye, tmp;
	getTransformation( eye, center, tmp );

	Plane frontPlane( localFront, center );
	double frontDist = frontPlane.distance( eye );
	Plane rightPlane( localRight, center );
	double rightDist = rightPlane.distance( eye );

	return atan2( rightDist, -frontDist );
}


/** Sets the transformation by elevation. Elevation is given as an angle in radians from xy plane.
Its meaning is similar to latitude used in cartography and navigation.
Positive number is going to the north direction, negative to the south.*/
void KeyboardMouseManipulator::setElevation( double elevation )
{
	CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
	Vec3d localUp = getUpVector( coordinateFrame );
	Vec3d localRight = getSideVector( coordinateFrame );

	Vec3d dir = Quat( -elevation, localRight ) * Quat( getHeading(), localUp ) * Vec3d( 0., -_distance, 0. );

	setTransformation( _center + dir, _center, localUp );
}


/// Returns the elevation in radians. \sa setElevation
double KeyboardMouseManipulator::getElevation() const
{
	CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
	Vec3d localUp = getUpVector( coordinateFrame );
	localUp.normalize();

	Vec3d center, eye, tmp;
	getTransformation( eye, center, tmp );

	Plane plane( localUp, center );
	double dist = plane.distance( eye );

	return asin( -dist / (eye-center).length() );
}


// doc in parent
bool KeyboardMouseManipulator::handleMouseWheel( const GUIEventAdapter& ea, GUIActionAdapter& us )
{
	osgGA::GUIEventAdapter::ScrollingMotion sm = ea.getScrollingMotion();

	// handle centering
	if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
	{

		if( ((sm == GUIEventAdapter::SCROLL_DOWN && _wheelZoomFactor > 0.)) ||
			((sm == GUIEventAdapter::SCROLL_UP   && _wheelZoomFactor < 0.)) )
		{

			if( getAnimationTime() <= 0. )
			{
				// center by mouse intersection (no animation)
				setCenterByMousePointerIntersection( ea, us );
			}
			else
			{
				// start new animation only if there is no animation in progress
				if( !isAnimating() )
					startAnimationByMousePointerIntersection( ea, us );

			}

		}
	}

	switch( sm )
	{
		// mouse scroll up event
	case GUIEventAdapter::SCROLL_UP:
		{
			// perform zoom
			zoomModel( _wheelZoomFactor, true );
			us.requestRedraw();
			us.requestContinuousUpdate( isAnimating() || _thrown );
			return true;
		}

		// mouse scroll down event
	case GUIEventAdapter::SCROLL_DOWN:
		{
			// perform zoom
			zoomModel( -_wheelZoomFactor, true );
			us.requestRedraw();
			us.requestContinuousUpdate( isAnimating() || _thrown );
			return true;
		}

		// unhandled mouse scrolling motion
	default:
		return false;
	}
}


// doc in parent
bool KeyboardMouseManipulator::performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
	// rotate camera
	if( getVerticalAxisFixed() )
		rotateWithFixedVertical( dx, dy );
	else
		rotateTrackball( _ga_t0->getXnormalized(), _ga_t0->getYnormalized(),
		_ga_t1->getXnormalized(), _ga_t1->getYnormalized(),
		getThrowScale( eventTimeDelta ) );
	return true;
}


// doc in parent
bool KeyboardMouseManipulator::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
	// pan model
	float scale = -0.3f * _distance * getThrowScale( eventTimeDelta );
	panModel( dx*scale, dy*scale );
	return true;
}


// doc in parent
bool KeyboardMouseManipulator::performMovementRightMouseButton( const double eventTimeDelta, const double /*dx*/, const double dy )
{
	// zoom model
	zoomModel( dy * getThrowScale( eventTimeDelta ), true );
	return true;
}


bool KeyboardMouseManipulator::performMouseDeltaMovement( const float dx, const float dy )
{
	// rotate camera
	if( getVerticalAxisFixed() )
		rotateWithFixedVertical( dx, dy );
	else
		rotateTrackball( 0.f, 0.f, dx, dy, 1.f );

	return true;
}


void KeyboardMouseManipulator::applyAnimationStep( const double currentProgress, const double prevProgress )
{
	OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData* >( _animationData.get() );
	assert( ad );

	// compute new center
	osg::Vec3d prevCenter, prevEye, prevUp;
	getTransformation( prevEye, prevCenter, prevUp );
	osg::Vec3d newCenter = osg::Vec3d(prevCenter) + (ad->_movement * (currentProgress - prevProgress));

	// fix vertical axis
	if( getVerticalAxisFixed() )
	{

		CoordinateFrame coordinateFrame = getCoordinateFrame( newCenter );
		Vec3d localUp = getUpVector( coordinateFrame );

		fixVerticalAxis( newCenter - prevEye, prevUp, prevUp, localUp, false );
	}

	// apply new transformation
	setTransformation( prevEye, newCenter, prevUp );
}


bool KeyboardMouseManipulator::startAnimationByMousePointerIntersection(
	const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{
	// get current transformation
	osg::Vec3d prevCenter, prevEye, prevUp;
	getTransformation( prevEye, prevCenter, prevUp );

	// center by mouse intersection
	if( !setCenterByMousePointerIntersection( ea, us ) )
		return false;

	OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData*>( _animationData.get() );
	assert( ad );

	// setup animation data and restore original transformation
	ad->start( osg::Vec3d(_center) - prevCenter, ea.getTime() );
	setTransformation( prevEye, prevCenter, prevUp );

	return true;
}


void KeyboardMouseManipulator::OrbitAnimationData::start( const osg::Vec3d& movement, const double startTime )
{
	AnimationData::start( startTime );

	_movement = movement;
}


/** Performs trackball rotation based on two points given, for example,
by mouse pointer on the screen.

Scale parameter is useful, for example, when manipulator is thrown.
It scales the amount of rotation based, for example, on the current frame time.*/
void KeyboardMouseManipulator::rotateTrackball( const float px0, const float py0,
										   const float px1, const float py1, const float /*scale*/ )
{
	osg::Vec3d axis;
	float angle;

	trackball( axis, angle, px1, py1, px0, py0 );

	Quat new_rotate;
	new_rotate.makeRotate( angle, axis );

	_rotation = _rotation * new_rotate;
}


/** Performs rotation horizontally by dx parameter and vertically by dy parameter,
while keeping UP vector.*/
void KeyboardMouseManipulator::rotateWithFixedVertical( const float dx, const float dy )
{
	CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
	Vec3d localUp = getUpVector( coordinateFrame );

	rotateYawPitch( _rotation, dx, dy, localUp );
}


/** Performs rotation horizontally by dx parameter and vertically by dy parameter,
while keeping UP vector given by up parameter.*/
void KeyboardMouseManipulator::rotateWithFixedVertical( const float dx, const float dy, const Vec3f& up )
{
	rotateYawPitch( _rotation, dx, dy, up );
}


/** Moves camera in x,y,z directions given in camera local coordinates.*/
void KeyboardMouseManipulator::panModel( const float dx, const float dy, const float dz )
{
	Matrix rotation_matrix;
	rotation_matrix.makeRotate( _rotation );

	Vec3d dv( dx, dy, dz );

	_center += dv * rotation_matrix;
}


/** Changes the distance of camera to the focal center.
If pushForwardIfNeeded is true and minimumDistance is reached,
the focal center is moved forward. Otherwise, distance is limited
to its minimum value.
\sa OrbitManipulator::setMinimumDistance
*/
void KeyboardMouseManipulator::zoomModel( const float dy, bool pushForwardIfNeeded )
{
	// scale
	float scale = 1.0f + dy;

	// minimum distance
	float minDist = _minimumDistance;
	if( getRelativeFlag( _minimumDistanceFlagIndex ) )
		minDist *= _modelSize;

	if( _distance*scale > minDist )
	{
		// regular zoom
		_distance *= scale;
	}
	else
	{
		if( pushForwardIfNeeded )
		{
			// push the camera forward
			float scale = -_distance;
			Matrixd rotation_matrix( _rotation );
			Vec3d dv = (Vec3d( 0.0f, 0.0f, -1.0f ) * rotation_matrix) * (dy * scale);
			_center += dv;
		}
		else
		{
			// set distance on its minimum value
			_distance = minDist;
		}
	}
}


/**
* Simulate a track-ball.  Project the points onto the virtual
* trackball, then figure out the axis of rotation, which is the cross
* product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
* Note:  This is a deformed trackball-- is a trackball in the center,
* but is deformed into a hyperbolic sheet of rotation away from the
* center.  This particular function was chosen after trying out
* several variations.
*
* It is assumed that the arguments to this routine are in the range
* (-1.0 ... 1.0)
*/
void KeyboardMouseManipulator::trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y )
{
	/*
	* First, figure out z-coordinates for projection of P1 and P2 to
	* deformed sphere
	*/

	osg::Matrixd rotation_matrix(_rotation);

	osg::Vec3d uv = Vec3d(0.0f,1.0f,0.0f)*rotation_matrix;
	osg::Vec3d sv = Vec3d(1.0f,0.0f,0.0f)*rotation_matrix;
	osg::Vec3d lv = Vec3d(0.0f,0.0f,-1.0f)*rotation_matrix;

	osg::Vec3d p1 = sv * p1x + uv * p1y - lv * tb_project_to_sphere(_trackballSize, p1x, p1y);
	osg::Vec3d p2 = sv * p2x + uv * p2y - lv * tb_project_to_sphere(_trackballSize, p2x, p2y);

	/*
	*  Now, we want the cross product of P1 and P2
	*/
	axis = p2^p1;
	axis.normalize();

	/*
	*  Figure out how much to rotate around that axis.
	*/
	float t = (p2 - p1).length() / (2.0 * _trackballSize);

	/*
	* Avoid problems with out-of-control values...
	*/
	if (t > 1.0) t = 1.0;
	if (t < -1.0) t = -1.0;
	angle = inRadians(asin(t));
}


/**
* Helper trackball method that projects an x,y pair onto a sphere of radius r OR
* a hyperbolic sheet if we are away from the center of the sphere.
*/
float KeyboardMouseManipulator::tb_project_to_sphere( float r, float x, float y )
{
	float d, t, z;

	d = sqrt(x*x + y*y);
	/* Inside sphere */
	if (d < r * 0.70710678118654752440)
	{
		z = sqrt(r*r - d*d);
	}                            /* On hyperbola */
	else
	{
		t = r / 1.41421356237309504880;
		z = t*t / d;
	}
	return z;
}


/** Get the FusionDistanceMode. Used by SceneView for setting up stereo convergence.*/
osgUtil::SceneView::FusionDistanceMode KeyboardMouseManipulator::getFusionDistanceMode() const
{
	return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE;
}

/** Get the FusionDistanceValue. Used by SceneView for setting up stereo convergence.*/
float KeyboardMouseManipulator::getFusionDistanceValue() const
{
	return _distance;
}


/** Set the center of the manipulator. */
void KeyboardMouseManipulator::setCenter( const Vec3d& center )
{
	_center = center;
}


/** Get the center of the manipulator. */
const Vec3d& KeyboardMouseManipulator::getCenter() const
{
	return _center;
}


/** Set the rotation of the manipulator. */
void KeyboardMouseManipulator::setRotation( const Quat& rotation )
{
	_rotation = rotation;
}


/** Get the rotation of the manipulator. */
const Quat& KeyboardMouseManipulator::getRotation() const
{
	return _rotation;
}


/** Set the distance of camera to the center. */
void KeyboardMouseManipulator::setDistance( double distance )
{
	_distance = distance;
}


/** Get the distance of the camera to the center. */
double KeyboardMouseManipulator::getDistance() const
{
	return _distance;
}


/** Set the size of the trackball. Value is relative to the model size. */
void KeyboardMouseManipulator::setTrackballSize( const double& size )
{
	/*
	* This size should really be based on the distance from the center of
	* rotation to the point on the object underneath the mouse.  That
	* point would then track the mouse as closely as possible.  This is a
	* simple example, though, so that is left as an Exercise for the
	* Programmer.
	*/
	_trackballSize = size;
	clampBetweenRange( _trackballSize, 0.1, 1.0, "TrackballManipulator::setTrackballSize(float)" );
}


/** Set the mouse wheel zoom factor.
The amount of camera movement on each mouse wheel event
is computed as the current distance to the center multiplied by this factor.
For example, value of 0.1 will short distance to center by 10% on each wheel up event.
Use negative value for reverse mouse wheel direction.*/
void KeyboardMouseManipulator::setWheelZoomFactor( double wheelZoomFactor )
{
	_wheelZoomFactor = wheelZoomFactor;
}


/** Set the minimum distance of the eye point from the center
before the center is pushed forward.*/
void KeyboardMouseManipulator::setMinimumDistance( const double& minimumDistance, bool relativeToModelSize )
{
	_minimumDistance = minimumDistance;
	setRelativeFlag( _minimumDistanceFlagIndex, relativeToModelSize );
}


/** Get the minimum distance of the eye point from the center
before the center is pushed forward.*/
double KeyboardMouseManipulator::getMinimumDistance( bool *relativeToModelSize ) const
{
	if( relativeToModelSize )
		*relativeToModelSize = getRelativeFlag( _minimumDistanceFlagIndex );

	return _minimumDistance;
}
//End OrbitManipulator 

///// Constructor.
//KeyboardMouseManipulator::KeyboardMouseManipulator( int flags ) : 
//	m_bCtrl(false),
//	m_bShift(false),
//	m_cdbRotationFactor(osg::PI*0.001),
//	inherited( flags ),
//	_distance( 100. ),
//	_trackballSize( 0.8 ),
//	m_bUFO(true)
//{
//	m_dbDirectionRotationRate	= 0.0;
//	m_dbPitchOffsetRate			= 0.0;
//	m_dbPitchOffset				= 0.0;
//	m_dbLateralRotationRate		= 0.0;
//	m_dbDefaultMoveSpeed		= 1;
//
//	m_mtrxdbOffset.makeIdentity();
//	m_vecdbDirection.set(0,-1,0);
//
//    setVerticalAxisFixed( false );
//
//    setMinimumDistance( 0.05, true );
//    setWheelZoomFactor( 0.1 );
//    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
//        setAnimationTime( 0.2 );
//}
//
//
///// Constructor.
//KeyboardMouseManipulator::KeyboardMouseManipulator(const KeyboardMouseManipulator& om, const osg::CopyOp& copyOp) :
//m_bCtrl(false),
//m_bShift(false),
//m_cdbRotationFactor(osg::PI*0.001),
//	osg::Object(om, copyOp),
//	inherited( om, copyOp ),
//	_center( om._center ),
//	_rotation( om._rotation ),
//	_distance( om._distance ),
//	_trackballSize( om._trackballSize ),
//	_wheelZoomFactor( om._wheelZoomFactor ),
//	_minimumDistance( om._minimumDistance ),
//	m_bUFO(true)
//{
//	m_dbDirectionRotationRate	= 0.0;
//	m_dbPitchOffsetRate			= 0.0;
//	m_dbPitchOffset				= 0.0;
//	m_dbLateralRotationRate		= 0.0;
//
//	m_dbDefaultMoveSpeed = 1;
//	
//	m_mtrxdbOffset.makeIdentity();
//
//	m_vecdbDirection.set(0,-1,0);
//}
//
//
//const char* KeyboardMouseManipulator::className() const	{
//	return "KeyboardMouseManipulator";
//}
//
//void KeyboardMouseManipulator::setByMatrix(const osg::Matrixd &matrix) {
//	if(m_bUFO)
//		setByMatrixUFO(matrix);
//	else
//		setByMatrixTrackball(matrix);
//}
//
//void KeyboardMouseManipulator::setByInverseMatrix(const osg::Matrixd &invmat)
//{
//	if(m_bUFO)
//		setByInverseMatrixUFO(invmat);
//	else
//		setByInverseMatrixTrackball(invmat);
//}
//
//osg::Matrixd KeyboardMouseManipulator::getMatrix() const {
//	if(m_bUFO)
//		return getMatrixUFO(); 
//	else
//		return getMatrixTrackball(); 
//}
//
//osg::Matrixd KeyboardMouseManipulator::getInverseMatrix() const {
//	if(m_bUFO)
//		return getInverseMatrixUFO();
//	else
//		return getInverseMatrixTrackball(); 
//}
//
//bool KeyboardMouseManipulator::handle( const GUIEventAdapter& ea, GUIActionAdapter& us )
//{
//	switch( ea.getEventType() )
//    {
//        case GUIEventAdapter::FRAME:
//			if(m_bUFO) {
////				updateMatrices();
//				return(true);
//			} else {
//				return handleFrame( ea, us );
//			}
//
//        case GUIEventAdapter::RESIZE:
//            return handleResize( ea, us );
//
//        default:
//            break;
//   }
//
//    if( ea.getHandled() )
//        return false;
//
//	int nButton = ea.getEventType();
//	switch(nButton)	{
///*        case GUIEventAdapter::MOVE:
//            return handleMouseMove( ea, us );
//
//        case GUIEventAdapter::DRAG:
//			updateTrackballUFO();
//			m_bUFO = false;
//            return handleMouseDrag( ea, us );
//
//        case GUIEventAdapter::PUSH:
//			updateTrackballUFO();
//			m_bUFO = false;
//            return handleMousePush( ea, us );
//
//        case GUIEventAdapter::RELEASE:
//            return handleMouseRelease( ea, us );
//*/
//        case GUIEventAdapter::KEYDOWN:
////			m_bUFO = true;
////			updateUFOTrackball();
//            return keyDown( ea, us );
//
//        case GUIEventAdapter::KEYUP:
//            return keyUp( ea, us );
//
//        //case GUIEventAdapter::SCROLL:
//        //    if( _flags & PROCESS_MOUSE_WHEEL )
//        //    return handleMouseWheel( ea, us );
//        //    else
//        //    return false;
//
//        default:
//            return false;
//    }
//}
//
//
//void KeyboardMouseManipulator::updateUFOTrackball() {
//	setTransformation(_homeEye, _center, _homeUp);
//	//setByMatrixTrackball(getMatrixUFO());
//	//setByInverseMatrixTrackball(getInverseMatrixUFO());
//}
//
//void KeyboardMouseManipulator::updateTrackballUFO() {
//	//setByMatrixUFO(getMatrixTrackball());
//	// setByInverseMatrixUFO(getInverseMatrixTrackball());
//}
//
//		
//
//
////begin UFO
//
//void KeyboardMouseManipulator::setNode(osg::Node *node)	{
//	m_pNode = node;
//
//	if (getAutoComputeHomePosition())
//		computeHomePosition();
//
//	home(0.0);
//}
//
//const osg::Node* KeyboardMouseManipulator::getNode() const	{
//	return m_pNode.get();
//}
//
//osg::Node* KeyboardMouseManipulator::getNode()	{
//	return m_pNode.get();
//}
//
//
//void KeyboardMouseManipulator::setByMatrixUFO(const osg::Matrixd &mat)	{
//	m_mtrxdbInverseMatrix = mat;
//	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);
//
//	m_vecdbPosition.set( m_mtrxdbInverseMatrix(3,0), m_mtrxdbInverseMatrix(3,1), m_mtrxdbInverseMatrix(3,2 ));
//	osg::Matrix R(m_mtrxdbInverseMatrix);
//	R(3,0) = R(3,1) = R(3,2) = 0.0;
//	m_vecdbDirection = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame
//}
//
//void KeyboardMouseManipulator::setByInverseMatrixUFO( const osg::Matrixd &invmat)	{
//	m_mtrxdbMatrix = invmat;
//	m_mtrxdbInverseMatrix.invert(m_mtrxdbMatrix);
//
//	m_vecdbPosition.set(m_mtrxdbInverseMatrix(3,0), m_mtrxdbInverseMatrix(3,1), m_mtrxdbInverseMatrix(3,2));
//	osg::Matrix R(m_mtrxdbInverseMatrix);
//	R(3,0) = R(3,1) = R(3,2) = 0.0;
//	m_vecdbDirection = osg::Vec3d(0,0,-1) * R; // camera up is +Z, regardless of CoordinateFrame
//}
//
//osg::Matrixd KeyboardMouseManipulator::getMatrixUFO() const	{
//	return (osg::Matrix::inverse(m_mtrxdbOffset) * m_mtrxdbMatrix);
//}
//
//osg::Matrixd KeyboardMouseManipulator::getInverseMatrixUFO() const	{
//	return (m_mtrxdbInverseMatrix * m_mtrxdbOffset);
//}
//
//void KeyboardMouseManipulator::computeHomePosition()	{
//	_homeCenter = osg::Vec3(0.0, 0.0, 0.0);
//	_homeEye = osg::Vec3(0.0, 5, 0.0);
//
//	setHomePosition(-_homeEye, _homeCenter, _homeUp);
//
//	m_vecdbPosition = _homeEye;
//	m_vecdbDirection = _homeCenter - _homeEye;
//	m_vecdbDirection.normalize();
//	m_mtrxdbInverseMatrix.makeLookAt(_homeEye, _homeCenter, _homeUp);
//	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);
//
//	m_mtrxdbOffset.makeIdentity();
//
//	m_dbDirectionRotationRate = 0.0;
//	m_dbPitchOffset = 0.0;
//	m_dbPitchOffsetRate = 0.0;
//	m_dbLateralRotationRate = 0.0;
//	m_dbForwardFactor = 0.0;
//}
//
//void KeyboardMouseManipulator::init(const GUIEventAdapter&, GUIActionAdapter&)	{
//}
//
//void KeyboardMouseManipulator::home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)	{
//	home(ea.getTime());
//	aa.requestRedraw();
//	aa.requestContinuousUpdate(false);
//}
//
//void KeyboardMouseManipulator::home(double)	{
//	if (!getAutoComputeHomePosition())
//		computeHomePosition();
//}
//
//
////----------------------------------------------------------------------------------------
//
//
//bool KeyboardMouseManipulator::keyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter & aa)	{
//	switch( ea.getKey() )
//	{
//	case osgGA::GUIEventAdapter::KEY_Control_L:
//	case osgGA::GUIEventAdapter::KEY_Control_R:
//		m_bCtrl = false;
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Shift_L:
//	case osgGA::GUIEventAdapter::KEY_Shift_R:
//		m_bShift = false;
////		m_dbDefaultMoveSpeed = 1;
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Up:
//	case osgGA::GUIEventAdapter::KEY_Down:
//		m_dbForwardFactor = 0.0;
//		m_dbLateralRotationRate = 0.0;
//		m_dbDefaultMoveSpeed = 1;
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Left:
//	case osgGA::GUIEventAdapter::KEY_Right:
//		m_dbDirectionRotationRate = 0.0;
//		m_dbPitchOffsetRate = 0.0;
//		m_dbDefaultMoveSpeed = 1;
//		return true;
//		break;
//
//	default:
//		return true;
//		break;
//	}
//}
//
//bool KeyboardMouseManipulator::keyDown( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & aa)	{
//	switch( ea.getKey() )
//	{
//	case osgGA::GUIEventAdapter::KEY_Control_L:
//	case osgGA::GUIEventAdapter::KEY_Control_R:
//		m_bCtrl = true;
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Shift_L:
//	case osgGA::GUIEventAdapter::KEY_Shift_R:
//		m_bShift = true;
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Up :
//		if(m_bCtrl)	{		
//			m_dbForwardFactor = m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed;
//		}
//		else	{ //Rotate view (but not direction of travel) up.
//			m_dbLateralRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		updateMatrices();
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Down:
//		if(m_bCtrl)	{	
//			m_dbForwardFactor = m_bShift ? -(m_dbDefaultMoveSpeed*=1.1) : -m_dbDefaultMoveSpeed;
//		}
//		else	{ //Rotate view (but not direction of travel) down.
//			m_dbLateralRotationRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		updateMatrices();
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Right:
//		if(m_bCtrl)	{
//			m_dbPitchOffsetRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		else	{	//Rotate view (but not direction of travel) right.
//			m_dbDirectionRotationRate = - m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		updateMatrices();
//		return true;
//		break;
//
//	case osgGA::GUIEventAdapter::KEY_Left:
//		if(m_bCtrl)	{
//			m_dbPitchOffsetRate = -m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		else	{	//Rotate view (but not direction of travel) left.
//			m_dbDirectionRotationRate = m_cdbRotationFactor * (m_bShift ? (m_dbDefaultMoveSpeed*=1.1) : m_dbDefaultMoveSpeed);
//		}
//		updateMatrices();
//		return true;
//		break;
//
//	case ' ':
//		home(ea.getTime());
//		updateMatrices();
//		return true;
//		break;
//
//	default:
//		return true;
//		break;
//	}
//}
//
//void KeyboardMouseManipulator::updateMatrices()	{
//	osg::CoordinateFrame cf1(getCoordinateFrame(m_vecdbDirection));
//
//	osg::CoordinateFrame cf(getCoordinateFrame(m_vecdbPosition));
//	osg::Vec3d upVec(getUpVector(cf));
//
//	osg::Matrix mtrxRotate = osg::Matrix::rotate(
//						m_dbLateralRotationRate,	getSideVector(cf),
//						0.0,						getFrontVector(cf),
//						m_dbDirectionRotationRate,	upVec);
//
//	m_vecdbDirection = m_vecdbDirection * mtrxRotate;
//
//	m_vecdbPosition += (m_vecdbDirection * m_dbForwardFactor);
//
//	m_dbPitchOffset += m_dbPitchOffsetRate;
//	if(m_dbPitchOffset >= osg::PI || m_dbPitchOffset < -osg::PI)
//		m_dbPitchOffset *= -1;
//
//	m_mtrxdbOffset = osg::Matrix::rotate(
//						0.0,			getSideVector(cf),
//						m_dbPitchOffset,getFrontVector(cf),
//						0.0,			upVec);
//
//	m_mtrxdbInverseMatrix.makeLookAt(m_vecdbPosition, m_vecdbPosition + m_vecdbDirection, upVec);
//	m_mtrxdbMatrix.invert(m_mtrxdbInverseMatrix);
//}
//
////end UFO
//
////begin Trackball
//
//void KeyboardMouseManipulator::setNodeTrackball(osg::Node *node)	{
//	m_pNode = node;
//
//	if (getAutoComputeHomePosition())
//		computeHomePosition();
//
//	home(0.0);
//}
//
//const osg::Node* KeyboardMouseManipulator::getNodeTrackball() const	{
//	return m_pNode.get();
//}
//
//osg::Node* KeyboardMouseManipulator::getNodeTrackball()	{
//	return m_pNode.get();
//}
//
//
//
//
//
//int KeyboardMouseManipulator::_minimumDistanceFlagIndex = allocateRelativeFlag();
//
//
//
///** Set the position of the manipulator using a 4x4 matrix.*/
//void KeyboardMouseManipulator::setByMatrixTrackball( const osg::Matrixd& matrix )
//{
//    _center = osg::Vec3d( 0., 0., -_distance ) * matrix;
//    _rotation = matrix.getRotate();
//
//    // fix current rotation
//    if( getVerticalAxisFixed() )
//        fixVerticalAxis( _center, _rotation, true );
//}
//
//
///** Set the position of the manipulator using a 4x4 matrix.*/
//void KeyboardMouseManipulator::setByInverseMatrixTrackball( const osg::Matrixd& matrix )
//{
//    setByMatrix( osg::Matrixd::inverse( matrix ) );
//}
//
//
///** Get the position of the manipulator as 4x4 matrix.*/
//osg::Matrixd KeyboardMouseManipulator::getMatrixTrackball() const
//{
//    return osg::Matrixd::translate( 0., 0., _distance ) *
//           osg::Matrixd::rotate( _rotation ) *
//           osg::Matrixd::translate( _center );
//}
//
//
///** Get the position of the manipulator as a inverse matrix of the manipulator,
//    typically used as a model view matrix.*/
//osg::Matrixd KeyboardMouseManipulator::getInverseMatrixTrackball() const
//{
//    return osg::Matrixd::translate( -_center ) *
//           osg::Matrixd::rotate( _rotation.inverse() ) *
//           osg::Matrixd::translate( 0.0, 0.0, -_distance );
//}
//
//
//// doc in parent
//void KeyboardMouseManipulator::setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation )
//{
//    _center = eye + rotation * osg::Vec3d( 0., 0., -_distance );
//    _rotation = rotation;
//
//    // fix current rotation
//    if( getVerticalAxisFixed() )
//        fixVerticalAxis( _center, _rotation, true );
//}
//
//
//// doc in parent
//void KeyboardMouseManipulator::getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const
//{
//    eye = _center - _rotation * osg::Vec3d( 0., 0., -_distance );
//    rotation = _rotation;
//}
//
//
//// doc in parent
//void KeyboardMouseManipulator::setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up )
//{
//    Vec3d lv( center - eye );
//
//    Vec3d f( lv );
//    f.normalize();
//    Vec3d s( f^up );
//    s.normalize();
//    Vec3d u( s^f );
//    u.normalize();
//
//    osg::Matrixd rotation_matrix( s[0], u[0], -f[0], 0.0f,
//                            s[1], u[1], -f[1], 0.0f,
//                            s[2], u[2], -f[2], 0.0f,
//                            0.0f, 0.0f,  0.0f, 1.0f );
//
//    _center = center;
//    _distance = lv.length();
//    _rotation = rotation_matrix.getRotate().inverse();
//
//    // fix current rotation
//    if( getVerticalAxisFixed() )
//        fixVerticalAxis( _center, _rotation, true );
//}
//
//
//// doc in parent
//void KeyboardMouseManipulator::getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const
//{
//    center = _center;
//    eye = _center + _rotation * osg::Vec3d( 0., 0., _distance );
//    up = _rotation * osg::Vec3d( 0., 1., 0. );
//}
//
//
///** Sets the transformation by heading. Heading is given as an angle in radians giving a azimuth in xy plane.
//    Its meaning is similar to longitude used in cartography and navigation.
//    Positive number is going to the east direction.*/
//void KeyboardMouseManipulator::setHeading( double azimuth )
//{
//    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
//    Vec3d localUp = getUpVector( coordinateFrame );
//    Vec3d localRight = getSideVector( coordinateFrame );
//
//    Vec3d dir = Quat( getElevation(), localRight ) * Quat( azimuth, localUp ) * Vec3d( 0., -_distance, 0. );
//
//    setTransformation( _center + dir, _center, localUp );
//}
//
//
///// Returns the heading in radians. \sa setHeading
//double KeyboardMouseManipulator::getHeading() const
//{
//    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
//    Vec3d localFront = getFrontVector( coordinateFrame );
//    Vec3d localRight = getSideVector( coordinateFrame );
//
//    Vec3d center, eye, tmp;
//    getTransformation( eye, center, tmp );
//
//    Plane frontPlane( localFront, center );
//    double frontDist = frontPlane.distance( eye );
//    Plane rightPlane( localRight, center );
//    double rightDist = rightPlane.distance( eye );
//
//    return atan2( rightDist, -frontDist );
//}
//
//
///** Sets the transformation by elevation. Elevation is given as an angle in radians from xy plane.
//    Its meaning is similar to latitude used in cartography and navigation.
//    Positive number is going to the north direction, negative to the south.*/
//void KeyboardMouseManipulator::setElevation( double elevation )
//{
//    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
//    Vec3d localUp = getUpVector( coordinateFrame );
//    Vec3d localRight = getSideVector( coordinateFrame );
//
//    Vec3d dir = Quat( -elevation, localRight ) * Quat( getHeading(), localUp ) * Vec3d( 0., -_distance, 0. );
//
//    setTransformation( _center + dir, _center, localUp );
//}
//
//
///// Returns the elevation in radians. \sa setElevation
//double KeyboardMouseManipulator::getElevation() const
//{
//    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
//    Vec3d localUp = getUpVector( coordinateFrame );
//    localUp.normalize();
//
//    Vec3d center, eye, tmp;
//    getTransformation( eye, center, tmp );
//
//    Plane plane( localUp, center );
//    double dist = plane.distance( eye );
//
//    return asin( -dist / (eye-center).length() );
//}
//
//
//// doc in parent
//bool KeyboardMouseManipulator::handleMouseWheel( const GUIEventAdapter& ea, GUIActionAdapter& us )
//{
//    osgGA::GUIEventAdapter::ScrollingMotion sm = ea.getScrollingMotion();
//
//    // handle centering
//    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
//    {
//
//        if( ((sm == GUIEventAdapter::SCROLL_DOWN && _wheelZoomFactor > 0.)) ||
//            ((sm == GUIEventAdapter::SCROLL_UP   && _wheelZoomFactor < 0.)) )
//        {
//
//            if( getAnimationTime() <= 0. )
//            {
//                // center by mouse intersection (no animation)
//                setCenterByMousePointerIntersection( ea, us );
//            }
//            else
//            {
//                // start new animation only if there is no animation in progress
//                if( !isAnimating() )
//                    startAnimationByMousePointerIntersection( ea, us );
//
//            }
//
//        }
//    }
//
//    switch( sm )
//    {
//        // mouse scroll up event
//        case GUIEventAdapter::SCROLL_UP:
//        {
//            // perform zoom
//            zoomModel( _wheelZoomFactor, true );
//            us.requestRedraw();
//            us.requestContinuousUpdate( isAnimating() || _thrown );
//            return true;
//        }
//
//        // mouse scroll down event
//        case GUIEventAdapter::SCROLL_DOWN:
//        {
//            // perform zoom
//            zoomModel( -_wheelZoomFactor, true );
//            us.requestRedraw();
//            us.requestContinuousUpdate( isAnimating() || _thrown );
//            return true;
//        }
//
//        // unhandled mouse scrolling motion
//        default:
//            return false;
//   }
//}
//
//
//// doc in parent
//bool KeyboardMouseManipulator::performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy )
//{
//    // rotate camera
//    if( getVerticalAxisFixed() )
//        rotateWithFixedVertical( dx, dy );
//    else
//        rotateTrackball( _ga_t0->getXnormalized(), _ga_t0->getYnormalized(),
//                         _ga_t1->getXnormalized(), _ga_t1->getYnormalized(),
//                         getThrowScale( eventTimeDelta ) );
//    return true;
//}
//
//
//// doc in parent
//bool KeyboardMouseManipulator::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
//{
//    // pan model
//    float scale = -0.3f * _distance * getThrowScale( eventTimeDelta );
//    panModel( dx*scale, dy*scale );
//    return true;
//}
//
//
//// doc in parent
//bool KeyboardMouseManipulator::performMovementRightMouseButton( const double eventTimeDelta, const double /*dx*/, const double dy )
//{
//    // zoom model
//    zoomModel( dy * getThrowScale( eventTimeDelta ), true );
//    return true;
//}
//
//
//bool KeyboardMouseManipulator::performMouseDeltaMovement( const float dx, const float dy )
//{
//    // rotate camera
//    if( getVerticalAxisFixed() )
//        rotateWithFixedVertical( dx, dy );
//    else
//        rotateTrackball( 0.f, 0.f, dx, dy, 1.f );
//
//    return true;
//}
//
//
//void KeyboardMouseManipulator::applyAnimationStep( const double currentProgress, const double prevProgress )
//{
//    OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData* >( _animationData.get() );
//    assert( ad );
//
//    // compute new center
//    osg::Vec3d prevCenter, prevEye, prevUp;
//    getTransformation( prevEye, prevCenter, prevUp );
//    osg::Vec3d newCenter = osg::Vec3d(prevCenter) + (ad->_movement * (currentProgress - prevProgress));
//
//    // fix vertical axis
//    if( getVerticalAxisFixed() )
//    {
//
//        CoordinateFrame coordinateFrame = getCoordinateFrame( newCenter );
//        Vec3d localUp = getUpVector( coordinateFrame );
//
//        fixVerticalAxis( newCenter - prevEye, prevUp, prevUp, localUp, false );
//   }
//
//   // apply new transformation
//   setTransformation( prevEye, newCenter, prevUp );
//}
//
//
//bool KeyboardMouseManipulator::startAnimationByMousePointerIntersection(
//      const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
//{
//    // get current transformation
//    osg::Vec3d prevCenter, prevEye, prevUp;
//    getTransformation( prevEye, prevCenter, prevUp );
//
//    // center by mouse intersection
//    if( !setCenterByMousePointerIntersection( ea, us ) )
//        return false;
//
//    OrbitAnimationData *ad = dynamic_cast< OrbitAnimationData*>( _animationData.get() );
//    assert( ad );
//
//    // setup animation data and restore original transformation
//    ad->start( osg::Vec3d(_center) - prevCenter, ea.getTime() );
//    setTransformation( prevEye, prevCenter, prevUp );
//
//    return true;
//}
//
//
//void KeyboardMouseManipulator::OrbitAnimationData::start( const osg::Vec3d& movement, const double startTime )
//{
//    AnimationData::start( startTime );
//
//    _movement = movement;
//}
//
//
///** Performs trackball rotation based on two points given, for example,
//    by mouse pointer on the screen.
//
//    Scale parameter is useful, for example, when manipulator is thrown.
//    It scales the amount of rotation based, for example, on the current frame time.*/
//void KeyboardMouseManipulator::rotateTrackball( const float px0, const float py0,
//                                        const float px1, const float py1, const float /*scale*/ )
//{
//    osg::Vec3d axis;
//    float angle;
//
//    trackball( axis, angle, px1, py1, px0, py0 );
//
//    Quat new_rotate;
//    new_rotate.makeRotate( angle, axis );
//
//    _rotation = _rotation * new_rotate;
//}
//
//
///** Performs rotation horizontally by dx parameter and vertically by dy parameter,
//    while keeping UP vector.*/
//void KeyboardMouseManipulator::rotateWithFixedVertical( const float dx, const float dy )
//{
//    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
//    Vec3d localUp = getUpVector( coordinateFrame );
//
//    rotateYawPitch( _rotation, dx, dy, localUp );
//}
//
//
///** Performs rotation horizontally by dx parameter and vertically by dy parameter,
//    while keeping UP vector given by up parameter.*/
//void KeyboardMouseManipulator::rotateWithFixedVertical( const float dx, const float dy, const Vec3f& up )
//{
//    rotateYawPitch( _rotation, dx, dy, up );
//}
//
//
///** Moves camera in x,y,z directions given in camera local coordinates.*/
//void KeyboardMouseManipulator::panModel( const float dx, const float dy, const float dz )
//{
//    Matrix rotation_matrix;
//    rotation_matrix.makeRotate( _rotation );
//
//    Vec3d dv( dx, dy, dz );
//
//    _center += dv * rotation_matrix;
//}
//
//
///** Changes the distance of camera to the focal center.
//    If pushForwardIfNeeded is true and minimumDistance is reached,
//    the focal center is moved forward. Otherwise, distance is limited
//    to its minimum value.
//    \sa OrbitManipulator::setMinimumDistance
// */
//void KeyboardMouseManipulator::zoomModel( const float dy, bool pushForwardIfNeeded )
//{
//    // scale
//    float scale = 1.0f + dy;
//
//    // minimum distance
//    float minDist = _minimumDistance;
//    if( getRelativeFlag( _minimumDistanceFlagIndex ) )
//        minDist *= _modelSize;
//
//    if( _distance*scale > minDist )
//    {
//        // regular zoom
//        _distance *= scale;
//    }
//    else
//    {
//        if( pushForwardIfNeeded )
//        {
//            // push the camera forward
//            float scale = -_distance;
//            Matrixd rotation_matrix( _rotation );
//            Vec3d dv = (Vec3d( 0.0f, 0.0f, -1.0f ) * rotation_matrix) * (dy * scale);
//            _center += dv;
//        }
//        else
//        {
//            // set distance on its minimum value
//            _distance = minDist;
//        }
//    }
//}
//
//
///**
// * Simulate a track-ball.  Project the points onto the virtual
// * trackball, then figure out the axis of rotation, which is the cross
// * product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
// * Note:  This is a deformed trackball-- is a trackball in the center,
// * but is deformed into a hyperbolic sheet of rotation away from the
// * center.  This particular function was chosen after trying out
// * several variations.
// *
// * It is assumed that the arguments to this routine are in the range
// * (-1.0 ... 1.0)
// */
//void KeyboardMouseManipulator::trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y )
//{
//    /*
//        * First, figure out z-coordinates for projection of P1 and P2 to
//        * deformed sphere
//        */
//
//    osg::Matrixd rotation_matrix(_rotation);
//
//    osg::Vec3d uv = Vec3d(0.0f,1.0f,0.0f)*rotation_matrix;
//    osg::Vec3d sv = Vec3d(1.0f,0.0f,0.0f)*rotation_matrix;
//    osg::Vec3d lv = Vec3d(0.0f,0.0f,-1.0f)*rotation_matrix;
//
//    osg::Vec3d p1 = sv * p1x + uv * p1y - lv * tb_project_to_sphere(_trackballSize, p1x, p1y);
//    osg::Vec3d p2 = sv * p2x + uv * p2y - lv * tb_project_to_sphere(_trackballSize, p2x, p2y);
//
//    /*
//        *  Now, we want the cross product of P1 and P2
//        */
//    axis = p2^p1;
//    axis.normalize();
//
//    /*
//        *  Figure out how much to rotate around that axis.
//        */
//    float t = (p2 - p1).length() / (2.0 * _trackballSize);
//
//    /*
//        * Avoid problems with out-of-control values...
//        */
//    if (t > 1.0) t = 1.0;
//    if (t < -1.0) t = -1.0;
//    angle = inRadians(asin(t));
//}
//
//
///**
// * Helper trackball method that projects an x,y pair onto a sphere of radius r OR
// * a hyperbolic sheet if we are away from the center of the sphere.
// */
//float KeyboardMouseManipulator::tb_project_to_sphere( float r, float x, float y )
//{
//    float d, t, z;
//
//    d = sqrt(x*x + y*y);
//                                 /* Inside sphere */
//    if (d < r * 0.70710678118654752440)
//    {
//        z = sqrt(r*r - d*d);
//    }                            /* On hyperbola */
//    else
//    {
//        t = r / 1.41421356237309504880;
//        z = t*t / d;
//    }
//    return z;
//}
//
//
///** Get the FusionDistanceMode. Used by SceneView for setting up stereo convergence.*/
//osgUtil::SceneView::FusionDistanceMode KeyboardMouseManipulator::getFusionDistanceMode() const
//{
//    return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE;
//}
//
///** Get the FusionDistanceValue. Used by SceneView for setting up stereo convergence.*/
//float KeyboardMouseManipulator::getFusionDistanceValue() const
//{
//    return _distance;
//}
//
//
///** Set the center of the manipulator. */
//void KeyboardMouseManipulator::setCenter( const Vec3d& center )
//{
//    _center = center;
//}
//
//
///** Get the center of the manipulator. */
//const Vec3d& KeyboardMouseManipulator::getCenter() const
//{
//    return _center;
//}
//
//
///** Set the rotation of the manipulator. */
//void KeyboardMouseManipulator::setRotation( const Quat& rotation )
//{
//    _rotation = rotation;
//}
//
//
///** Get the rotation of the manipulator. */
//const Quat& KeyboardMouseManipulator::getRotation() const
//{
//    return _rotation;
//}
//
//
///** Set the distance of camera to the center. */
//void KeyboardMouseManipulator::setDistance( double distance )
//{
//    _distance = distance;
//}
//
//
///** Get the distance of the camera to the center. */
//double KeyboardMouseManipulator::getDistance() const
//{
//    return _distance;
//}
//
//
///** Set the size of the trackball. Value is relative to the model size. */
//void KeyboardMouseManipulator::setTrackballSize( const double& size )
//{
//    /*
//    * This size should really be based on the distance from the center of
//    * rotation to the point on the object underneath the mouse.  That
//    * point would then track the mouse as closely as possible.  This is a
//    * simple example, though, so that is left as an Exercise for the
//    * Programmer.
//    */
//    _trackballSize = size;
//    clampBetweenRange( _trackballSize, 0.1, 1.0, "TrackballManipulator::setTrackballSize(float)" );
//}
//
//
///** Set the mouse wheel zoom factor.
//    The amount of camera movement on each mouse wheel event
//    is computed as the current distance to the center multiplied by this factor.
//    For example, value of 0.1 will short distance to center by 10% on each wheel up event.
//    Use negative value for reverse mouse wheel direction.*/
//void KeyboardMouseManipulator::setWheelZoomFactor( double wheelZoomFactor )
//{
//    _wheelZoomFactor = wheelZoomFactor;
//}
//
//
///** Set the minimum distance of the eye point from the center
//    before the center is pushed forward.*/
//void KeyboardMouseManipulator::setMinimumDistance( const double& minimumDistance, bool relativeToModelSize )
//{
//    _minimumDistance = minimumDistance;
//    setRelativeFlag( _minimumDistanceFlagIndex, relativeToModelSize );
//}
//
//
///** Get the minimum distance of the eye point from the center
//    before the center is pushed forward.*/
//double KeyboardMouseManipulator::getMinimumDistance( bool *relativeToModelSize ) const
//{
//    if( relativeToModelSize )
//        *relativeToModelSize = getRelativeFlag( _minimumDistanceFlagIndex );
//
//    return _minimumDistance;
//}
//
////end Trackball
