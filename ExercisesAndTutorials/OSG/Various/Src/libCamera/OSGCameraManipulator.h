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

#ifndef OSG_CAMERA_MANIPULATOR_H
#define OSG_CAMERA_MANIPULATOR_H

#include <osgGA/CameraManipulator>
#include <osgGA/GUIEventAdapter>

#include <iostream>

namespace VR {

	class OSGCameraManipulator : public osgGA::CameraManipulator	{
	public:
		OSGCameraManipulator();

		virtual const char* className() const;
		virtual void setByMatrix(const osg::Matrixd &matrix);
		virtual void setByInverseMatrix(const osg::Matrixd &invmat);
		virtual osg::Matrixd getMatrix() const;
		virtual osg::Matrixd getInverseMatrix() const ;
		virtual void setNode(osg::Node* node);
		virtual const osg::Node* getNode() const;
		virtual osg::Node* getNode();
		virtual void computeHomePosition();
		virtual void home(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&aa) ;
		void home(double);

		virtual void init(const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa);

		bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &aa);

	protected:

		virtual ~OSGCameraManipulator();

		osg::observer_ptr<osg::Node> m_pNode;
		osg::Matrixd m_mtrxdbMatrix;		//View matrix
		osg::Matrixd m_mtrxdbInverseMatrix;	//Current position with the inverse matrix
		osg::Matrixd m_mtrxdbOffset;		//Corrects view-matrix for rotations on Z

		double		m_dbForwardFactor;		//Forward move value
		double		m_dbDefaultMoveSpeed;	//Speed for a move in any direction

		double		m_dbDirectionRotationRate;	//Side rotation angle

		double		m_dbPitchOffsetRate;	//Angle of rotation on Z 
		double		m_dbPitchOffset;		//Accumulates angle of rotation on Z
		double		m_dbLateralRotationRate;		//Angle of rotation on X
		const double m_cdbRotationFactor;	//Angle in radians

		osg::Vec3d	m_vecdbPosition;		//Eye (position of the camera)
		osg::Vec3d	m_vecdbDirection;		//Center (center of objects) - Eye

		bool m_bCtrl;
		bool m_bShift;

		bool keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		bool keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);

		void updateMatrices();
		void setCameraPosition();


//================================================================================================
/*        virtual bool performMovement();
        virtual bool performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy );
		inline bool getVerticalAxisFixed() const;

		bool handleMouseDrag( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
		bool handleMousePush( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );		
		bool handleMouseRelease( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );

		virtual void rotateWithFixedVertical( const float dx, const float dy );
        virtual void rotateWithFixedVertical( const float dx, const float dy, const osg::Vec3f& up );

        osg::Vec3d _center;
        osg::Quat  _rotation;
        double     _distance;

        // mouse state
        bool _thrown;
        bool _allowThrow;
        float _mouseCenterX, _mouseCenterY;

        // internal event stack comprising last two mouse events.
        osg::ref_ptr< const osgGA::GUIEventAdapter > _ga_t1;
        osg::ref_ptr< const osgGA::GUIEventAdapter > _ga_t0;

        double _delta_frame_time;
		double _last_frame_time;

        bool _verticalAxisFixed;

        virtual void rotateTrackball( const float px0, const float py0,
                                      const float px1, const float py1, const float scale );

        float getThrowScale( const double eventTimeDelta ) const;
        static void rotateYawPitch( osg::Quat& rotation, const double yaw, const double pitch,
                                    const osg::Vec3d& localUp = osg::Vec3d( 0.,0.,0.) );

        void trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y );
		float tb_project_to_sphere( float r, float x, float y );

        static void fixVerticalAxis( osg::Quat& rotation, const osg::Vec3d& localUp, bool disallowFlipOver );
        void fixVerticalAxis( osg::Vec3d& eye, osg::Quat& rotation, bool disallowFlipOver );
        static void fixVerticalAxis( const osg::Vec3d& forward, const osg::Vec3d& up, osg::Vec3d& newUp,
                                     const osg::Vec3d& localUp, bool disallowFlipOver );

        double _trackballSize;

        void addMouseEvent( const osgGA::GUIEventAdapter& ea );
        void flushMouseEventStack();
       virtual bool isMouseMoving() const;
*/ 
	};
}
#endif //OSG_CAMERA_MANIPULATOR_H