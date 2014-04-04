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

namespace VR {

	class OSGCameraManipulator : public osgGA::OrbitManipulator
	{
		typedef osgGA::OrbitManipulator inherited;

    public:

        OSGCameraManipulator(int flags = DEFAULT_SETTINGS);
        OSGCameraManipulator(const OSGCameraManipulator& om,
                             const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);

	private:
        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

		bool keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		bool keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);

		double		m_dbForwardFactor;		//Forward move value
		double		m_dbDefaultMoveSpeed;	//Speed for a move in any direction

		double		m_dbDirectionRotationRate;	//Side rotation angle

		double		m_dbPitchOffsetRate;	//Angle of rotation on Z 
		double		m_dbPitchOffset;		//Accumulates angle of rotation on Z
		double		m_dbLateralRotationRate;		//Angle of rotation on X
		const double m_cdbRotationFactor;	//Angle in radians

		bool m_bCtrl;
		bool m_bShift;
	};
}
#endif //OSG_CAMERA_MANIPULATOR_H