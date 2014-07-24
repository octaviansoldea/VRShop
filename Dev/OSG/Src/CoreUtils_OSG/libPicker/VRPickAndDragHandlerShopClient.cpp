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

/* Modified by Matej Steinbacher and Octavian Soldea */

#include <iostream>
#include <fstream>

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>

#include <osgViewer/Viewer>

#include "VRProduct.h"
#include "VRScene.h"

#include "BasicDefinitions.h"

#include "VRPickAndDragHandlerShopClient.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


PickAndDragHandlerShopClient::PickAndDragHandlerShopClient()	{
}

//-------------------------------------------------------------------------------

PickAndDragHandlerShopClient::~PickAndDragHandlerShopClient()	{
}

//-------------------------------------------------------------------------------

bool PickAndDragHandlerShopClient::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa) {
	osgViewer::Viewer * pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);

	Scene * pScene = dynamic_cast<Scene*>(pViewer->getSceneData());

	bool bRes = true;

	int nEventType = ea.getEventType();
	if (nEventType == GUIEventAdapter::DRAG) {
		bRes = false;
		return(bRes);
	}

	if((PickAndDragHandler::handle(ea, aa) == false) || 
		(m_pPickedObject == NULL))	{
		bRes = false;
		return(bRes);
	}

	if ((nEventType == GUIEventAdapter::LEFT_MOUSE_BUTTON)) {
		AbstractObject * pPickedObject = m_pPickedObject.get();

		//Only first parent is checked if it's a product or not
		int nParent = pPickedObject->getParentalNodePaths().size();
		string strParentName = pPickedObject->getParents()[0]->getName();
		if (strParentName == "Products")	{
			emit signalProductPicked(pPickedObject);
		} else if (pPickedObject->getName() == "Cashier")	{
			emit signalCashierPicked();
		}
	}

	return(bRes);
}

//-----------------------------------------------------------------------
