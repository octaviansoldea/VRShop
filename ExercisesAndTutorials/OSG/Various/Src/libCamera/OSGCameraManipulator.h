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

#include <osgGA/OrbitManipulator>
#include <osgGA/CameraManipulator>
#include <osgGA/StandardManipulator>

using namespace osgGA;

namespace VR {

	class OSGCameraManipulator : public osgGA::StandardManipulator
	{
		bool m_bUFO;
	public:

		void initUFO();

		OSGCameraManipulator( int flags = DEFAULT_SETTINGS );
		OSGCameraManipulator( const OSGCameraManipulator& om,
			const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );
		
		virtual void setByMatrix( const osg::Matrixd &matrix ) ;
        virtual void setByInverseMatrix( const osg::Matrixd &invmat);
        virtual osg::Matrixd getMatrix() const;
        virtual osg::Matrixd getInverseMatrix() const ;

		/** Handles incoming osgGA events */
        bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &aa);

		void updateUFOOrbit();
		void updateOrbitUFO();

		//Begin UFOManipulator 
		public:

        /** return className
          \return returns constant "UFO"
          */

        /** Set the current position with a matrix
          \param matrix  A viewpoint matrix.
         */
        virtual void setByMatrixUFO( const osg::Matrixd &matrix ) ;

        /** Set the current position with the inverse matrix
          \param invmat The inverse of a viewpoint matrix
          */
        virtual void setByInverseMatrixUFO( const osg::Matrixd &invmat);

        /** Get the current viewmatrix */
        virtual osg::Matrixd getMatrixUFO() const;

        /** Get the current inverse view matrix */
        virtual osg::Matrixd getInverseMatrixUFO() const ;

        /** Set the  subgraph this manipulator is driving the eye through.
            \param node     root of subgraph
         */
        virtual void setNode(osg::Node* node);

        /** Get the root node of the subgraph this manipulator is driving the eye through (const)*/
        virtual const osg::Node* getNode() const;

        /** Get the root node of the subgraph this manipulator is driving the eye through */
        virtual osg::Node* getNode();

        /** Computes the home position based on the extents and scale of the
            scene graph rooted at node */
        virtual void computeHomePosition();

        /** Sets the viewpoint matrix to the home position */
        virtual void home(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) ;
        void home(double);

        virtual void init(const GUIEventAdapter& ,GUIActionAdapter&);

        /** Reports Usage parameters to the application */
        void getUsage(osg::ApplicationUsage& usage) const;

        /** Report the current position as LookAt vectors */
        void getCurrentPositionAsLookAt( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up );


        void setMinHeight( double in_min_height ) { _minHeightAboveGround = in_min_height; }
        double getMinHeight() const { return _minHeightAboveGround; }

        void setMinDistance( double in_min_dist ) { _minDistanceInFront = in_min_dist; }
        double getMinDistance() const { return _minDistanceInFront; }

        void setForwardSpeed( double in_fs ) { _forwardSpeed = in_fs; }
        double getForwardSpeed() const { return _forwardSpeed; }

        void setSideSpeed( double in_ss ) { _sideSpeed = in_ss; }
        double getSideSpeed() const { return _sideSpeed; }

        void setRotationSpeed( double in_rot_speed ) { _directionRotationRate = in_rot_speed; }
        double getRotationSpeed() const { return _directionRotationRate; }

    protected:

        bool intersect(const osg::Vec3d& start, const osg::Vec3d& end, osg::Vec3d& intersection) const;

        osg::observer_ptr<osg::Node> _node;
        float       _viewAngle;
        osg::Matrixd _matrix;
        osg::Matrixd _inverseMatrix;
        osg::Matrixd _offset;

        double    _minHeightAboveGround;
        double    _minDistanceInFront;

        double    _speedEpsilon;
        double    _forwardSpeed;
        double    _sideSpeed;
        double    _upSpeed;
        double    _speedAccelerationFactor;
        double    _speedDecelerationFactor;

        bool      _decelerateUpSideRate;

        double    _directionRotationEpsilon;
        double    _directionRotationRate;
        double    _directionRotationAcceleration;
        double    _directionRotationDeceleration;

        double    _viewOffsetDelta;
        double    _pitchOffsetRate;
        double    _pitchOffset;
        double    _yawOffsetRate;
        double    _yawOffset;

        double    _t0;
        double    _dt;
        osg::Vec3d _direction;
        osg::Vec3d _position;


        bool _shift;
        bool _ctrl;
        bool _decelerateOffsetRate;

        bool _straightenOffset;

