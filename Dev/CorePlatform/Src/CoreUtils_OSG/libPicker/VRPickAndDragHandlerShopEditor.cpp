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

#include "BasicDefinitions.h"

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>

#include <osg/ComputeBoundsVisitor>

#include "VRAbstractObjectFactory.h"
#include "VRAbstractObject.h"
#include "VRBoundingBox.h"


#include "VRPickAndDragHandlerShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;

//-------------------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa) {
	bool bRes = true;

	if((PickAndDragHandler::handle(ea, aa) == false) || 
		(m_pPickedObject == NULL))	{
			bRes = false;
			return(bRes);
	}

	int nEventType = ea.getEventType();
	if (nEventType == GUIEventAdapter::DRAG) {
		emit signalPropertiesSettingsChanged();
	}

	if (nEventType == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
		ref_ptr<AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(m_pPickedObject.get());
		emit signalPropertiesSettingsChanged();
		emit signalItemPicked();

		if(ea.getModKeyMask() && osgGA::GUIEventAdapter::MODKEY_CTRL)	{
			bool bRes = addPart(pPickedObject);
			if (bRes==false)	{
				removePart(pPickedObject);
			}
		} else {
			//Only first parent is checked if it's a product or not
			int nParent = pPickedObject->getParentalNodePaths().size()-1;
			const string & strParentName = pPickedObject->getParents()[nParent]->getName();
			if (strParentName == "Products")	{
				const string & strProductName = pPickedObject->getName();
				emit signalProductPicked(strProductName);
			}
		}
	}

	return(bRes);
}

//-----------------------------------------------------------------------

vector<ref_ptr<AbstractObject>> PickAndDragHandlerShopEditor::getPickedObjects()	{
	return m_pvecPickedObjects;
}

//-----------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::addPart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	bool bRes = false;
	ref_ptr < VR::AbstractObject > pAbstractObject = dynamic_cast< VR::AbstractObject *>(apAbstractObject.get());

	if(find(m_pvecPickedObjects.begin(),m_pvecPickedObjects.end(),pAbstractObject) == m_pvecPickedObjects.end())	{
		m_pvecPickedObjects.push_back(pAbstractObject);
		bRes = true;
	}
	return bRes;
}

//-----------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::removePart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	bool bRes = true;
	ref_ptr < VR::AbstractObject > pAbstractObject = dynamic_cast< VR::AbstractObject *>(apAbstractObject.get());

	m_pvecPickedObjects.erase(remove(m_pvecPickedObjects.begin(), m_pvecPickedObjects.end(), pAbstractObject),
		m_pvecPickedObjects.end());

	return bRes;
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::clearList()	{
	m_pvecPickedObjects.clear();
}

//==========================================================================

void PickAndDragHandlerShopEditor::setPropertiesPosition(const osg::Vec3d & avec3dPosition)	{
	if(!m_pPickedObject)
		return;

	ref_ptr<AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(m_pPickedObject.get());

	float flPosX = avec3dPosition[0];
	float flPosY = avec3dPosition[1];
	float flPosZ = avec3dPosition[2];
	pPickedObject->setPosition(flPosX, flPosY, flPosZ);

	Matrix mtrxPos = pPickedObject->calculateMatrix();
	pPickedObject->setMatrix(mtrxPos);
}

//------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::setPropertiesScaling(const Vec3d & avec3dScaling)	{
	if (!m_pPickedObject)
		return;

	ref_ptr<AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(m_pPickedObject.get());

	float flLenX = avec3dScaling[0];
	float flLenY = avec3dScaling[1];
	float flLenZ = avec3dScaling[2];
	pPickedObject->setScaling(flLenX, flLenY, flLenZ);

	Matrix mtrxLen = pPickedObject->calculateMatrix();
	pPickedObject->setMatrix(mtrxLen);
}

//------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::setPropertiesRotation(const Vec3d & avec3dRotation)	{
	if (!m_pPickedObject)
		return;

	ref_ptr<AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(m_pPickedObject.get());

	float flRotX = avec3dRotation[0];
	float flRotY = avec3dRotation[1];
	float flRotZ = avec3dRotation[2];
	pPickedObject->setRotation(flRotX, flRotY, flRotZ);

	Matrix mtrxRot = pPickedObject->calculateMatrix();
	pPickedObject->setMatrix(mtrxRot);
}

//------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::slotSetTransformParams(const QString & astrText)	{
	const QString & strText = astrText;
	m_nCurrentBasicTransform = TRANSLATE;

	if (strText == "Vertical/Lateral")	{
		m_nCurrentModalityTransform = DISPLAY_PLANE;
	} else if (strText == "Lateral")	{
		m_nCurrentModalityTransform = X_AXIS;
	} else if (strText == "Vertical")	{
		m_nCurrentModalityTransform = Z_AXIS;
	} else if (strText == "Longitudinal")	{
		m_nCurrentModalityTransform = Y_AXIS;
	} else if (strText == "Display")	{
		m_nCurrentModalityTransform = VIEW_DIRECTION;
	}
}