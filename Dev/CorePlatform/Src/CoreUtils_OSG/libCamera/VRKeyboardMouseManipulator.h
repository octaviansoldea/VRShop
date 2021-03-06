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

#ifndef VR_KEYBOARD_MOUSE_MANIPULATOR_H
#define VR_KEYBOARD_MOUSE_MANIPULATOR_H

#include <osgGA/OrbitManipulator>

namespace VR {

	class KeyboardMouseManipulator : public osgGA::OrbitManipulator	{
    public:
        KeyboardMouseManipulator(int flags = DEFAULT_SETTINGS);
        KeyboardMouseManipulator(const KeyboardMouseManipulator& cm,
                             const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY);

        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	private:
		virtual bool keyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		bool keyUp(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter &aa);
	
	protected:
		double		m_dbForwardFactor;		//Forward move value
		double		m_dbDefaultMoveSpeed;	//Speed for a move in any direction

		double		m_dbDirectionRotationRate;	//Side rotation angle

		double		m_dbTranslationFactorZ;		//Angle of rotation on Z 
		double		m_dbTranslationFactorX;		//Angle of rotation on X
		const double m_cdbRotationFactor;		//Angle in radians

		bool m_bCtrl;
		bool m_bShift;
	};
}
#endif //VR_KEYBOARD_MOUSE_MANIPULATOR_H