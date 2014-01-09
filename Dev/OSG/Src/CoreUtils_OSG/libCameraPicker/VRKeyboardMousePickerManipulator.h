#ifndef VR_KEYBOARD_MOUSE_PICKER_H
#define VR_KEYBOARD_MOUSE_PICKER_H

#include <osgGA/GUIEventHandler>

#include "VRKeyboardMouseManipulator.h"
#include "VRPickAndDragHandler.h"
#include <osgGA/TrackballManipulator>

namespace VR	{
	class KeyboardMousePickerManipulator : 
		public osgGA::GUIEventHandler {
	public:
		KeyboardMousePickerManipulator();

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	protected:
		osg::ref_ptr < KeyboardMouseManipulator > m_pKeyboardMouseManipulator;
		osg::ref_ptr < PickAndDragHandler > m_pPickAndDragHandler;
	};
}
#endif //VR_KEYBOARD_MOUSE_PICKER_H