#ifndef VR_KEYBOARD_MOUSE_PICKER_H
#define VR_KEYBOARD_MOUSE_PICKER_H

#include <osgGA/GUIEventHandler>

#include "VRKeyboardMouseManipulator.h"
#include "VRPickAndDragHandler.h"
#include <osgGA/TrackballManipulator>

namespace VR	{
	class KeyboardMousePicker : public osgGA::GUIEventHandler	{
	public:
		KeyboardMousePicker();

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	};
}
#endif //VR_KEYBOARD_MOUSE_PICKER_H