//Pressing "H": make lateral movement
//Pressing "V": make vertical movement
//Pressing "L": make longitudial movement
//Pressing "R": make rotation
//Pressing "S": make scalling
//Pressing "SHIFT L or R": make movement Up/down-Left/right irrespective of axes

#include <iostream>

#include <osgUtil/PolytopeIntersector>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/MatrixTransform>

#include "VRBoundingBox.h"
#include "VRAbstractObject.h"
#include "BasicDefinitions.h"
#include "VRObjectTransformation.h"

#include "VRPickAndDragHandler.h"

using namespace osg;
using namespace osgGA;
using namespace VR;
using namespace std;

PickAndDragHandler::PickAndDragHandler() :
	m_dbMouseLastGetXNormalized(0), m_dbMouseLastGetYNormalized(0),
	m_nCurrentBasicTransform(TRANSLATE), m_nCurrentModalityTransform(DISPLAY_PLANE) {
}

//---------------------------------------------------------------------------------------

void PickAndDragHandler::getMouseSignals(MouseSignals * apMouseSignals, const GUIEventAdapter & ea) {
	apMouseSignals->m_nButton = ea.getButton();
	apMouseSignals->m_flXNormalized = ea.getXnormalized();
	apMouseSignals->m_flYNormalized = ea.getYnormalized();
}

//------------------------------------------------------------------------------

// The role of this function is to read the computer interface and send it to handles
bool PickAndDragHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa ) {
	osgViewer::Viewer * pViewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!pViewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

//	bool bRes = true;
	bool bRes = false;

	int nResEvent = ea.getEventType();
	if(nResEvent == GUIEventAdapter::KEYDOWN) {
		int nKey = ea.getKey();
		bRes = handleKeyDown(nKey);
	} else if (nResEvent == GUIEventAdapter::PUSH)	{
		MouseSignals mouseSignals;
		getMouseSignals(&mouseSignals, ea);
		bRes = handlePush(mouseSignals, pViewer);
	} else if (nResEvent == GUIEventAdapter::DRAG) {
		if(m_pPickedObject==NULL) {
			return(false);
		}
		MouseSignals mouseSignals;
		getMouseSignals(&mouseSignals, ea);
		bRes = handleDrag(mouseSignals, pViewer);			
	} else if (nResEvent == GUIEventAdapter::RELEASE)	{
		bRes = true;
	}

	return(bRes);
}

//---------------------------------------------------------------------------------------

bool PickAndDragHandler::handleKeyDown(int anKey) {
	int nKey = anKey;
	if((nKey == 't') || (nKey == 'T'))
		m_nCurrentBasicTransform = TRANSLATE;
	else if((nKey == 'r') || (nKey == 'R'))
		m_nCurrentBasicTransform = ROTATE;
	else if((nKey == 's') || (nKey == 'S'))
		m_nCurrentBasicTransform = SCALE;
	else if((nKey == 'p') || (nKey == 'P')) {
		if(m_nCurrentBasicTransform == TRANSLATE) {
			m_nCurrentModalityTransform = DISPLAY_PLANE;
		} else {
			return(false);
		}
	} else if((nKey == 'c') || (nKey == 'C')) {
		if((m_nCurrentBasicTransform == TRANSLATE) || (m_nCurrentBasicTransform == ROTATE)) {
			m_nCurrentModalityTransform = VIEW_DIRECTION;
		}  else {
			return(false);
		}
	} else if((nKey == 'x') || (nKey == 'X')) {
		m_nCurrentModalityTransform = X_AXIS;
	} else if((nKey == 'y') || (nKey == 'Y')) {
		m_nCurrentModalityTransform = Y_AXIS;
	} else if((nKey == 'z') || (nKey == 'Z')) {
		m_nCurrentModalityTransform = Z_AXIS;
	} else {
		return(false);
	}
	return(true);
}

//---------------------------------------------------------------------------------------

