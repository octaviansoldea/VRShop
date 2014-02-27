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
#include "VRScene.h"

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
		(m_pPickedObject == NULL))	{
		bRes = false;
		return(bRes);
	}

	int nEventType = ea.getEventType();
	if ((nEventType == GUIEventAdapter::DRAG) || (nEventType == GUIEventAdapter::LEFT_MOUSE_BUTTON)) {
		
		emit signalPropertiesSettingsChanged();
	}

	if(nEventType == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL)	{
		bool bRes = addPart(PickAndDragHandler::m_pPickedObject);
		if (bRes==false)	{
			removePart(PickAndDragHandler::m_pPickedObject);
		}
	}

	return(bRes);
}

//-----------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::addPart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	bool bRes = false;
	if(find(m_pvecPickedObjects.begin(),m_pvecPickedObjects.end(),apAbstractObject) == m_pvecPickedObjects.end())	{
		m_pvecPickedObjects.push_back(apAbstractObject);
		bRes = true;
	}
	return bRes;
}

//-----------------------------------------------------------------------

bool PickAndDragHandlerShopEditor::removePart(ref_ptr < VR::AbstractObject > apAbstractObject) {
	bool bRes = true;
	m_pvecPickedObjects.erase(remove(m_pvecPickedObjects.begin(), m_pvecPickedObjects.end(), apAbstractObject),
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

	float flPosX = avec3dPosition[0];
	float flPosY = avec3dPosition[1];
	float flPosZ = avec3dPosition[2];
	m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);

	Vec3d vec3dPos = m_pPickedObject->getPosition();
	Vec3d vec3dRot = m_pPickedObject->getRotation();
	Vec3d vec3dLen = m_pPickedObject->getScaling();

	Matrix matrix(Matrix::identity());

	Matrix posMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			degrees2Radians(vec3dRot[0]), osg::X_AXIS,
			degrees2Radians(vec3dRot[1]), osg::Y_AXIS,
			degrees2Radians(vec3dRot[2]), osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	m_pPickedObject->setMatrix(posMatrix);
}

//------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::setPropertiesScaling(const Vec3d & avec3dScaling)	{
	if (!m_pPickedObject)
		return;

	float flLenX = avec3dScaling[0];
	float flLenY = avec3dScaling[1];
	float flLenZ = avec3dScaling[2];
	m_pPickedObject->setScaling(flLenX, flLenY, flLenZ);

	Vec3d vec3dPos = m_pPickedObject->getPosition();
	Vec3d vec3dRot = m_pPickedObject->getRotation();
	Vec3d vec3dLen = m_pPickedObject->getScaling();

	Matrix matrix(Matrix::identity());

	Matrix scalingMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			degrees2Radians(vec3dRot[0]), osg::X_AXIS,
			degrees2Radians(vec3dRot[1]), osg::Y_AXIS,
			degrees2Radians(vec3dRot[2]), osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	m_pPickedObject->setMatrix(scalingMatrix);
}

//------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::setPropertiesRotation(const Vec3d & avec3dRotation)	{
	if (!m_pPickedObject)
		return;

	float flRotX = avec3dRotation[0];
	float flRotY = avec3dRotation[1];
	float flRotZ = avec3dRotation[2];
	m_pPickedObject->setRotation(flRotX, flRotY, flRotZ);

	Vec3d vec3dPos = m_pPickedObject->getPosition();
	Vec3d vec3dRot = m_pPickedObject->getRotation();
	Vec3d vec3dLen = m_pPickedObject->getScaling();

	Matrix matrix(Matrix::identity());

	Matrix rotationMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			degrees2Radians(vec3dRot[0]), osg::X_AXIS,
			degrees2Radians(vec3dRot[1]), osg::Y_AXIS,
			degrees2Radians(vec3dRot[2]), osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	m_pPickedObject->setMatrix(rotationMatrix);
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

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::groupSelection(osg::ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 2)	{
		cout << "Too few items selected for grouping" << endl;
		return;
	}

	vector<ref_ptr<VR::AbstractObject>>::iterator it = m_pvecPickedObjects.begin();
	
	ref_ptr<VR::AbstractObject> pGroupedObject = dynamic_cast<AbstractObject*>(AbstractObject::createInstance("CustomFurniture").get());
	for (it=it; it != m_pvecPickedObjects.end(); it++)	{		
		it->get()->setIsTargetPick(false);
		pGroupedObject->addChild(*it);
		apScene->removeElement(*it);
	}
	pGroupedObject->setIsTargetPick(true);
	apScene->addElement(pGroupedObject);

	clearList();
}

//-----------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::splitSelection(osg::ref_ptr<Scene> apScene)	{
	if (m_pvecPickedObjects.size() == 0)	{
		cout << "No items selected" << endl;
		return;
	}

	vector<osg::ref_ptr<AbstractObject>>::iterator it = m_pvecPickedObjects.begin();

	int nI;
	ref_ptr<AbstractObject> pAbstractObject;
	for (it; it != m_pvecPickedObjects.end(); it++)	{
		apScene->removeElement(*it);
		for (nI=0;nI<it->get()->getNumChildren(); nI++)	{
			pAbstractObject = dynamic_cast<AbstractObject *>(it->get()->getChild(nI));
			pAbstractObject->setIsTargetPick(true);
			apScene->addElement(pAbstractObject);
		}
	}
	clearList();
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::duplicateSelection(osg::ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	vector<osg::ref_ptr<AbstractObject>>::iterator it = m_pvecPickedObjects.begin();

	int nI;
	ref_ptr<AbstractObject> pAbstractObject;
	for (it; it != m_pvecPickedObjects.end(); it++)	{
		pAbstractObject = AbstractObject::createInstance("Container");
		float Pos[3] = {2,0,0};
		pAbstractObject->setPosition(Pos[0],Pos[1],Pos[2]);
		apScene->addElement(pAbstractObject.get());
	}
	clearList();
}

//-----------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::removeSelection(ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	vector<osg::ref_ptr<AbstractObject>>::iterator it = m_pvecPickedObjects.begin();

	int nI;
	ref_ptr<AbstractObject> pAbstractObject;
	for (it; it != m_pvecPickedObjects.end(); it++)	{
		pAbstractObject = dynamic_cast<AbstractObject *>(it->get());
		apScene->removeElement(pAbstractObject);
	}
	clearList();
}

