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

#include "VRScene.h"
#include "VRAbstractObject.h"
#include "VRBoundingBox.h"

#include "BasicDefinitions.h"

#include <QStringListModel>

#include "VRDuplicateItem_GUI.h"
#include "VRRemoveSelection_GUI.h"


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
	osgViewer::Viewer * pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);

	ref_ptr<Scene > pScene = dynamic_cast<VR::Scene*>(pViewer->getSceneData());

	bool bRes = true;

	if((PickAndDragHandler::handle(ea, aa) == false) || 
		(m_pPickedObject == NULL))	{
		bRes = false;
		return(bRes);
	}

	int nEventType = ea.getEventType();
	if ((nEventType == GUIEventAdapter::DRAG)) {
		emit signalPropertiesSettingsChanged();

		pScene->print();
	}
	if ((nEventType == GUIEventAdapter::LEFT_MOUSE_BUTTON)) {		
		emit signalPropertiesSettingsChanged();

		pScene->print();
	}

	if(nEventType == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL)	{
		ref_ptr< AbstractObject> pPickedObject = dynamic_cast<AbstractObject*>(m_pPickedObject.get());

		bool bRes = addPart(pPickedObject);
		if (bRes==false)	{
			removePart(pPickedObject);
		}
	}

	return(bRes);
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

	Matrix & mtrxPos = pPickedObject->calculateMatrix();
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

	Matrix & mtrxLen = pPickedObject->calculateMatrix();
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

	Matrix & mtrxRot = pPickedObject->calculateMatrix();
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

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::groupSelection(ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 2)	{
		cout << "Too few items selected for grouping" << endl;
		return;
	}

	vector<ref_ptr<VR::AbstractObject>>::iterator it = m_pvecPickedObjects.begin();
	
	ref_ptr<VR::AbstractObject> pGroupedObject = dynamic_cast<AbstractObject*>(AbstractObject::createInstance("CustomFurniture").get());
	for (it; it != m_pvecPickedObjects.end(); it++)	{
		it->get()->setIsTargetPick(false);
		pGroupedObject->addChild(*it);
		apScene->removeChild(*it);
	}
	pGroupedObject->setIsTargetPick(true);
	apScene->addChild(pGroupedObject.get());

	clearList();
}

//-----------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::splitSelection(ref_ptr<Scene> apScene)	{
	if (m_pvecPickedObjects.size() == 0)	{
		cout << "No items selected" << endl;
		return;
	}

	vector<ref_ptr<AbstractObject>>::iterator it = m_pvecPickedObjects.begin();

	ref_ptr<AbstractObject> pAbstractObject;

	Vec3d vec3dPos;
	Vec3d vec3dRot;
	Vec3d vec3dLen;

	for (it; it != m_pvecPickedObjects.end(); it++)	{
		vec3dPos = it->get()->getPosition();
		vec3dRot = it->get()->getRotation();
		vec3dLen = it->get()->getScaling();

		apScene->removeChild(*it);
		int nI;
		for (nI=0;nI<it->get()->getNumChildren(); nI++)	{
			pAbstractObject = dynamic_cast<AbstractObject *>(it->get()->getChild(nI));

			Vec3d vec3dPosItem = pAbstractObject->getPosition();
			Vec3d vec3dRotItem = pAbstractObject->getRotation();
			Vec3d vec3dLenItem = pAbstractObject->getScaling();

			pAbstractObject->setPosition(vec3dPosItem[0]+vec3dPos[0], vec3dPosItem[1]+vec3dPos[1], vec3dPosItem[2]+vec3dPos[2]);
			pAbstractObject->setRotation(vec3dRotItem[0]+vec3dRot[0], vec3dRotItem[1]+vec3dRot[1], vec3dRotItem[2]+vec3dRot[2]);
			pAbstractObject->setScaling(vec3dLenItem[0]*vec3dLen[0], vec3dLenItem[1]*vec3dLen[1], vec3dLenItem[2]*vec3dLen[2]);

			Matrix & mtrxItem = pAbstractObject->calculateMatrix();
			pAbstractObject->setMatrix(mtrxItem);

			pAbstractObject->setIsTargetPick(true);
			apScene->addChild(pAbstractObject);
		}
	}
	clearList();
}

//-----------------------------------------------------------------------

void PickAndDragHandlerShopEditor::duplicateSelection(ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	//If selection not empty, open the dialog
	DuplicateItem_GUI * pDuplicateItem_GUI = new DuplicateItem_GUI;
	pDuplicateItem_GUI->setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = pDuplicateItem_GUI->exec();
	const int nNumberOfCopies = pDuplicateItem_GUI->m_pSpinBoxCopies->text().toInt();

	if ((bRes == 0) || (nNumberOfCopies == 0))	{
		clearList();
		delete pDuplicateItem_GUI;
		return;
	}

	Vec3d vec3dPos = Vec3d(
		pDuplicateItem_GUI->m_pLineEditLocationX->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditLocationY->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditLocationZ->text().toFloat());

	Vec3d vec3dRot = Vec3d(
		pDuplicateItem_GUI->m_pLineEditRotationX->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditRotationY->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditRotationZ->text().toFloat());

	Vec3d vec3dLen = Vec3d(
		pDuplicateItem_GUI->m_pLineEditScaleX->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditScaleY->text().toFloat(),
		pDuplicateItem_GUI->m_pLineEditScaleZ->text().toFloat());

	vector<osg::ref_ptr<AbstractObject>>::iterator it;

	ref_ptr<AbstractObject> pObject = 0;
	int nI;
	for (nI=0;nI<nNumberOfCopies;nI++)	{
		for (it = m_pvecPickedObjects.begin(); it != m_pvecPickedObjects.end(); it++)	{
			//An open issue with the matrix
			pObject = dynamic_cast<AbstractObject*>(it->get()->clone(CopyOp::DEEP_COPY_ALL));
			apScene->addChild(pObject);
		}
	}
	clearList();
	delete pDuplicateItem_GUI;
}

//-----------------------------------------------------------------------------------

void PickAndDragHandlerShopEditor::removeSelection(ref_ptr<Scene> apScene)	{
	if(m_pvecPickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	//If selection not empty, open the dialog
	RemoveSelection_GUI removeSelection_GUI;
	removeSelection_GUI.setWindowFlags(Qt::FramelessWindowHint);

	QStringListModel model;
	QStringList list;

	vector<ref_ptr<AbstractObject>>::iterator it;
	for (it = m_pvecPickedObjects.begin(); it != m_pvecPickedObjects.end(); it++)	{
		list.push_back(string("- " + it->get()->getName()).c_str());
	}

	model.setStringList(list);
	removeSelection_GUI.m_pListView->setModel(&model);

	bool bRes = removeSelection_GUI.exec();
	if (bRes == true)	{
		for (it = m_pvecPickedObjects.begin(); it != m_pvecPickedObjects.end(); it++)	{
			apScene->removeChild(*it);
		}
	}
	clearList();
}
