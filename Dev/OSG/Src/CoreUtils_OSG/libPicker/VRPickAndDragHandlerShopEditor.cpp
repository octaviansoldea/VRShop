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

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>

#include "VRAbstractObject.h"

#include "BasicDefinitions.h"
#include "VRPickAndDragHandlerShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;
using namespace osgGA;


//-------------------------------------------------------------------------------

PickAndDragHandlerShopEditor::PickAndDragHandlerShopEditor()	{
}

//-------------------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa) {
	bool bRes = true;

	if((PickAndDragHandler::handle(ea, aa) == false) || 
		(m_pPickedObject == NULL || 
		!m_mtrxPickedObject.valid())
		)	{
		bRes = false;
		return(bRes);
	}

	addPart(PickAndDragHandler::m_pPickedObject);

	m_pPickedObjects = PickAndDragHandler::m_pPickedObject.get();

	Matrixd vecPickedObjectPos = PickAndDragHandler::m_pPickedObject->getMatrix();

	emit signalPropertiesSettingsChanged(vecPickedObjectPos);

	return(bRes);
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::addPart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	if(find(m_pvecPickedObjects.begin(),m_pvecPickedObjects.end(),apAbstractObject) == m_pvecPickedObjects.end())	{
		m_pvecPickedObjects.push_back(apAbstractObject);
	}
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::removePart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	m_pvecPickedObjects.erase(remove(m_pvecPickedObjects.begin(), m_pvecPickedObjects.end(), apAbstractObject),
		m_pvecPickedObjects.end()); 
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::clearList()	{
	m_pvecPickedObjects.clear();
}

//==========================================================================

void PickAndDragHandlerShopEditor::setPropertiesPosition(const osg::Vec3d & avec3dPosition)	{
	if (m_pvecPickedObjects.size()==0)
		return;

	vector<ref_ptr<AbstractObject>>::iterator it;
	for (it = m_pvecPickedObjects.begin(); it != m_pvecPickedObjects.end(); it++)	{
		ref_ptr <AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(it->get());
		Matrix mtrxTemp = pPickedObject->getMatrix();
		AbstractObjectParams aOP;
		aOP.m_flPosX = avec3dPosition[0];
		aOP.m_flPosY = avec3dPosition[1];
		aOP.m_flPosZ = avec3dPosition[2];
		pPickedObject->setPosition(aOP);

		mtrxTemp.setTrans(avec3dPosition);

		m_pPickedObjects->setMatrix(mtrxTemp);
	}
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