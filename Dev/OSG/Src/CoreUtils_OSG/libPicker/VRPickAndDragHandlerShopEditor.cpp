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
#include "VRObjectTransformation.h"

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

	if (ea.getEventType() == GUIEventAdapter::EventType::DRAG) {
		emit signalPropertiesSettingsChanged();
	}

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
			vec3dRot[0], osg::X_AXIS,
			vec3dRot[1], osg::Y_AXIS,
			vec3dRot[2], osg::Z_AXIS)	*
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
			vec3dRot[0], osg::X_AXIS,
			vec3dRot[1], osg::Y_AXIS,
			vec3dRot[2], osg::Z_AXIS)	*
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

	cout << "Value from the Dialog" << vec3dRot[2] << endl;

	Matrix matrix(Matrix::identity());

	Matrix rotationMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			vec3dRot[0], osg::X_AXIS,
			vec3dRot[1], osg::Y_AXIS,
			vec3dRot[2], osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	int nI,nJ;

	cout << "Matrix: " << endl;
	for (nI=0;nI<4;nI++) {
		for (nJ=0;nJ<4;nJ++) {
			cout << rotationMatrix(nI,nJ) << " ";
		}
		cout << endl;
	}

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

//-----------------------------------------------------------------------------------