bool PickAndDragHandler::handlePush(const MouseSignals & aMouseSignals, osgViewer::Viewer * apViewer) {
	float flXNormalized = aMouseSignals.m_flXNormalized;
	float flYNormalized = aMouseSignals.m_flYNormalized;

	if(aMouseSignals.m_nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
		float flMargin = 0.01;

		//Do the polytope intersect the scene graph.
		ref_ptr<osgUtil::PolytopeIntersector> pPicker = new osgUtil::PolytopeIntersector( 
			osgUtil::Intersector::PROJECTION,
			flXNormalized-flMargin, flYNormalized-flMargin,
			flXNormalized+flMargin, flYNormalized+flMargin);

		//InteresectionVisitor is used to testing for intersections with the scene
		osgUtil::IntersectionVisitor iv(pPicker);
		apViewer->getCamera()->accept(iv);

		//Check if any part of the scene was picked
		if (pPicker->containsIntersections()) {

			m_dbMouseLastGetXNormalized = flXNormalized;
			m_dbMouseLastGetYNormalized = flYNormalized;

			//A vector of Nodes from a root node to a descendant
			NodePath& nodePath = pPicker->getFirstIntersection().nodePath;

			//Navigate through nodes and pick the "right" one
			int idx;
			for(idx=nodePath.size()-1; idx>=0; idx--) {
				m_pPickedObject = dynamic_cast<AbstractObject*>(nodePath[idx]);
				if(m_pPickedObject != NULL && m_pPickedObject->getIsTargetPick() != false) {
					break;
				}
			}

			//Get the matrix of the picked object and pass it to the drag
			if(idx >= 0) {
				return(true);
			} else {
				m_pPickedObject = NULL;
			}
		}
		else	{
			m_pPickedObject = NULL;
		}
	}	//Case: Push_Left_Mouse_button
	else {
		m_pPickedObject = NULL;
	}
	return(true);
}

//---------------------------------------------------------------------------------------

