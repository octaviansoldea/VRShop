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
	//m_dbMouseLastGetX(0), m_dbMouseLastGetY(0),
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

	m_pScene = dynamic_cast<Group*>(pViewer->getSceneData());
	Matrix &mtrxPickedObject = m_mtrxPickedObject;

	bool bRes = true;

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
		//m_nTransformSelection = MOVE_ON_XZ;

		//Remove bounding box - bounding box is put as a last child
		//if(m_pPickedObject!=NULL)
		//	m_pPickedObject->removeChild(m_pPickedObject->getNumChildren()-1);
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

bool PickAndDragHandler::handlePush(const MouseSignals & aMouseSignals, osgViewer::Viewer * apViewer) {
	float flXNormalized = aMouseSignals.m_flXNormalized;
	float flYNormalized = aMouseSignals.m_flYNormalized;

	if(aMouseSignals.m_nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
		double dbMargin = 0.01;

		//Do the polytope intersect the scene graph.
		osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector( 
			osgUtil::Intersector::PROJECTION,
			flXNormalized-dbMargin, flYNormalized-dbMargin,
			flXNormalized+dbMargin, flYNormalized+dbMargin);

		//InteresectionVisitor is used to testing for intersections with the scene
		osgUtil::IntersectionVisitor iv(picker);
		apViewer->getCamera()->accept(iv);

		//Check if any part of the scene was picked
		if (picker->containsIntersections()) {

			m_dbMouseLastGetXNormalized = flXNormalized;
			m_dbMouseLastGetYNormalized = flYNormalized;

			//A vector of Nodes from a root node to a descendant
			NodePath& nodePath = picker->getFirstIntersection().nodePath;

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
				m_mtrxPickedObject = m_pPickedObject->getMatrix();
				PrintMatrix(m_mtrxPickedObject, "Picked object matrix");
			}	
			else
				m_pPickedObject = NULL;
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

		PrintMatrix(m_mtrxPickedObject, "Picked Object when Drag - ging");

		osg::Matrix & mtrxPickedObject = m_mtrxPickedObject;

		float flXNormalized = aMouseSignals.m_flXNormalized;
		float flYNormalized = aMouseSignals.m_flYNormalized;

		//A mouse move 
		float flDiffPosX =	flXNormalized - m_dbMouseLastGetXNormalized; 
		float flDiffPosY =	flYNormalized - m_dbMouseLastGetYNormalized;

		if(fabs(flDiffPosX)<0.001 && fabs(flDiffPosY)<0.001) {
			return false;
		}

		Matrixd mat = apViewer->getCameraManipulator()->getMatrix();
		Vec3f vec3dLook(mat(2,0),mat(2,1),mat(2,2));
		Vec3f eyeVector(mat(3,0),mat(3,1),mat(3,2));

		//Move factor controls the move for the distance of the object from the camera
		float moveFactor = 0.3F * (vec3dLook - eyeVector).length();

		Vec3d vec3dCenter = m_pPickedObject->getBound().center();
		ObjectTransformation oTCenter;
		Matrix mtrxCenter = oTCenter.setTranslationGetMatrix(vec3dCenter[0], vec3dCenter[1], vec3dCenter[2]);

		ObjectTransformation oTSpecific;
		Matrix mtrxSpecific;
		//Does Up/down-left/right dragging respective to the axes
		if(m_nCurrentBasicTransform == TRANSLATE) {
			if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
				mtrxSpecific = oTSpecific.setTranslationGetMatrix(moveFactor*(flDiffPosX), 0.0, moveFactor*(flDiffPosY));
			} else if(m_nCurrentModalityTransform == VIEW_DIRECTION) {
				mtrxSpecific = oTSpecific.setTranslationGetMatrix(
					moveFactor*(flDiffPosX)*mat(0,0), 
					moveFactor*(flDiffPosX)*mat(0,1), 
					moveFactor*(flDiffPosY)
					);
			} else if(m_nCurrentModalityTransform == X_AXIS) {
				mtrxSpecific = 
					oTSpecific.setTranslationGetMatrix(moveFactor*(flDiffPosX), 0.0, 0.0);
			} else if(m_nCurrentModalityTransform == Y_AXIS) {
				mtrxSpecific = 
					oTSpecific.setTranslationGetMatrix(0.0, 0.0, moveFactor*(flDiffPosY));
			} else if(m_nCurrentModalityTransform == Z_AXIS) {
				mtrxSpecific = 
					oTSpecific.setTranslationGetMatrix(0.0, moveFactor*(flDiffPosY), 0.0);
			}
		} else if(m_nCurrentBasicTransform == ROTATE) {
			//Angles should be in radians
			double flRXAngle = flDiffPosY;
			double flRYAngle = flDiffPosX;
			double flRZAngle = flDiffPosX;
			//degrees2Radians(1.0)

			if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
				mtrxSpecific = oTSpecific.setRotationGetMatrix(flRZAngle, ROTATION_ON_Z)	*
					oTSpecific.setRotationGetMatrix(flRYAngle, ROTATION_ON_Y)	*
					oTSpecific.setRotationGetMatrix(flRXAngle, ROTATION_ON_X)	*
					mtrxPickedObject;

			} else if(m_nCurrentModalityTransform == X_AXIS) {
				mtrxSpecific = oTSpecific.setRotationGetMatrix(flRXAngle, ROTATION_ON_X);

			} else if(m_nCurrentModalityTransform == Y_AXIS) {
				mtrxSpecific = oTSpecific.setRotationGetMatrix(flRYAngle, ROTATION_ON_Y);

			} else if(m_nCurrentModalityTransform == Z_AXIS) {
				mtrxSpecific = oTSpecific.setRotationGetMatrix(flRZAngle, ROTATION_ON_Z);
			} 
		} else if(m_nCurrentBasicTransform == SCALE) {
			if(m_nCurrentModalityTransform == X_AXIS) {
				mtrxSpecific = oTSpecific.setScalingGetMatrix(moveFactor*(flDiffPosX), 0.0, 0.0);
			} else if(m_nCurrentModalityTransform == Y_AXIS)	{
				mtrxSpecific = oTSpecific.setScalingGetMatrix(0.0, moveFactor*(flDiffPosX), 0.0);
			} else if(m_nCurrentModalityTransform == Z_AXIS)	{
				mtrxSpecific = oTSpecific.setScalingGetMatrix(0.0, 0.0, moveFactor*(flDiffPosX));
			} else {
				return(false);
			}
		}
		Matrix mtrxCenterInverse;
		osg::ref_ptr < MatrixTransform > pMT = new MatrixTransform();
		pMT->setMatrix(mtrxCenter);
		mtrxCenterInverse = pMT->getInverseMatrix();

		// Central line of matrix frmation : O^-1 S R O
		Matrix mtrxTransformMatrix = mtrxPickedObject * mtrxCenterInverse * mtrxSpecific * mtrxCenter;
		
		m_pPickedObject->setMatrix(mtrxTransformMatrix);

		PrintMatrix(mtrxPickedObject, "mtrxPickedObject");
		PrintMatrix(mtrxSpecific, "mtrxSpecific");
		PrintMatrix(mtrxCenter, "mtrxCenter");
		PrintMatrix(mtrxCenterInverse, "mtrxCenterInverse");

		PrintMatrix(mtrxTransformMatrix, "mtrxTransformMatrix");

		apViewer->setSceneData(m_pScene);

		return(true);
	}

//---------------------------------------------------------------------------------------

void PickAndDragHandler::handleTranslate()	{
}

//---------------------------------------------------------------------------------------

void PickAndDragHandler::handleRotate()	{
}

//---------------------------------------------------------------------------------------

void PickAndDragHandler::handleScale()	{
}

//---------------------------------------------------------------------------------------

void PickAndDragHandler::PrintMatrix(const osg::Matrix & aMtrx, const string & astrTitle) {

	cout << astrTitle << endl;
	int i,j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			cout << aMtrx(i, j) << " ";
		}
		cout << endl;
	}

	cout << endl;

}
