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

namespace VR {

	class OSGCameraManipulator : public osgGA::CameraManipulator	{
		public:
			OSGCameraManipulator();

			virtual const char* className() const;
			virtual void setByMatrix( const osg::Matrixd &matrix ) ;
			virtual void setByInverseMatrix( const osg::Matrixd &invmat);
			virtual osg::Matrixd getMatrix() const;
			virtual osg::Matrixd getInverseMatrix() const ;
			virtual void setNode(osg::Node* node);
			virtual const osg::Node* getNode() const;
			virtual osg::Node* getNode();
			virtual void computeHomePosition();
			virtual void home(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) ;
			void home(double);

			virtual void init(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);

			bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter &aa);

		protected:

			virtual ~OSGCameraManipulator();

			osg::observer_ptr<osg::Node> _node;
			osg::Matrixd _matrix;
			osg::Matrixd _inverseMatrix;
			osg::Matrixd _offset;

			double		m_dbForwardFactor;
			double		m_dbDefaultMoveSpeed;

			double		_directionRotationRate;

			double		_pitchOffsetRate;
			double		_pitchOffset;
			double		_yawOffsetRate;
			double		_yawOffset;
			double		m_dbRotationFactor;

			double		_t0;
			osg::Vec3d	_direction;
			osg::Vec3d	_position;

			bool m_bCtrl;

			void _stop();
			void _keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &);
			void _keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &);
			void _frame(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &);

			void setCameraPosition();
	};
}
#endif //OSG_CAMERA_MANIPULATOR_H