        void _stop();
        void _keyDown( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &);
        void _keyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &);
        void _frame(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &);

        void _adjustPosition();
		//End UFOManipulator 

		//Begin OrbitManipulator 

		typedef StandardManipulator inherited;

	public:

		META_Object( VR, OSGCameraManipulator );

		virtual void setByMatrixOrbit( const osg::Matrixd& matrix );
		virtual void setByInverseMatrixOrbit( const osg::Matrixd& matrix );
		virtual osg::Matrixd getMatrixOrbit() const;
		virtual osg::Matrixd getInverseMatrixOrbit() const;

		virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation );
		virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );
		virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const;
		virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const;

		void setHeading( double azimuth );
		double getHeading() const;
		void setElevation( double elevation );
		double getElevation() const;

		virtual void setCenter( const osg::Vec3d& center );
		const osg::Vec3d& getCenter() const;
		virtual void setRotation( const osg::Quat& rotation );
		const osg::Quat& getRotation() const;
		virtual void setDistance( double distance );
		double getDistance() const;

		virtual void setTrackballSize( const double& size );
		inline double getTrackballSize() const;
		virtual void setWheelZoomFactor( double wheelZoomFactor );
		inline double getWheelZoomFactor() const;

		virtual void setMinimumDistance( const double& minimumDistance, bool relativeToModelSize = false );
		double getMinimumDistance( bool *relativeToModelSize = NULL ) const;

		virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const;
		virtual float getFusionDistanceValue() const;

	protected:

		virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );

		virtual bool performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy );
		virtual bool performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy );
		virtual bool performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy );
		virtual bool performMouseDeltaMovement( const float dx, const float dy );
		virtual void applyAnimationStep( const double currentProgress, const double prevProgress );

		virtual void rotateTrackball( const float px0, const float py0,
			const float px1, const float py1, const float scale );
		virtual void rotateWithFixedVertical( const float dx, const float dy );
		virtual void rotateWithFixedVertical( const float dx, const float dy, const osg::Vec3f& up );
		virtual void panModel( const float dx, const float dy, const float dz = 0.f );
		virtual void zoomModel( const float dy, bool pushForwardIfNeeded = true );
		void trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y );
		float tb_project_to_sphere( float r, float x, float y );
		virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );

		osg::Vec3d _center;
		osg::Quat  _rotation;
		double     _distance;

		double _trackballSize;
		double _wheelZoomFactor;

		double _minimumDistance;
		static int _minimumDistanceFlagIndex;

		class OrbitAnimationData : public osgGA::StandardManipulator::AnimationData {
		public:
			osg::Vec3d _movement;
			void start( const osg::Vec3d& movement, const double startTime );
		};
		virtual void allocAnimationData() { _animationData = new OrbitAnimationData(); }
		
	}; // class OSGCameraManipulator

	//
	//  inline functions
	//

	/** Get the size of the trackball relative to the model size. */
	inline double OSGCameraManipulator::getTrackballSize() const  { return _trackballSize; }
	/** Get the mouse wheel zoom factor.*/
	inline double OSGCameraManipulator::getWheelZoomFactor() const  { return _wheelZoomFactor; }

	//End OrbitManipulator 

} // namespacve VR


