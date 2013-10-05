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

		private:

			virtual ~OSGCameraManipulator();

			osg::observer_ptr<osg::Node> m_pNode;
			osg::Matrixd m_mtrxdbMatrix;		//View matrix
			osg::Matrixd m_mtrxdbInverseMatrix;	//Current position with the inverse matrix
			osg::Matrixd m_mtrxdbOffset;		//Corrects view-matrix for rotations on Z

			double		m_dbForwardFactor;		//Forward move value
			double m_cdbDefaultMoveSpeed;	//Speed for a move in any direction

			double		m_dbDirectionRotationRate;	//Side rotation angle

			double		m_dbPitchOffsetRate;	//Angle of rotation on Z 
			double		m_dbPitchOffset;		//Accumulates angle of rotation on Z
			double		m_dbLateralRotationRate;		//Angle of rotation on X
			const double m_cdbRotationFactor;	//Angle in radians

			osg::Vec3d	m_vecdbPosition;		//Eye (position of the camera)
			osg::Vec3d	m_vecdbDirection;		//Center (center of objects) - Eye

			bool m_bCtrl;
			bool m_bShift;

			void stop();
			void keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
			void keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);

			void updateMatrices();
			void setCameraPosition();
	};
}
#endif //OSG_CAMERA_MANIPULATOR_H