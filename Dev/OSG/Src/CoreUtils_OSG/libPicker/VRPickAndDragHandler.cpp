//Pressing "H": make lateral movement
//Pressing "V": make vertical movement
//Pressing "L": make longitudial movement
//Pressing "R": make rotation
//Pressing "S": make scalling
//Pressing "SHIFT L or R": make movement Up/down-Left/right irrespective of axes

#include <osgUtil/PolytopeIntersector>
#include <osgViewer/Viewer>
#include <osg/Group>

#include <iostream>

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
	m_dbMouseLastGetX(0), m_dbMouseLastGetY(0),
	m_nCurrentBasicTransform(TRANSLATE), m_nCurrentModalityTransform(DISPLAY_PLANE) {

}

//------------------------------------------------------------------------------

bool PickAndDragHandler::handle( const GUIEventAdapter& ea, GUIActionAdapter& aa ) {
	osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	if(!viewer)	{
		std::cout << "Error Viewer" << std::endl;
		exit(-1);
	}

	m_pScene = dynamic_cast<Group*>(viewer->getSceneData());

	switch (ea.getEventType())	{
		//Keydown sets the type of the transformation to be performed
	case(GUIEventAdapter::KEYDOWN):	{
		int nKey = ea.getKey();
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
									}	//Case: Keydown

	case(GUIEventAdapter::PUSH):	{
		int nButton = ea.getButton();
		if(nButton == GUIEventAdapter::LEFT_MOUSE_BUTTON) {
			double dbMargin = 0.01;

			//Do the polytope intersections with the scene graph.
			osgUtil::PolytopeIntersector* picker = new osgUtil::PolytopeIntersector( 
				osgUtil::Intersector::PROJECTION,
				ea.getXnormalized()-dbMargin,
				ea.getYnormalized()-dbMargin,
				ea.getXnormalized()+dbMargin,
				ea.getYnormalized()+dbMargin);

			//InteresectionVisitor is used to testing for intersections with the scene
			osgUtil::IntersectionVisitor iv(picker);
			viewer->getCamera()->accept(iv);

			//Check if any part of the scene was picked
			if (picker->containsIntersections()) {
				m_dbMouseLastGetX = ea.getX();
				m_dbMouseLastGetY = ea.getY();

				m_dbMouseLastGetXNormalized = ea.getXnormalized();
				m_dbMouseLastGetYNormalized = ea.getYnormalized();

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
				if(idx >= 0)
					m_mtrxPickedObject = m_pPickedObject->getMatrix();
				else
					m_pPickedObject = NULL;
			}
			else	{
				m_pPickedObject = NULL;
			}
			break;
		}	//Case: Push_Left_Mouse_button
		else {
			m_pPickedObject = NULL;
		}
									}	//Case: Push

	case(GUIEventAdapter::DRAG): {
		if(m_pPickedObject==NULL) {
			return(false);
		}

		//A mouse move 
		float flDiffPosX =	ea.getXnormalized() - m_dbMouseLastGetXNormalized; 
		float flDiffPosY =	ea.getYnormalized() - m_dbMouseLastGetYNormalized;

		if(fabs(flDiffPosX)<0.001 && fabs(flDiffPosY)<0.001) {
			return false;
		}

		Matrixd mat = viewer->getCameraManipulator()->getMatrix();
		Vec3f vec3dLook(mat(2,0),mat(2,1),mat(2,2));
		Vec3f eyeVector(mat(3,0),mat(3,1),mat(3,2));

		//Move factor controls the move for the distance of the object from the camera
		float moveFactor = 0.3F * (vec3dLook - eyeVector).length();

		ObjectTransformation * pObjectTransformation = new ObjectTransformation();
		Matrix mtrx;

		//Does Up/down-left/right dragging respective to the axes
		if(m_nCurrentBasicTransform == TRANSLATE) {
			if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
				mtrx = m_mtrxPickedObject *
					pObjectTransformation->setGetTranslation(moveFactor*(flDiffPosX), 0.0, moveFactor*(flDiffPosY));
			} else if(m_nCurrentModalityTransform == VIEW_DIRECTION) {
				mtrx = m_mtrxPickedObject *
					pObjectTransformation->setGetTranslation(
					moveFactor*(flDiffPosX)*mat(0,0), 
					moveFactor*(flDiffPosX)*mat(0,1), 
					moveFactor*(flDiffPosY)
					);
			} else if(m_nCurrentModalityTransform == X_AXIS) {
				mtrx = m_mtrxPickedObject *
					pObjectTransformation->setGetTranslation(moveFactor*(flDiffPosX), 0.0, 0.0);
			} else if(m_nCurrentModalityTransform == Y_AXIS) {
				mtrx = m_mtrxPickedObject *
					pObjectTransformation->setGetTranslation(0.0, 0.0, moveFactor*(flDiffPosY));
			} else if(m_nCurrentModalityTransform == Z_AXIS) {
				mtrx = m_mtrxPickedObject *
					pObjectTransformation->setGetTranslation(0.0, moveFactor*(flDiffPosY), 0.0);
			}
		} else if(m_nCurrentBasicTransform == ROTATE) {
			if(m_nCurrentModalityTransform == DISPLAY_PLANE) {
				//Angles should be in radians
				double flRXAngle = 
					flDiffPosY
					//				degrees2Radians(1.0)
					;
				double flRYAngle = 
					flDiffPosX
					//				degrees2Radians(1.0)
					;
				double flRZAngle = 
					flDiffPosX
					//				degrees2Radians(1.0)
					;
				mtrx = pObjectTransformation->setGetRotation(flRZAngle, ROTATION_ON_Z)	*
					pObjectTransformation->setGetRotation(flRYAngle, ROTATION_ON_Y)	*
					pObjectTransformation->setGetRotation(flRXAngle, ROTATION_ON_X)	*
					m_mtrxPickedObject;

			} else if(m_nCurrentModalityTransform == X_AXIS) {

			} else if(m_nCurrentModalityTransform == Y_AXIS) {

			} else if(m_nCurrentModalityTransform == Z_AXIS) {

			} else if(m_nCurrentBasicTransform == SCALE) {
				if(m_nCurrentModalityTransform == X_AXIS) {
					mtrx = pObjectTransformation->setGetScaling(moveFactor*(flDiffPosX), moveFactor*(flDiffPosX), moveFactor*(flDiffPosX)) 
						* m_mtrxPickedObject;
				} else if(m_nCurrentModalityTransform == Y_AXIS)	{
					mtrx = pObjectTransformation->setGetScaling(moveFactor*(flDiffPosX), moveFactor*(flDiffPosX), moveFactor*(flDiffPosX)) 
						* m_mtrxPickedObject;
				} else if(m_nCurrentModalityTransform == Z_AXIS)	{
					mtrx = pObjectTransformation->setGetScaling(moveFactor*(flDiffPosX), moveFactor*(flDiffPosX), moveFactor*(flDiffPosX)) 
						* m_mtrxPickedObject;
				} else {
					delete pObjectTransformation;
					return(false);
				}
			}
		}

		delete pObjectTransformation;

		m_pPickedObject->setMatrix(mtrx);

		viewer->setSceneData(m_pScene);

		return(true);
								 }

	case(GUIEventAdapter::RELEASE): {
		//m_nTransformSelection = MOVE_ON_XZ;

		//Remove bounding box - bounding box is put as a last child
		//if(m_pPickedObject!=NULL)
		//	m_pPickedObject->removeChild(m_pPickedObject->getNumChildren()-1);

		return(true);
									}
	}
	return(false);
}
	
//---------------------------------------------------------------------------------------
