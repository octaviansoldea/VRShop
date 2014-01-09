#include <iostream>

#include <osgViewer/Viewer>

#include "VRKeyboardMouseManipulator.h"
#include "VRPickAndDragHandler.h"
#include "VRKeyboardMousePickerManipulator.h"

using namespace std;
using namespace VR;
using namespace osgGA;

KeyboardMousePickerManipulator::KeyboardMousePickerManipulator()	{
	m_pKeyboardMouseManipulator = new KeyboardMouseManipulator ;
	m_pPickAndDragHandler = new PickAndDragHandler;
}

//-----------------------------------------------------------------------

//virtual bool handle(const GUIEventAdapter& ea,GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*) { return handle(ea,aa); }
bool KeyboardMousePickerManipulator::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)	{

	bool bRes = true;
	osgViewer::Viewer * pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(m_pPickAndDragHandler->isIntersection(ea, aa)) {
		cout << "Intersection: m_pPickAndDragHandler" << endl;
		pViewer->addEventHandler( m_pPickAndDragHandler );
		bRes = m_pPickAndDragHandler->handle(ea, aa);
	} else {
		//cout << "No Intersection: m_pKeyboardMouseManipulator" << endl;
		pViewer->setCameraManipulator(m_pKeyboardMouseManipulator);
		bRes = m_pKeyboardMouseManipulator->handle(ea, aa);
		
	}
	return(bRes);
}
