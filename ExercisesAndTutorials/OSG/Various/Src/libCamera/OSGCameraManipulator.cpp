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

//OSGCameraManipulator::OSGCameraManipulator():
//m_bCtrl(false),
//m_bShift(false),
//m_cdbRotationFactor(osg::PI*0.001)
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
//	m_vecdbDirection.set(0,1,0);
//}
//
//OSGCameraManipulator::~OSGCameraManipulator()	{
//}

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

/*
void OSGCameraManipulator::computeHomePosition()	{
	_homeCenter = osg::Vec3(0.0, 0.0, 0.0);
	_homeEye = osg::Vec3(0.0, 3.0, 0.0);

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
*/
#include <osg/BoundsChecking>
#include <cassert>

using namespace osg;
using namespace osgGA;



int OSGCameraManipulator::_minimumDistanceFlagIndex = allocateRelativeFlag();


/// Constructor.
OSGCameraManipulator::OSGCameraManipulator( int flags )
   : inherited( flags ),
     _distance( 1. ),
     _trackballSize( 0.8 )
{
	    setVerticalAxisFixed( false );

    setMinimumDistance( 0.05, true );
    setWheelZoomFactor( 0.1 );
    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT )
        setAnimationTime( 0.2 );
}


/// Constructor.
OSGCameraManipulator::OSGCameraManipulator(const OSGCameraManipulator& om, const osg::CopyOp& copyOp)
   : osg::Object(om, copyOp),
     inherited( om, copyOp ),
     _center( om._center ),
     _rotation( om._rotation ),
     _distance( om._distance ),
     _trackballSize( om._trackballSize ),
     _wheelZoomFactor( om._wheelZoomFactor ),
     _minimumDistance( om._minimumDistance )
{
}


/** Set the position of the manipulator using a 4x4 matrix.*/
void OSGCameraManipulator::setByMatrix( const osg::Matrixd& matrix )
{
    _center = osg::Vec3d( 0., 0., -_distance ) * matrix;
    _rotation = matrix.getRotate();

    // fix current rotation
    if( getVerticalAxisFixed() )
        fixVerticalAxis( _center, _rotation, true );
}


/** Set the position of the manipulator using a 4x4 matrix.*/
void OSGCameraManipulator::setByInverseMatrix( const osg::Matrixd& matrix )
{
    setByMatrix( osg::Matrixd::inverse( matrix ) );
}


/** Get the position of the manipulator as 4x4 matrix.*/
osg::Matrixd OSGCameraManipulator::getMatrix() const
{
    return osg::Matrixd::translate( 0., 0., _distance ) *
           osg::Matrixd::rotate( _rotation ) *
           osg::Matrixd::translate( _center );
}


/** Get the position of the manipulator as a inverse matrix of the manipulator,
    typically used as a model view matrix.*/
osg::Matrixd OSGCameraManipulator::getInverseMatrix() const
{
    return osg::Matrixd::translate( -_center ) *
           osg::Matrixd::rotate( _rotation.inverse() ) *
           osg::Matrixd::translate( 0.0, 0.0, -_distance );
}


// doc in parent
void OSGCameraManipulator::setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation )
{
    _center = eye + rotation * osg::Vec3d( 0., 0., -_distance );
    _rotation = rotation;

    // fix current rotation
    if( getVerticalAxisFixed() )
        fixVerticalAxis( _center, _rotation, true );
}


// doc in parent
void OSGCameraManipulator::getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const
{
    eye = _center - _rotation * osg::Vec3d( 0., 0., -_distance );
    rotation = _rotation;
}


// doc in parent
void OSGCameraManipulator::setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up )
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
void OSGCameraManipulator::getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const
{
    center = _center;
    eye = _center + _rotation * osg::Vec3d( 0., 0., _distance );
    up = _rotation * osg::Vec3d( 0., 1., 0. );
}


/** Sets the transformation by heading. Heading is given as an angle in radians giving a azimuth in xy plane.
    Its meaning is similar to longitude used in cartography and navigation.
    Positive number is going to the east direction.*/
void OSGCameraManipulator::setHeading( double azimuth )
{
    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
    Vec3d localUp = getUpVector( coordinateFrame );
    Vec3d localRight = getSideVector( coordinateFrame );

    Vec3d dir = Quat( getElevation(), localRight ) * Quat( azimuth, localUp ) * Vec3d( 0., -_distance, 0. );

    setTransformation( _center + dir, _center, localUp );
}


/// Returns the heading in radians. \sa setHeading
double OSGCameraManipulator::getHeading() const
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
void OSGCameraManipulator::setElevation( double elevation )
{
    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
    Vec3d localUp = getUpVector( coordinateFrame );
    Vec3d localRight = getSideVector( coordinateFrame );

    Vec3d dir = Quat( -elevation, localRight ) * Quat( getHeading(), localUp ) * Vec3d( 0., -_distance, 0. );

    setTransformation( _center + dir, _center, localUp );
}


