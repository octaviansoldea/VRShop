#include <iostream>

#include "VRKeyboardMouseManipulator.h"
#include "VRPickAndDragHandler.h"

#include <osgViewer/Viewer>

#include "VRKeyboardMousePicker.h"

using namespace VR;
using namespace osgGA;

KeyboardMousePicker::KeyboardMousePicker()	{
}

//-----------------------------------------------------------------------

bool KeyboardMousePicker::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)	{
	osgViewer::Viewer * pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!pViewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	bool bRes = false;
	return(bRes);
}