bool PickAndDragHandler::handleDrag(const MouseSignals & aMouseSignals, osgViewer::Viewer * apViewer) {
	float flXNormalized = aMouseSignals.m_flXNormalized;
	float flYNormalized = aMouseSignals.m_flYNormalized;

	//A mouse move 
	float flDiffPosX =	flXNormalized - m_dbMouseLastGetXNormalized; 
	float flDiffPosY =	flYNormalized - m_dbMouseLastGetYNormalized;

	if(fabs(flDiffPosX)<0.001 && fabs(flDiffPosY)<0.001) {
		return false;
	}

	m_dbMouseLastGetXNormalized = flXNormalized;
	m_dbMouseLastGetYNormalized = flYNormalized;

	Matrixd mat = apViewer->getCameraManipulator()->getMatrix();
	Vec3f vec3dLook(mat(2,0),mat(2,1),mat(2,2));
	Vec3f eyeVector(mat(3,0),mat(3,1),mat(3,2));

	//Move factor controls the move for the distance of the object from the camera
	float moveFactor = 0.3F * (vec3dLook - eyeVector).length();

	//Does Up/down-left/right dragging respective to the axes
	if(m_nCurrentBasicTransform == TRANSLATE) {
		float flPosX=0.0;
		float flPosY=0.0;
		float flPosZ=0.0;

		if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
			flPosX = m_pPickedObject->getPosition()[0] + moveFactor*(flDiffPosX);
			flPosY = m_pPickedObject->getPosition()[1];
			flPosZ = m_pPickedObject->getPosition()[2] + moveFactor*(flDiffPosY);

			m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);

		} else if(m_nCurrentModalityTransform == VIEW_DIRECTION) {
			flPosX = m_pPickedObject->getPosition()[0] + moveFactor*(flDiffPosX)*mat(0,0);
			flPosY = m_pPickedObject->getPosition()[1] + moveFactor*(flDiffPosX)*mat(0,1);
			flPosZ = m_pPickedObject->getPosition()[2] + moveFactor*(flDiffPosY);

			m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);

		} else if(m_nCurrentModalityTransform == X_AXIS) {
			flPosX = m_pPickedObject->getPosition()[0] + moveFactor*(flDiffPosX);
			flPosY = m_pPickedObject->getPosition()[1];
			flPosZ = m_pPickedObject->getPosition()[2];

			m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);

		} else if(m_nCurrentModalityTransform == Y_AXIS) {
			flPosX = m_pPickedObject->getPosition()[0];
			flPosY = m_pPickedObject->getPosition()[1] + moveFactor*(flDiffPosY);
			flPosZ = m_pPickedObject->getPosition()[2];

			m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);

		} else if(m_nCurrentModalityTransform == Z_AXIS) {
			flPosX = m_pPickedObject->getPosition()[0];
			flPosY = m_pPickedObject->getPosition()[1];
			flPosZ = m_pPickedObject->getPosition()[2] + moveFactor*(flDiffPosY);

			m_pPickedObject->setPosition(flPosX, flPosY, flPosZ);
		}

	} else if(m_nCurrentBasicTransform == ROTATE) {
		//Angles should be in radians
		float flRXAngle=0.0;
		float flRYAngle=0.0;
		float flRZAngle=0.0;

		if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
			flRXAngle = flDiffPosY;
			flRYAngle = flDiffPosX;
			flRZAngle = flDiffPosX;

			flRXAngle = m_pPickedObject->getRotation()[0] + flDiffPosY*moveFactor;
			flRYAngle = m_pPickedObject->getRotation()[1] + flDiffPosX*moveFactor;
			flRZAngle = m_pPickedObject->getRotation()[2] + flDiffPosX*moveFactor;

			m_pPickedObject->setRotation(flRXAngle, flRYAngle, flRZAngle);

		} else if(m_nCurrentModalityTransform == X_AXIS) {
			flRXAngle = m_pPickedObject->getRotation()[0] + flDiffPosY*moveFactor;
			flRYAngle = m_pPickedObject->getRotation()[1];
			flRZAngle = m_pPickedObject->getRotation()[2];

			m_pPickedObject->setRotation(flRXAngle, flRYAngle, flRZAngle);

		} else if(m_nCurrentModalityTransform == Y_AXIS) {
			flRXAngle = m_pPickedObject->getRotation()[0];
			flRYAngle = m_pPickedObject->getRotation()[1] + flDiffPosX*moveFactor;
			flRZAngle = m_pPickedObject->getRotation()[2];

			m_pPickedObject->setRotation(flRXAngle, flRYAngle, flRZAngle);
		} else if(m_nCurrentModalityTransform == Z_AXIS) {
			flRXAngle = m_pPickedObject->getRotation()[0];
			flRYAngle = m_pPickedObject->getRotation()[1];
			flRZAngle = m_pPickedObject->getRotation()[2] + flDiffPosX*moveFactor;

			m_pPickedObject->setRotation(flRXAngle, flRYAngle, flRZAngle);
		} else {
			flRXAngle = m_pPickedObject->getRotation()[0] + flDiffPosY*moveFactor;
			flRYAngle = m_pPickedObject->getRotation()[1] + flDiffPosX*moveFactor;
			flRZAngle = m_pPickedObject->getRotation()[2];

			m_pPickedObject->setRotation(flRXAngle, flRYAngle, flRZAngle);
		}

	} else if(m_nCurrentBasicTransform == SCALE) {
		float flLenX=0.0;
		float flLenY=0.0;
		float flLenZ=0.0;

		if(m_nCurrentModalityTransform == X_AXIS) {
			flLenX = m_pPickedObject->getScaling()[0] + moveFactor*(flDiffPosX);
			flLenY = m_pPickedObject->getScaling()[1];
			flLenZ = m_pPickedObject->getScaling()[2];

			m_pPickedObject->setScaling(flLenX, flLenY, flLenZ);
		} else if(m_nCurrentModalityTransform == Y_AXIS)	{
			flLenX = m_pPickedObject->getScaling()[0];
			flLenY = m_pPickedObject->getScaling()[1] + moveFactor*(flDiffPosX);
			flLenZ = m_pPickedObject->getScaling()[2];

			m_pPickedObject->setScaling(flLenX, flLenY, flLenZ);

		} else if(m_nCurrentModalityTransform == Z_AXIS)	{
			flLenX = m_pPickedObject->getScaling()[0];
			flLenY = m_pPickedObject->getScaling()[1];
			flLenZ = m_pPickedObject->getScaling()[2] + moveFactor*(flDiffPosY);

			m_pPickedObject->setScaling(flLenX, flLenY, flLenZ);
		} else {
			flLenX = m_pPickedObject->getScaling()[0];
			flLenY = m_pPickedObject->getScaling()[1];
			flLenZ = m_pPickedObject->getScaling()[2];

			m_pPickedObject->setScaling(flLenX, flLenY, flLenZ);
		}
	}
	Vec3d vec3dPos = m_pPickedObject->getPosition();
	Vec3d vec3dRot = m_pPickedObject->getRotation();
	Vec3d vec3dLen = m_pPickedObject->getScaling();

	Matrix matrix(Matrix::identity());

	Matrix positionMatrix =
		matrix.scale(vec3dLen)	*
		matrix.rotate(
			degrees2Radians(vec3dRot[0]), osg::X_AXIS,
			degrees2Radians(vec3dRot[1]), osg::Y_AXIS,
			degrees2Radians(vec3dRot[2]), osg::Z_AXIS)	*
		matrix.translate(vec3dPos);

	m_pPickedObject->setMatrix(positionMatrix);

	ref_ptr<Group> pScene = dynamic_cast<Group*>(apViewer->getSceneData());
	apViewer->setSceneData(pScene);

	return(true);
}

//---------------------------------------------------------------------------------------