//	class OSGCameraManipulator : public osgGA::StandardManipulator	{
//		bool m_bUFO;
//	public:
//		OSGCameraManipulator( int flags = DEFAULT_SETTINGS );
//		OSGCameraManipulator( const OSGCameraManipulator& om,
//			const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );
//
//		virtual const char* className() const;
//
//		virtual void setByMatrix(const osg::Matrixd &matrix);
//		virtual void setByInverseMatrix(const osg::Matrixd &invmat);
//		virtual osg::Matrixd getMatrix() const;
//		virtual osg::Matrixd getInverseMatrix() const;
//
//		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &us);
//
//		void updateUFOTrackball();
//		void updateTrackballUFO();
//
//		//begin UFO
//
//
//		
//		virtual void setByMatrixUFO( const osg::Matrixd &matrix ) ;
//		virtual void setByInverseMatrixUFO( const osg::Matrixd &invmat);
//		virtual osg::Matrixd getMatrixUFO() const;
//		virtual osg::Matrixd getInverseMatrixUFO() const ;
//		virtual void setNode(osg::Node* node);
//		virtual const osg::Node* getNode() const;
//		virtual osg::Node* getNode();
//		virtual void computeHomePosition();
//		virtual void home(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) ;
//		void home(double);
//
//		virtual void init(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
//
//	protected:
//
//		osg::observer_ptr<osg::Node> m_pNode;
//		osg::Matrixd m_mtrxdbMatrix;		//View matrix
//		osg::Matrixd m_mtrxdbInverseMatrix;	//Current position with the inverse matrix
//		osg::Matrixd m_mtrxdbOffset;		//Corrects view-matrix for rotations on Z
//
//		double		m_dbForwardFactor;		//Forward move value
//		double		m_dbDefaultMoveSpeed;	//Speed for a move in any direction
//
//		double		m_dbDirectionRotationRate;	//Side rotation angle
//
//		double		m_dbPitchOffsetRate;	//Angle of rotation on Z 
//		double		m_dbPitchOffset;		//Accumulates angle of rotation on Z
//		double		m_dbLateralRotationRate;		//Angle of rotation on X
//		const double m_cdbRotationFactor;	//Angle in radians
//
//		osg::Vec3d	m_vecdbPosition;		//Eye (position of the camera)
//		osg::Vec3d	m_vecdbDirection;		//Center (center of objects) - Eye
//
//		bool m_bCtrl;
//		bool m_bShift;
//
//		bool keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
//		bool keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);
//
//		void updateMatrices();
//
//
//		//end UFO
//
//		//begin Trackball
//		
//		virtual void setByMatrixTrackball(const osg::Matrixd &matrix);
//		virtual void setByInverseMatrixTrackball(const osg::Matrixd &invmat);
//		virtual osg::Matrixd getMatrixTrackball() const;
//		virtual osg::Matrixd getInverseMatrixTrackball() const ;
//		virtual void setNodeTrackball(osg::Node* node);
//		virtual const osg::Node* getNodeTrackball() const;
//		virtual osg::Node* getNodeTrackball();
//
//
//		typedef StandardManipulator inherited;
//
//	public:
//
//
////		META_Object( OSGCameraManipulator, OSGCameraManipulator );
//
//		virtual void setTransformation( const osg::Vec3d& eye, const osg::Quat& rotation );
//		virtual void setTransformation( const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up );
//		virtual void getTransformation( osg::Vec3d& eye, osg::Quat& rotation ) const;
//		virtual void getTransformation( osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up ) const;
//
//		void setHeading( double azimuth );
//		double getHeading() const;
//		void setElevation( double elevation );
//		double getElevation() const;
//
//		virtual void setCenter( const osg::Vec3d& center );
//		const osg::Vec3d& getCenter() const;
//		virtual void setRotation( const osg::Quat& rotation );
//		const osg::Quat& getRotation() const;
//		virtual void setDistance( double distance );
//		double getDistance() const;
//
//		virtual void setTrackballSize( const double& size );
//		inline double getTrackballSize() const;
//		virtual void setWheelZoomFactor( double wheelZoomFactor );
//		inline double getWheelZoomFactor() const;
//
//		virtual void setMinimumDistance( const double& minimumDistance, bool relativeToModelSize = false );
//		double getMinimumDistance( bool *relativeToModelSize = NULL ) const;
//
//		virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const;
//		virtual float getFusionDistanceValue() const;
//
//
//	protected:
////============================================================================================
//        //virtual bool handleKeyDown( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
//        //virtual bool handleKeyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
////============================================================================================
//		virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
//
//		virtual bool performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy );
//		virtual bool performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy );
//		virtual bool performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy );
//		virtual bool performMouseDeltaMovement( const float dx, const float dy );
//		virtual void applyAnimationStep( const double currentProgress, const double prevProgress );
//
//		virtual void rotateTrackball( const float px0, const float py0,
//			const float px1, const float py1, const float scale );
//		virtual void rotateWithFixedVertical( const float dx, const float dy );
//		virtual void rotateWithFixedVertical( const float dx, const float dy, const osg::Vec3f& up );
//		virtual void panModel( const float dx, const float dy, const float dz = 0.f );
//		virtual void zoomModel( const float dy, bool pushForwardIfNeeded = true );
//		void trackball( osg::Vec3d& axis, float& angle, float p1x, float p1y, float p2x, float p2y );
//		float tb_project_to_sphere( float r, float x, float y );
//		virtual bool startAnimationByMousePointerIntersection( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us );
//
//		osg::Matrixd _matrix;	//Matej
//		osg::Vec3d _center;
//		osg::Quat  _rotation;
//		double     _distance;
//
//		double _trackballSize;
//		double _wheelZoomFactor;
//
//		double _minimumDistance;
//		static int _minimumDistanceFlagIndex;
//
//
//		class OrbitAnimationData : public osgGA::StandardManipulator::AnimationData {
//		public:
//			osg::Vec3d _movement;
//			void start( const osg::Vec3d& movement, const double startTime );
//		};
//		virtual void allocAnimationData() { _animationData = new OrbitAnimationData(); }
//
//		//end Trackball
//	};
//
//	//
//	//  inline functions
//	//
//
//	/** Get the size of the trackball relative to the model size. */
//	inline double OSGCameraManipulator::getTrackballSize() const  { return _trackballSize; }
//	/** Get the mouse wheel zoom factor.*/
//	inline double OSGCameraManipulator::getWheelZoomFactor() const  { return _wheelZoomFactor; }
//
//
//}

#endif //OSG_CAMERA_MANIPULATOR_H