/// Returns the elevation in radians. \sa setElevation
double OSGCameraManipulator::getElevation() const
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
bool OSGCameraManipulator::handleMouseWheel( const GUIEventAdapter& ea, GUIActionAdapter& us )
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
bool OSGCameraManipulator::performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy )
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
bool OSGCameraManipulator::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
    // pan model
    float scale = -0.3f * _distance * getThrowScale( eventTimeDelta );
    panModel( dx*scale, dy*scale );
    return true;
}


// doc in parent
bool OSGCameraManipulator::performMovementRightMouseButton( const double eventTimeDelta, const double /*dx*/, const double dy )
{
    // zoom model
    zoomModel( dy * getThrowScale( eventTimeDelta ), true );
    return true;
}


bool OSGCameraManipulator::performMouseDeltaMovement( const float dx, const float dy )
{
    // rotate camera
    if( getVerticalAxisFixed() )
        rotateWithFixedVertical( dx, dy );
    else
        rotateTrackball( 0.f, 0.f, dx, dy, 1.f );

    return true;
}


void OSGCameraManipulator::applyAnimationStep( const double currentProgress, const double prevProgress )
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


bool OSGCameraManipulator::startAnimationByMousePointerIntersection(
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


void OSGCameraManipulator::OrbitAnimationData::start( const osg::Vec3d& movement, const double startTime )
{
    AnimationData::start( startTime );

    _movement = movement;
}


/** Performs trackball rotation based on two points given, for example,
    by mouse pointer on the screen.

    Scale parameter is useful, for example, when manipulator is thrown.
    It scales the amount of rotation based, for example, on the current frame time.*/
void OSGCameraManipulator::rotateTrackball( const float px0, const float py0,
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
void OSGCameraManipulator::rotateWithFixedVertical( const float dx, const float dy )
{
    CoordinateFrame coordinateFrame = getCoordinateFrame( _center );
    Vec3d localUp = getUpVector( coordinateFrame );

    rotateYawPitch( _rotation, dx, dy, localUp );
}


/** Performs rotation horizontally by dx parameter and vertically by dy parameter,
    while keeping UP vector given by up parameter.*/
void OSGCameraManipulator::rotateWithFixedVertical( const float dx, const float dy, const Vec3f& up )
{
    rotateYawPitch( _rotation, dx, dy, up );
}


/** Moves camera in x,y,z directions given in camera local coordinates.*/
void OSGCameraManipulator::panModel( const float dx, const float dy, const float dz )
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
void OSGCameraManipulator::zoomModel( const float dy, bool pushForwardIfNeeded )
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
void OSGCameraManipulator::trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y )
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
float OSGCameraManipulator::tb_project_to_sphere( float r, float x, float y )
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
osgUtil::SceneView::FusionDistanceMode OSGCameraManipulator::getFusionDistanceMode() const
{
    return osgUtil::SceneView::USE_FUSION_DISTANCE_VALUE;
}

/** Get the FusionDistanceValue. Used by SceneView for setting up stereo convergence.*/
float OSGCameraManipulator::getFusionDistanceValue() const
{
    return _distance;
}


/** Set the center of the manipulator. */
void OSGCameraManipulator::setCenter( const Vec3d& center )
{
    _center = center;
}


/** Get the center of the manipulator. */
const Vec3d& OSGCameraManipulator::getCenter() const
{
    return _center;
}


/** Set the rotation of the manipulator. */
void OSGCameraManipulator::setRotation( const Quat& rotation )
{
    _rotation = rotation;
}


/** Get the rotation of the manipulator. */
const Quat& OSGCameraManipulator::getRotation() const
{
    return _rotation;
}


/** Set the distance of camera to the center. */
void OSGCameraManipulator::setDistance( double distance )
{
    _distance = distance;
}


/** Get the distance of the camera to the center. */
double OSGCameraManipulator::getDistance() const
{
    return _distance;
}


/** Set the size of the trackball. Value is relative to the model size. */
void OSGCameraManipulator::setTrackballSize( const double& size )
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
void OSGCameraManipulator::setWheelZoomFactor( double wheelZoomFactor )
{
    _wheelZoomFactor = wheelZoomFactor;
}


/** Set the minimum distance of the eye point from the center
    before the center is pushed forward.*/
void OSGCameraManipulator::setMinimumDistance( const double& minimumDistance, bool relativeToModelSize )
{
    _minimumDistance = minimumDistance;
    setRelativeFlag( _minimumDistanceFlagIndex, relativeToModelSize );
}


/** Get the minimum distance of the eye point from the center
    before the center is pushed forward.*/
double OSGCameraManipulator::getMinimumDistance( bool *relativeToModelSize ) const
{
    if( relativeToModelSize )
        *relativeToModelSize = getRelativeFlag( _minimumDistanceFlagIndex );

    return _minimumDistance;
}
